/*
 * Copyright (C) 2001-2006 Jacek Sieka, arnetheduck on gmail point com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

/*
 * Automatic Directory Listing Search
 * Henrik Engström, henrikengstrom at home se
 */
 
 // Pothead used ADLSearch.cpp as a template

#include "stdinc.h"
#include "../../client/DCPlusPlus.h"

#include "AutoSearch.h"

#include "../../client/File.h"
#include "../../client/SimpleXML.h"
#include "../../client/ClientManager.h"
#include "../../client/QueueManager.h"
#include "../../client/LogManager.h"
#include "../FdmUtil.h"

AutoSearchManager::AutoSearchManager() {
	TimerManager::getInstance()->addListener(this);
	SearchManager::getInstance()->addListener(this);
	QueueManager::getInstance()->setBlockAutoSearch(false);
	Load();

	curPos = 0;
	timeToSearch = 7 * 60;
	time = 0;
}

AutoSearchManager::~AutoSearchManager() {
	SearchManager::getInstance()->removeListener(this);
	TimerManager::getInstance()->removeListener(this);
	Save();
}

void AutoSearchManager::on(TimerManagerListener::Minute, uint32_t /*aTick*/) throw() {
	Lock l(cs);
	time++;

	// If not alright to search, retry in a minute
	if (time < timeToSearch || !SearchManager::getInstance()->okToSearch())
		return;

	if (time == timeToSearch)
		QueueManager::getInstance()->setBlockAutoSearch(true);

	AutoSearchCollection::iterator pos = collection.begin() + curPos;

	// If have some searches
	if (pos < collection.end()) {
		if (!pos->isActive) {
			curPos++;
			return;
		}

		if (pos->onlyIfOp) {
			clientsWhereOp.clear();

			ClientManager* clientMgr = ClientManager::getInstance();
			clientMgr->lock();

			Client::List& clients = clientMgr->getClients();
			for(Client::List::iterator it = clients.begin(); it != clients.end(); ++it) {
				Client* client = *it;
				if(!client->isConnected())
					continue;
				if(client->isOp())
					clientsWhereOp.push_back(client->getHubUrl());
			}
			clientMgr->unlock();

			if(!clientsWhereOp.size()) {
				// Not Op anywhere, next search
				curPos++;
				return;
			}

			SearchManager::getInstance()->search(clientsWhereOp, pos->searchString, (int64_t)pos->size * AutoSearch::GetSize(pos->typeFileSize), (SearchManager::TypeModes)pos->sourceType, (SearchManager::SizeModes)pos->typeFileSize, "auto");
		} else {
			SearchManager::getInstance()->search(pos->searchString, (int64_t)pos->size * AutoSearch::GetSize(pos->typeFileSize), (SearchManager::TypeModes)pos->sourceType, (SearchManager::SizeModes)pos->typeFileSize, "auto");
		}

		// Setup wanted results for matching with search results
		clearAndAddToStringList(resMatch, pos->resultsMatch);
		clearAndAddToStringList(resExclude, pos->resultsExclude);
		clearAndAddToStringList(resExtensions, pos->resultsExtensions);
		resMinSize = (int64_t)pos->resultsMinSize * AutoSearch::GetSize(pos->resultsTypeFileSize);
		resMaxSize = (int64_t)pos->resultsMaxSize * AutoSearch::GetSize(pos->resultsTypeFileSize);

		// Prepare for next search
		curPos++;
		timeToSearch += 5;
	} else {
	// Finished autosearch
		time = 0;
		timeToSearch = 7 * 60;
		curPos = 0;
		QueueManager::getInstance()->setBlockAutoSearch(false);
	}
}

void AutoSearchManager::clearAndAddToStringList(StringList& aStringList, string aString) {
	Lock l(cs);
	aStringList.clear();
	StringTokenizer<string> st(aString, '|');
	for(StringIter i = st.getTokens().begin(); i != st.getTokens().end(); ++i)
		aStringList.push_back(Text::toLower(*i));
}

void AutoSearchManager::on(SearchManagerListener::SR, SearchResult* sr) throw() {
	// Not searched for anything, ignore
	if (resMatch.empty())
		return;
	
	if (sr->getType() == SearchResult::TYPE_FILE)
		if (sr->getSize() < resMinSize || (resMaxSize > 0 && sr->getSize() > resMaxSize)) return;

	fullPathInLower = Text::toLower(sr->getFile());

	for(iter = resExclude.begin(); iter != resExclude.end(); ++iter)
		if (fullPathInLower.find(*iter) != string::npos) return;

	for(iter = resMatch.begin(); iter != resMatch.end(); ++iter)
		if (fullPathInLower.find(*iter) == string::npos) return;

	if (sr->getType() == SearchResult::TYPE_FILE && !resExtensions.empty()) {
		extension = Util::getFileExt(fullPathInLower);
	
		if (extension == Util::emptyString) return;

		for(iter = resExtensions.begin(); iter != resExtensions.end(); ++iter)
			if (extension == *iter) break;
			else if (iter + 1 == resExtensions.end()) return;
	}

	// Got a hit, Notify
	// Fixme, some better way of notifying
	LogManager::getInstance()->message("Autosearch Result. File " + sr->getFile() + " from " + sr->getUser()->getFirstNick() + " in " + sr->getHubName());
}

