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

#if !defined(RESOURCE_MANAGER_H)
#define RESOURCE_MANAGER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Singleton.h"

class ResourceManager : public Singleton<ResourceManager> {
public:

#include "StringDefs.h"

	void loadLanguage(const string& aFile);
	const string& getString(Strings x) const { /*dcassert(x >= 0 && x < LAST);*/ return strings[x]; };
	const wstring& getStringW(Strings x) const { /*dcassert(x >= 0 && x < LAST);*/ return wstrings[x]; };
	bool isRTL() { return rtl; }

//FireDC++ start
	const string& getStringTwo(StringsTwo x) const { /*dcassert(x >= 0 && x < LASTTWO);*/ return stringsTwo[x]; };
	const wstring& getStringTwoW(StringsTwo x) const { /*dcassert(x >= 0 && x < LASTTWO);*/ return wstringsTwo[x]; };
//FireDC++ end
private:
	friend class Singleton<ResourceManager>;

	typedef HASH_MAP<string, Strings> NameMap;
	typedef NameMap::iterator NameIter;

//FireDC++ start
	typedef HASH_MAP<string, StringsTwo> NameMapTwo;
	typedef NameMapTwo::iterator NameIterTwo;
//FireDC++ end

	ResourceManager() : rtl(false) {
		createWide();
//FireDC++ start
		createWideTwo();
//FireDC++ end
	};
	virtual ~ResourceManager() { }

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


#define STRING(x) ResourceManager::getInstance()->getString(ResourceManager::x)
#define CSTRING(x) ResourceManager::getInstance()->getString(ResourceManager::x).c_str()
#define WSTRING(x) ResourceManager::getInstance()->getStringW(ResourceManager::x)
#define CWSTRING(x) ResourceManager::getInstance()->getStringW(ResourceManager::x).c_str()

//FireDC++ start
#define STRINGTWO(x) ResourceManager::getInstance()->getStringTwo(ResourceManager::x)
#define CSTRINGTWO(x) ResourceManager::getInstance()->getStringTwo(ResourceManager::x).c_str()
#define WSTRINGTWO(x) ResourceManager::getInstance()->getStringTwoW(ResourceManager::x)
#define CWSTRINGTWO(x) ResourceManager::getInstance()->getStringTwoW(ResourceManager::x).c_str()
//FireDC++ end

#define STRING_I(x) ResourceManager::getInstance()->getString(x)
#define CSTRING_I(x) ResourceManager::getInstance()->getString(x).c_str()
#define WSTRING_I(x) ResourceManager::getInstance()->getStringW(x)
#define CWSTRING_I(x) ResourceManager::getInstance()->getStringW(x).c_str()

//FireDC++ start
#define STRINGTWO_I(x) ResourceManager::getInstance()->getStringTwo(x)
#define CSTRINGTWO_I(x) ResourceManager::getInstance()->getStringTwo(x).c_str()
#define WSTRINGTWO_I(x) ResourceManager::getInstance()->getStringTwoW(x)
#define CWSTRINGTWO_I(x) ResourceManager::getInstance()->getStringTwoW(x).c_str()
//FireDC++ end

#ifdef UNICODE
#define TSTRING WSTRING
#define CTSTRING CWSTRING
#define CTSTRING_I CWSTRING_I

//FireDC++ start
#define TSTRINGTWO WSTRINGTWO
#define CTSTRINGTWO CWSTRINGTWO
#define CTSTRINGTWO_I CWSTRINGTWO_I
//FireDC++ end

#else
#define TSTRING STRING
#define CTSTRING CSTRING

//FireDC++ start
#define TSTRINGTWO STRINGTWO
#define CTSTRINGTWO CSTRINGTWO
//FireDC++ end

#endif


#endif // !defined(RESOURCE_MANAGER_H)
