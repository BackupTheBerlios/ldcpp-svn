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

#include "Fire-SettingsManager.h"
#include "Fire-ResourceManager.h"

#include "../../client/SimpleXML.h"
#include "../../client/Util.h"
#include "../../client/File.h"

const string FireSettingsManager::settingTags[] =
{
	// Strings
	"FireLanguageFileLocation",
//FireDC++ start
	"BeepFile", "BeginFile", "FinishedFile", "SourceFile", "UploadFile", "ChatNameFile", 
	"SoundTTH", "SoundException", "SoundHubConnected", "SoundHubDisconnected", "SoundFavUserOnline",
	"SonURLFile", "StartUploadFile", "SoundTypingNotify", 
//FireDC++ end
	"SENTRY", 
	// Ints
//FireDC++ start
	//Sound stuff
	"DownloadBeginsSoundActive", "DownloadFinishedSoundActive", "SourceAddedSoundActive", 
	"UploadFinishedSoundActive", "PmSoundActive", "MynickSoundActive", 
	"TthInvalidSoundActive", "ExceptionSoundActive", "HubConnectedSoundActive", 
	"HubDisconnectedSoundActive", "FavuserOnlineSoundActive", "UrlClickSoundActive", 
	"StartUploadSoundActive", "SoundTypingNotifyActive", 
	"SoundsDisabled",
	"PrivateMessageBeep", "PrivateMessageBeepOpen",
//FireDC++ end
	"SENTRY",
	// Int64
	"aInt64",
	"SENTRY"
};

FireSettingsManager::FireSettingsManager()
{
	for(int i=0; i<SETTINGS_LAST; i++)
		isSet[i] = false;

	for(int j=0; j<INT_LAST-INT_FIRST; j++) {
		intDefaults[j] = 0;
		intSettings[j] = 0;
	}
	for(int k=0; k<INT64_LAST-INT64_FIRST; k++) {
		int64Defaults[k] = 0;
		int64Settings[k] = 0;
	}

	setDefault(FIRE_LANGUAGE_FILE, "testing");

	//FireDC++ start
	setDefault(DOWNLOAD_BEGINS_SOUND_ACTIVE, false);
	setDefault(DOWNLOAD_FINISHED_SOUND_ACTIVE, false);
	setDefault(SOURCE_ADDED_SOUND_ACTIVE, false);
	setDefault(UPLOAD_FINISHED_SOUND_ACTIVE, false);
	setDefault(PM_SOUND_ACTIVE, false);
	setDefault(MYNICK_SOUND_ACTIVE, false);
	setDefault(TTH_INVALID_SOUND_ACTIVE, false);
	setDefault(EXCEPTION_SOUND_ACTIVE, false);
	setDefault(HUB_CONNECTED_SOUND_ACTIVE, false);
	setDefault(HUB_DISCONNECTED_SOUND_ACTIVE, false);
	setDefault(FAVUSER_ONLINE_SOUND_ACTIVE, false);
	setDefault(URL_CLICK_SOUND_ACTIVE, false);
	setDefault(START_UPLOAD_SOUND_ACTIVE, false);
	setDefault(SOUND_TYPING_NOTIFY_ACTIVE, false);
	setDefault(SOUNDS_DISABLED, false);

	setDefault(PRIVATE_MESSAGE_BEEP, false);
	setDefault(PRIVATE_MESSAGE_BEEP_OPEN, false);
//FireDC++ end

#ifdef _WIN32
#endif
}

void FireSettingsManager::load(string const& aFileName)
{
	try {
		SimpleXML xml;
		
		xml.fromXML(File(aFileName, File::READ, File::OPEN).read());
		
		xml.resetCurrentChild();
		
		xml.stepIn();
		
		if(xml.findChild("FireSettings"))
		{
			xml.stepIn();

			int i;
			
			for(i=STR_FIRST; i<STR_LAST; i++)
			{
				const string& attr = settingTags[i];
				dcassert(attr.find("SENTRY") == string::npos);
				
				if(xml.findChild(attr))
					set(StrSetting(i), xml.getChildData());
				xml.resetCurrentChild();
			}
			for(i=INT_FIRST; i<INT_LAST; i++)
			{
				const string& attr = settingTags[i];
				dcassert(attr.find("SENTRY") == string::npos);
				
				if(xml.findChild(attr))
					set(IntSetting(i), Util::toInt(xml.getChildData()));
				xml.resetCurrentChild();
			}
			for(i=INT64_FIRST; i<INT64_LAST; i++)
			{
				const string& attr = settingTags[i];
				dcassert(attr.find("SENTRY") == string::npos);
				
				if(xml.findChild(attr))
					set(Int64Setting(i), Util::toInt64(xml.getChildData()));
				xml.resetCurrentChild();
			}
			
			xml.stepOut();
		}
	
		fire(FireSettingsManagerListener::Load(), xml);
//		fire(FireSettingsManagerListener::Load(), &xml);
		xml.stepOut();

	} catch(const Exception&) {
	}
}

void FireSettingsManager::save(string const& aFileName) {

	SimpleXML xml;
	xml.addTag("Fire");
	xml.stepIn();
	xml.addTag("FireSettings");
	xml.stepIn();

	int i;
	string type("type"), curType("string");
	
	for(i=STR_FIRST; i<STR_LAST; i++)
	{
		if(isSet[i]) {
			xml.addTag(settingTags[i], get(StrSetting(i), false));
			xml.addChildAttrib(type, curType);
		}
	}

	curType = "int";
	for(i=INT_FIRST; i<INT_LAST; i++)
	{
		if(isSet[i]) {
			xml.addTag(settingTags[i], get(IntSetting(i), false));
			xml.addChildAttrib(type, curType);
		}
	}
	curType = "int64";
	for(i=INT64_FIRST; i<INT64_LAST; i++)
	{
		if(isSet[i])
		{
			xml.addTag(settingTags[i], get(Int64Setting(i), false));
			xml.addChildAttrib(type, curType);
		}
	}
	xml.stepOut();
	
	fire(FireSettingsManagerListener::Save(), xml);
//	fire(FireSettingsManagerListener::Save(), &xml);

	try {
		File out(aFileName + ".tmp", File::WRITE, File::CREATE | File::TRUNCATE);
		BufferedOutputStream<false> f(&out);
		f.write(SimpleXML::utf8Header);
		xml.toXML(&f);
		f.flush();
		out.close();
		File::deleteFile(aFileName);
		File::renameFile(aFileName + ".tmp", aFileName);
	} catch(const FileException&) {
		// ...
	}
}
