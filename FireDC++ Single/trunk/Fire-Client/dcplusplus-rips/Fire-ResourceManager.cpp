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

#include "stdinc.h"
#include "../../client/DCPlusPlus.h"

#include "Fire-ResourceManager.h"

#include "../../client/SimpleXML.h"
#include "../../client/File.h"
#include "../../client/Text.h"

wstring FireResourceManager::wstrings[FireResourceManager::LAST];
//FireDC++ start
wstring FireResourceManager::wstringsTwo[FireResourceManager::LASTTWO];
//FireDC++ end

void FireResourceManager::loadLanguage(const string& aFile) {
	try {
		File f(aFile, File::READ, File::OPEN);
		SimpleXML xml;
		xml.fromXML(f.read());

		HASH_MAP<string, int> h;
//FireDC++ start
		HASH_MAP<string, int> e;
		
//FireDC++ end
		for(int i = 0; i < LAST; ++i) {
			h[names[i]] = i;
		}
//FireDC++ start
		for(int i = 0; i < LASTTWO; ++i) {
			e[namesTwo[i]] = i;
		}
//FireDC++ end
		if(xml.findChild("Language")) {
			rtl = xml.getBoolChildAttrib("RightToLeft");

			xml.stepIn();
			if(xml.findChild("Strings")) {
				xml.stepIn();

				while(xml.findChild("String")) {
					HASH_MAP<string, int>::iterator j = h.find(xml.getChildAttrib("Name"));

					if(j != h.end()) {
						strings[j->second] = xml.getChildData();
					}
				}
				createWide();
			}
//FireDC++ start
			xml.stepOut();
			if(xml.findChild("StringsTwo")) {
				xml.stepIn();

				while(xml.findChild("StringTwo")) {
					HASH_MAP<string, int>::iterator j = e.find(xml.getChildAttrib("Name"));

					if(j != e.end()) {
						stringsTwo[j->second] = xml.getChildData();
					}
				}
				createWideTwo();
			}
//FireDC++ end
		}
	} catch(const Exception&) {
		// ...
	}
}

void FireResourceManager::createWide() {
	for(int i = 0; i < LAST; ++i) {
		wstrings[i].clear();
		Text::utf8ToWide(strings[i], wstrings[i]);
	}
}

//FireDC++ start
void FireResourceManager::createWideTwo() {
	for(int i = 0; i < LASTTWO; ++i) {
		wstringsTwo[i].clear();
		Text::utf8ToWide(stringsTwo[i], wstringsTwo[i]);
	}
}
//FireDC++ end
