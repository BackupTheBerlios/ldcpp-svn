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

#if !defined(FIRE_SETTINGS_MANAGER_H)
#define FIRE_SETTINGS_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../client/Util.h"
#include "../../client/Speaker.h"
#include "../../client/Singleton.h"

class SimpleXML;

class FireSettingsManagerListener {
public:
	virtual ~FireSettingsManagerListener() { }
	template<int I>	struct X { enum { TYPE = I };  };

	typedef X<0> Load;
	typedef X<1> Save;

//	virtual void on(Load, SimpleXML*) throw() { }
//	virtual void on(Save, SimpleXML*) throw() { }
	virtual void on(Load, SimpleXML&) throw() { }
	virtual void on(Save, SimpleXML&) throw() { }
};

class FireSettingsManager : public Singleton<FireSettingsManager>, public Speaker<FireSettingsManagerListener>
{
public:

	enum StrSetting { STR_FIRST,
		FIRE_LANGUAGE_FILE = STR_FIRST,
//FireDC++ start
		BEEPFILE, BEGINFILE, FINISHFILE, SOURCEFILE, UPLOADFILE, CHATNAMEFILE, 
		SOUND_TTH, SOUND_EXC, SOUND_HUBCON, SOUND_HUBDISCON, SOUND_FAVUSER,
		SONURLFILE, STARTUPLOADFILE, SOUND_TYPING_NOTIFY, 
//FireDC++ end
		STR_LAST };

	enum IntSetting { INT_FIRST = STR_LAST + 1, 
//FireDC++ start
		//Sound stuff
		DOWNLOAD_BEGINS_SOUND_ACTIVE = INT_FIRST, DOWNLOAD_FINISHED_SOUND_ACTIVE, 
		SOURCE_ADDED_SOUND_ACTIVE, 
		UPLOAD_FINISHED_SOUND_ACTIVE, PM_SOUND_ACTIVE, MYNICK_SOUND_ACTIVE, 
		TTH_INVALID_SOUND_ACTIVE, EXCEPTION_SOUND_ACTIVE, HUB_CONNECTED_SOUND_ACTIVE, 
		HUB_DISCONNECTED_SOUND_ACTIVE, FAVUSER_ONLINE_SOUND_ACTIVE, URL_CLICK_SOUND_ACTIVE, 
		START_UPLOAD_SOUND_ACTIVE, SOUND_TYPING_NOTIFY_ACTIVE, 
		SOUNDS_DISABLED,
		PRIVATE_MESSAGE_BEEP, PRIVATE_MESSAGE_BEEP_OPEN,
//FireDC++ end
		INT_LAST };

	enum Int64Setting { INT64_FIRST = INT_LAST + 1,
		AINT64 = INT64_FIRST, INT64_LAST, SETTINGS_LAST = INT64_LAST };

	const string& get(StrSetting key, bool useDefault = true) const {
		return (isSet[key] || !useDefault) ? strSettings[key - STR_FIRST] : strDefaults[key - STR_FIRST];
	}

	int get(IntSetting key, bool useDefault = true) const {
		return (isSet[key] || !useDefault) ? intSettings[key - INT_FIRST] : intDefaults[key - INT_FIRST];
	}
	int64_t get(Int64Setting key, bool useDefault = true) const {
		return (isSet[key] || !useDefault) ? int64Settings[key - INT64_FIRST] : int64Defaults[key - INT64_FIRST];
	}

	bool getBool(IntSetting key, bool useDefault = true) const {
		return (get(key, useDefault) != 0);
	}

	void set(StrSetting key, string const& value) {
		strSettings[key - STR_FIRST] = value;
		isSet[key] = !value.empty();
	}

	void set(IntSetting key, int value) {
		intSettings[key - INT_FIRST] = value;
		isSet[key] = true;
	}

	void set(IntSetting key, const string& value) {
		if(value.empty()) {
			intSettings[key - INT_FIRST] = 0;
			isSet[key] = false;
		} else {
			intSettings[key - INT_FIRST] = Util::toInt(value);
			isSet[key] = true;
		}
	}

	void set(Int64Setting key, int64_t value) {
		int64Settings[key - INT64_FIRST] = value;
		isSet[key] = true;
	}

	void set(Int64Setting key, const string& value) {
		if(value.empty()) {
			int64Settings[key - INT64_FIRST] = 0;
			isSet[key] = false;
		} else {
			int64Settings[key - INT64_FIRST] = Util::toInt64(value);
			isSet[key] = true;
		}
	}

	void set(IntSetting key, bool value) { set(key, (int)value); }

	void setDefault(StrSetting key, string const& value) {
		strDefaults[key - STR_FIRST] = value;
	}

	void setDefault(IntSetting key, int value) {
		intDefaults[key - INT_FIRST] = value;
	}
	void setDefault(Int64Setting key, int64_t value) {
		int64Defaults[key - INT64_FIRST] = value;
	}

	bool isDefault(int aSet) { return !isSet[aSet]; }

	void load() {
		load(Util::getConfigPath() + "Fire.xml");
	}
	void save() {
		save(Util::getConfigPath() + "Fire.xml");
	}

	void load(const string& aFileName);
	void save(const string& aFileName);

private:
	friend class Singleton<FireSettingsManager>;
	FireSettingsManager();
	virtual ~FireSettingsManager() throw() { }

	static const string settingTags[SETTINGS_LAST+1];

	string strSettings[STR_LAST - STR_FIRST];
	int    intSettings[INT_LAST - INT_FIRST];
	int64_t int64Settings[INT64_LAST - INT64_FIRST];
	string strDefaults[STR_LAST - STR_FIRST];
	int    intDefaults[INT_LAST - INT_FIRST];
	int64_t int64Defaults[INT64_LAST - INT64_FIRST];
	bool isSet[SETTINGS_LAST];
};

// Shorthand accessor macros
#define FIRESETTING(k) (FireSettingsManager::getInstance()->get(FireSettingsManager::k, true))
#define FIREBOOLSETTING(k) (FireSettingsManager::getInstance()->getBool(FireSettingsManager::k, true))

#endif // !defined(FIRE_SETTINGS_MANAGER_H)
