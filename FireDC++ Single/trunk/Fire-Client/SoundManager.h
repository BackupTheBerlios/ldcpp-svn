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

#include "../client/File.h"
#include "../client/CriticalSection.h"
#include "../client/Singleton.h"
#include "../client/TimerManager.h"
#include "../Fire-Client/dcplusplus-rips/Fire-SettingsManager.h"

class SoundManager : public Singleton<SoundManager>
{
public:
	enum SoundArea { DOWNLOAD_BEGINS, DOWNLOAD_FINISHED, SOURCE_ADDED, UPLOAD_FINISHED, PM, MYNICK, TTH_INVALID, EXCEPTION, HUB_CONNECTED, HUB_DISCONNECTED, FAVUSER_ONLINE, URL_CLICK, START_UPLOAD, TYPING_NOTIFY, LAST };
	enum {FILE, ACTIVE};

	void sound(SoundArea area) throw() {
		if (!FIREBOOLSETTING(SOUNDS_DISABLED)) {
			if (getBoolSetting(area, ACTIVE)) {
				if (!getSetting(area, FILE).empty()) {
					PlaySound(Text::toT(getSetting(area, FILE)).c_str(), NULL, SND_FILENAME | SND_ASYNC);
				}
			}
		}
	}

	const string& getSetting(int area, int sel) {
		return FireSettingsManager::getInstance()->get(static_cast<FireSettingsManager::StrSetting>(soundOptions[area][sel]), true);
	}

	const bool getBoolSetting(int area, int sel) {
		return FireSettingsManager::getInstance()->getBool(static_cast<FireSettingsManager::IntSetting>(soundOptions[area][sel]), true);
	}

	void saveSetting(int area, int sel, const string& setting) {
		FireSettingsManager::getInstance()->set(static_cast<FireSettingsManager::StrSetting>(soundOptions[area][sel]), setting);
	}

private:
	friend class Singleton<SoundManager>;
	CriticalSection cs;

	int soundOptions[LAST][2];

	SoundManager() {
		soundOptions[DOWNLOAD_BEGINS][FILE]		= FireSettingsManager::BEGINFILE;
		soundOptions[DOWNLOAD_BEGINS][ACTIVE]	= FireSettingsManager::DOWNLOAD_BEGINS_SOUND_ACTIVE;
        soundOptions[DOWNLOAD_FINISHED][FILE]	= FireSettingsManager::FINISHFILE;
		soundOptions[DOWNLOAD_FINISHED][ACTIVE]	= FireSettingsManager::DOWNLOAD_FINISHED_SOUND_ACTIVE;
		soundOptions[SOURCE_ADDED][FILE]		= FireSettingsManager::SOURCEFILE;
		soundOptions[SOURCE_ADDED][ACTIVE]		= FireSettingsManager::SOURCE_ADDED_SOUND_ACTIVE;
		soundOptions[UPLOAD_FINISHED][FILE]		= FireSettingsManager::UPLOADFILE;
		soundOptions[UPLOAD_FINISHED][ACTIVE]	= FireSettingsManager::UPLOAD_FINISHED_SOUND_ACTIVE;
		soundOptions[PM][FILE]					= FireSettingsManager::BEEPFILE;
		soundOptions[PM][ACTIVE]				= FireSettingsManager::PM_SOUND_ACTIVE;
		soundOptions[MYNICK][FILE]				= FireSettingsManager::CHATNAMEFILE;			// Add the one in ChatCtrl.cpp
		soundOptions[MYNICK][ACTIVE]			= FireSettingsManager::MYNICK_SOUND_ACTIVE;		// Add the one in ChatCtrl.cpp
		soundOptions[TTH_INVALID][FILE]			= FireSettingsManager::SOUND_TTH;
		soundOptions[TTH_INVALID][ACTIVE]		= FireSettingsManager::TTH_INVALID_SOUND_ACTIVE;
		soundOptions[EXCEPTION][FILE]			= FireSettingsManager::SOUND_EXC;
		soundOptions[EXCEPTION][ACTIVE]			= FireSettingsManager::EXCEPTION_SOUND_ACTIVE;
		soundOptions[HUB_CONNECTED][FILE]		= FireSettingsManager::SOUND_HUBCON;
		soundOptions[HUB_CONNECTED][ACTIVE]		= FireSettingsManager::HUB_CONNECTED_SOUND_ACTIVE;
		soundOptions[HUB_DISCONNECTED][FILE]	= FireSettingsManager::SOUND_HUBDISCON;
		soundOptions[HUB_DISCONNECTED][ACTIVE]	= FireSettingsManager::HUB_DISCONNECTED_SOUND_ACTIVE;
		soundOptions[FAVUSER_ONLINE][FILE]		= FireSettingsManager::SOUND_FAVUSER;
		soundOptions[FAVUSER_ONLINE][ACTIVE]	= FireSettingsManager::FAVUSER_ONLINE_SOUND_ACTIVE;
		soundOptions[URL_CLICK][FILE]			= FireSettingsManager::SONURLFILE;				// Add the one in HubFrame.cpp/PrivateFrame.cpp
		soundOptions[URL_CLICK][ACTIVE]			= FireSettingsManager::URL_CLICK_SOUND_ACTIVE;	// Add the one in HubFrame.cpp/PrivateFrame.cpp
		soundOptions[START_UPLOAD][FILE]		= FireSettingsManager::STARTUPLOADFILE;
		soundOptions[START_UPLOAD][ACTIVE]		= FireSettingsManager::START_UPLOAD_SOUND_ACTIVE;
		soundOptions[TYPING_NOTIFY][FILE]		= FireSettingsManager::SOUND_TYPING_NOTIFY;
		soundOptions[TYPING_NOTIFY][ACTIVE]		= FireSettingsManager::SOUND_TYPING_NOTIFY_ACTIVE;
	};
	virtual ~SoundManager() throw() { };
};

#define SOUND(area) SoundManager::getInstance()->sound(area)

#endif // !defined(AFX_SOUNDMANAGER_H__73C7E0F5_5C7D_4A2A_827B_53267D0EF4C5__INCLUDED_)

/**
 * @file
 * $Id: SoundManager.h,v 1.16 2005/01/06 18:19:48 Virus27 Exp $
 */