void AutoSearchManager::Load() {
	Lock l(cs);
	// Clear current
	collection.clear();

	// Load file as a string
	try {
		SimpleXML xml;
		xml.fromXML(File(getConfigFile(), File::READ, File::OPEN).read());

		if(xml.findChild("AutoSearch")) {
			xml.stepIn();

			// Predicted several groups of searches to be differentiated
			// in multiple categories. Not implemented yet.
			if(xml.findChild("SearchGroup")) {
				xml.stepIn();

				// Loop until no more searches found
				while(xml.findChild("Search")) {
					xml.stepIn();

					// Found another search, load it
					AutoSearch search;

					if(xml.findChild("SearchString"))
						search.searchString = xml.getChildData();

					if(xml.findChild("SourceType"))
						search.sourceType = Util::toInt(xml.getChildData());

					if(xml.findChild("SizeMode"))
						search.sizeMode = Util::toInt(xml.getChildData());

					if(xml.findChild("Size"))
						search.size = Util::toInt64(xml.getChildData());

					if(xml.findChild("SizeType"))
						search.typeFileSize =Util::toInt(xml.getChildData());

					if(xml.findChild("OnlyIfOp"))
						search.onlyIfOp = (Util::toInt(xml.getChildData()) != 0);

					if(xml.findChild("IsActive"))
						search.isActive = (Util::toInt(xml.getChildData()) != 0);

					if(xml.findChild("Matches"))
						search.resultsMatch = xml.getChildData();

					if(xml.findChild("Excludes"))
						search.resultsExclude = xml.getChildData();

					if(xml.findChild("Extensions"))
						search.resultsExtensions = xml.getChildData();

					if(xml.findChild("ResMinSize"))
						search.resultsMinSize = Util::toInt64(xml.getChildData());

					if(xml.findChild("ResMaxSize"))
						search.resultsMaxSize = Util::toInt64(xml.getChildData());

					if(xml.findChild("ResSizeType"))
						search.resultsTypeFileSize = Util::toInt(xml.getChildData());

					// Add search to collection
					if(search.searchString.size() > 0)
						collection.push_back(search);

					// Go to next search
					xml.stepOut();
				}
			}
		}
	} catch(const SimpleXMLException&) {
		return;
	} catch(const FileException&) {
		return;
	}
}

void AutoSearchManager::Save() {
	Lock l(cs);
	// Prepare xml string for saving
	try {
		SimpleXML xml;

		xml.addTag("AutoSearch");
		xml.stepIn();

		// Predicted several groups of searches to be differentiated
		// in multiple categories. Not implemented yet.
		xml.addTag("SearchGroup");
		xml.stepIn();

		// Save all	searches
		for(AutoSearchCollection::iterator i = collection.begin(); i != collection.end(); ++i) {
			AutoSearch& search = *i;
			if(search.searchString.size() == 0) {
				continue;
			}
			string type = "type";
			xml.addTag("Search");
			xml.stepIn();

			xml.addTag("SearchString", search.searchString);
			xml.addChildAttrib(type, string("string"));

			xml.addTag("SourceType", search.sourceType);
			xml.addChildAttrib(type, string("int"));

			xml.addTag("SizeMode", search.sizeMode);
			xml.addChildAttrib(type, string("int"));

			xml.addTag("Size", search.size);
			xml.addChildAttrib(type, string("int64"));

			xml.addTag("SizeType", search.typeFileSize);
			xml.addChildAttrib(type, string("int"));

			xml.addTag("OnlyIfOp", search.onlyIfOp);
			xml.addChildAttrib(type, string("bool"));

			xml.addTag("IsActive", search.isActive);
			xml.addChildAttrib(type, string("bool"));

			xml.addTag("Matches", search.resultsMatch);
			xml.addChildAttrib(type, string("string"));

			xml.addTag("Excludes", search.resultsExclude);
			xml.addChildAttrib(type, string("string"));

			xml.addTag("Extensions", search.resultsExtensions);
			xml.addChildAttrib(type, string("string"));

			xml.addTag("ResMinSize", search.resultsMinSize);
			xml.addChildAttrib(type, string("int64"));

			xml.addTag("ResMaxSize", search.resultsMaxSize);
			xml.addChildAttrib(type, string("int64"));

			xml.addTag("ResSizeType", search.resultsTypeFileSize);
			xml.addChildAttrib(type, string("int"));

			xml.stepOut();
		}

		xml.stepOut();

		xml.stepOut();

		// Save string to file			
		try {
			File fout(getConfigFile(), File::WRITE, File::CREATE | File::TRUNCATE);
			fout.write(SimpleXML::utf8Header);
			fout.write(xml.toXML());
			fout.close();
		} catch(const FileException&) {
			return;
		}
	} catch(const SimpleXMLException&) {
		return;
	}
}