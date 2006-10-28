/* 
 * Copyright (C) 2001-2005 Jacek Sieka, arnetheduck on gmail point com
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

#if !defined(AFX_SOUNDMANAGER_H__73C7E0F5_5C7D_4A2A_827B_53267D0EF4C5__INCLUDED_)
#define AFX_SOUNDMANAGER_H__73C7E0F5_5C7D_4A2A_827B_53267D0EF4C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "File.h"
#include "CriticalSection.h"
#include "Singleton.h"
#include "TimerManager.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	enum SoundArea { DOWNLOAD_BEGINS, DOWNLOAD_FINISHED, SOURCE_ADDED, UPLOAD_FINISHED, PM, MYNICK, TTH_INVALID, EXCEPTION, HUB_CONNECTED, HUB_DISCONNECTED, FAVUSER_ONLINE, URL_CLICK, START_UPLOAD, TYPING_NOTIFY, LAST };
	enum {FILE, ACTIVE};

	void sound(SoundArea area) throw() {
		if (!BOOLSETTING(SOUNDS_DISABLED)) {
			if (getBoolSetting(area, ACTIVE)) {
				if (!getSetting(area, FILE).empty()) {
					PlaySound(Text::toT(getSetting(area, FILE)).c_str(), NULL, SND_FILENAME | SND_ASYNC);
				}
			}
		}
	}

	const string& getSetting(int area, int sel) {
		return SettingsManager::getInstance()->get(static_cast<SettingsManager::StrSetting>(soundOptions[area][sel]), true);
	}

	const bool getBoolSetting(int area, int sel) {
		return SettingsManager::getInstance()->getBool(static_cast<SettingsManager::IntSetting>(soundOptions[area][sel]), true);
	}

	void saveSetting(int area, int sel, const string& setting) {
		SettingsManager::getInstance()->set(static_cast<SettingsManager::StrSetting>(soundOptions[area][sel]), setting);
	}

private:
	friend class Singleton<SoundManager>;
	CriticalSection cs;

	int soundOptions[LAST][2];

	SoundManager() {
		soundOptions[DOWNLOAD_BEGINS][FILE]		= SettingsManager::BEGINFILE;
		soundOptions[DOWNLOAD_BEGINS][ACTIVE]	= SettingsManager::DOWNLOAD_BEGINS_SOUND_ACTIVE;
        soundOptions[DOWNLOAD_FINISHED][FILE]	= SettingsManager::FINISHFILE;
		soundOptions[DOWNLOAD_FINISHED][ACTIVE]	= SettingsManager::DOWNLOAD_FINISHED_SOUND_ACTIVE;
		soundOptions[SOURCE_ADDED][FILE]		= SettingsManager::SOURCEFILE;
		soundOptions[SOURCE_ADDED][ACTIVE]		= SettingsManager::SOURCE_ADDED_SOUND_ACTIVE;
		soundOptions[UPLOAD_FINISHED][FILE]		= SettingsManager::UPLOADFILE;
		soundOptions[UPLOAD_FINISHED][ACTIVE]	= SettingsManager::UPLOAD_FINISHED_SOUND_ACTIVE;
		soundOptions[PM][FILE]					= SettingsManager::BEEPFILE;
		soundOptions[PM][ACTIVE]				= SettingsManager::PM_SOUND_ACTIVE;
		soundOptions[MYNICK][FILE]				= SettingsManager::CHATNAMEFILE;			// Add the one in ChatCtrl.cpp
		soundOptions[MYNICK][ACTIVE]			= SettingsManager::MYNICK_SOUND_ACTIVE;		// Add the one in ChatCtrl.cpp
		soundOptions[TTH_INVALID][FILE]			= SettingsManager::SOUND_TTH;
		soundOptions[TTH_INVALID][ACTIVE]		= SettingsManager::TTH_INVALID_SOUND_ACTIVE;
		soundOptions[EXCEPTION][FILE]			= SettingsManager::SOUND_EXC;
		soundOptions[EXCEPTION][ACTIVE]			= SettingsManager::EXCEPTION_SOUND_ACTIVE;
		soundOptions[HUB_CONNECTED][FILE]		= SettingsManager::SOUND_HUBCON;
		soundOptions[HUB_CONNECTED][ACTIVE]		= SettingsManager::HUB_CONNECTED_SOUND_ACTIVE;
		soundOptions[HUB_DISCONNECTED][FILE]	= SettingsManager::SOUND_HUBDISCON;
		soundOptions[HUB_DISCONNECTED][ACTIVE]	= SettingsManager::HUB_DISCONNECTED_SOUND_ACTIVE;
		soundOptions[FAVUSER_ONLINE][FILE]		= SettingsManager::SOUND_FAVUSER;
		soundOptions[FAVUSER_ONLINE][ACTIVE]	= SettingsManager::FAVUSER_ONLINE_SOUND_ACTIVE;
		soundOptions[URL_CLICK][FILE]			= SettingsManager::SONURLFILE;				// Add the one in HubFrame.cpp/PrivateFrame.cpp
		soundOptions[URL_CLICK][ACTIVE]			= SettingsManager::URL_CLICK_SOUND_ACTIVE;	// Add the one in HubFrame.cpp/PrivateFrame.cpp
		soundOptions[START_UPLOAD][FILE]		= SettingsManager::STARTUPLOADFILE;
		soundOptions[START_UPLOAD][ACTIVE]		= SettingsManager::START_UPLOAD_SOUND_ACTIVE;
		soundOptions[TYPING_NOTIFY][FILE]		= SettingsManager::SOUND_TYPING_NOTIFY;
		soundOptions[TYPING_NOTIFY][ACTIVE]		= SettingsManager::SOUND_TYPING_NOTIFY_ACTIVE;
	};
	virtual ~SoundManager() throw() { };
};

#define SOUND(area) SoundManager::getInstance()->sound(area)

#endif // !defined(AFX_SOUNDMANAGER_H__73C7E0F5_5C7D_4A2A_827B_53267D0EF4C5__INCLUDED_)

/**
 * @file
 * $Id: SoundManager.h,v 1.16 2005/01/06 18:19:48 Virus27 Exp $
 */
