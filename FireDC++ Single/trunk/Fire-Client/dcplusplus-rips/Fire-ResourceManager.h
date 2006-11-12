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

#if !defined(FIRE_RESOURCE_MANAGER_H)
#define FIRE_RESOURCE_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../client/Singleton.h"

class FireResourceManager : public Singleton<FireResourceManager> {
public:
	
#include "Fire-StringDefs.h"

	void loadLanguage(const string& aFile);
	const string& getString(FireStrings x) const { dcassert(x >= 0 && x < LAST); return strings[x]; }
	const wstring& getStringW(FireStrings x) const { dcassert(x >= 0 && x < LAST); return wstrings[x]; }
	bool isRTL() { return rtl; }

//FireDC++ start
	const string& getStringTwo(FireStringsTwo x) const { dcassert(x >= 0 && x < LASTTWO); return stringsTwo[x]; };
	const wstring& getStringTwoW(FireStringsTwo x) const { dcassert(x >= 0 && x < LASTTWO); return wstringsTwo[x]; };
//FireDC++ end
private:
	friend class Singleton<FireResourceManager>;
	
	typedef HASH_MAP<string, FireStrings> NameMap;
	typedef NameMap::iterator NameIter;

//FireDC++ start
	typedef HASH_MAP<string, FireStringsTwo> NameMapTwo;
	typedef NameMapTwo::iterator NameIterTwo;
//FireDC++ end

	FireResourceManager(): rtl(false) {
		createWide();
//FireDC++ start
		createWideTwo();
//FireDC++ end
	};
	virtual ~FireResourceManager() { }
	
	static string strings[LAST];
	static wstring wstrings[LAST];
	static string names[LAST];

	bool rtl;

//FireDC++ start
	static string stringsTwo[LASTTWO];
	static wstring wstringsTwo[LASTTWO];
	static string namesTwo[LASTTWO];
//FireDC++ end

	void createWide();
//FireDC++ start
	void createWideTwo();
//FireDC++ end
};


#define FIRESTRING(x) FireResourceManager::getInstance()->getString(FireResourceManager::x)
#define FIRECSTRING(x) FireResourceManager::getInstance()->getString(FireResourceManager::x).c_str()
#define FIREWSTRING(x) FireResourceManager::getInstance()->getStringW(FireResourceManager::x)
#define FIRECWSTRING(x) FireResourceManager::getInstance()->getStringW(FireResourceManager::x).c_str()

//FireDC++ start
#define FIRESTRINGTWO(x) FireResourceManager::getInstance()->getStringTwo(FireResourceManager::x)
#define FIRECSTRINGTWO(x) FireResourceManager::getInstance()->getStringTwo(FireResourceManager::x).c_str()
#define FIREWSTRINGTWO(x) FireResourceManager::getInstance()->getStringTwoW(FireResourceManager::x)
#define FIRECWSTRINGTWO(x) FireResourceManager::getInstance()->getStringTwoW(FireResourceManager::x).c_str()
//FireDC++ end

#define FIRESTRING_I(x) FireResourceManager::getInstance()->getString(x)
#define FIRECSTRING_I(x) FireResourceManager::getInstance()->getString(x).c_str()
#define FIREWSTRING_I(x) FireResourceManager::getInstance()->getStringW(x)
#define FIRECWSTRING_I(x) FireResourceManager::getInstance()->getStringW(x).c_str()

//FireDC++ start
#define FIRESTRINGTWO_I(x) FireResourceManager::getInstance()->getStringTwo(x)
#define FIRECSTRINGTWO_I(x) FireResourceManager::getInstance()->getStringTwo(x).c_str()
#define FIREWSTRINGTWO_I(x) FireResourceManager::getInstance()->getStringTwoW(x)
#define FIRECWSTRINGTWO_I(x) FireResourceManager::getInstance()->getStringTwoW(x).c_str()
//FireDC++ end

#ifdef UNICODE
#define FIRETSTRING FIREWSTRING
#define FIRECTSTRING FIRECWSTRING
#define FIRECTSTRING_I FIRECWSTRING_I

//FireDC++ start
#define FIRETSTRINGTWO FIREWSTRINGTWO
#define FIRECTSTRINGTWO FIRECWSTRINGTWO
#define FIRECTSTRINGTWO_I FIRECWSTRINGTWO_I
//FireDC++ end

#else
#define FIRETSTRING FIRESTRING
#define FIRECTSTRING FIRECSTRING

//FireDC++ start
#define FIRETSTRINGTWO FIRESTRINGTWO
#define FIRECTSTRINGTWO FIRECSTRINGTWO
//FireDC++ end

#endif


#endif // !defined(FIRE_RESOURCE_MANAGER_H)
