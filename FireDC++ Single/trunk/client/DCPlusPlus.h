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

#if !defined(DC_PLUS_PLUS_H)
#define DC_PLUS_PLUS_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _WIN32
#define snprintf _snprintf
#endif

#ifdef _DEBUG

inline void CDECL debugTrace(const char* format, ...)
{
	va_list args;
	va_start(args, format);

#ifdef _WIN32
	char buf[512];

	_vsnprintf(buf, sizeof(buf), format, args);
	OutputDebugStringA(buf);
#else // _WIN32
	vprintf(format, args);
#endif // _WIN32
	va_end(args);
}

#define dcdebug debugTrace
#ifdef _WIN32
#define dcassert(exp) \
do { if (!(exp)) { \
	dcdebug("Assertion hit in %s(%d): " #exp "\n", __FILE__, __LINE__); \
	if(1 == _CrtDbgReport(_CRT_ASSERT, __FILE__, __LINE__, NULL, #exp)) \
_CrtDbgBreak(); } } while(false)
#define dcasserta(exp) dcassert(0)
#else
#include <assert.h>
#define dcasserta(exp) assert(exp)
#define dcassert(exp) assert(exp)
#endif
#define dcdrun(exp) exp
#else //_DEBUG
#ifdef _WIN32
#define dcasserta(exp) __assume(exp)
#else
#define dcasserta(exp)
#endif // _WIN32
#define dcdebug if (false) printf
#define dcassert(exp)
#define dcdrun(exp)
#endif //_DEBUG

// Make sure we're using the templates from algorithm...
#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

typedef vector<string> StringList;
typedef StringList::iterator StringIter;
typedef StringList::const_iterator StringIterC;

typedef pair<string, string> StringPair;
typedef vector<StringPair> StringPairList;
typedef StringPairList::iterator StringPairIter;

typedef HASH_MAP<string, string> StringMap;
typedef StringMap::iterator StringMapIter;

typedef HASH_SET<string> StringSet;
typedef StringSet::iterator StringSetIter;

typedef vector<wstring> WStringList;
typedef WStringList::iterator WStringIter;
typedef WStringList::const_iterator WStringIterC;

typedef pair<wstring, wstring> WStringPair;
typedef vector<WStringPair> WStringPairList;
typedef WStringPairList::iterator WStringPairIter;

#if defined(_MSC_VER)
#define _LL(x) x##ll
#define _ULL(x) x##ull
#define I64_FMT "%I64d"
#define U64_FMT "%I64d"

#elif defined(SIZEOF_LONG) && SIZEOF_LONG == 8
#define _LL(x) x##l
#define _ULL(x) x##ul
#define I64_FMT "%ld"
#define U64_FMT "%ld"
#else
#define _LL(x) x##ll
#define _ULL(x) x##ull
#define I64_FMT "%lld"
#define U64_FMT "%lld"
#endif

#ifdef _WIN32

# define PATH_SEPARATOR '\\'
# define PATH_SEPARATOR_STR "\\"

#else

# define PATH_SEPARATOR '/'
# define PATH_SEPARATOR_STR "/"

#endif


typedef HASH_MAP<wstring, wstring> WStringMap;
typedef WStringMap::iterator WStringMapIter;

#ifdef UNICODE

typedef wstring tstring;
typedef WStringList TStringList;
typedef WStringIter TStringIter;

typedef WStringPair TStringPair;
typedef WStringPairIter TStringPairIter;
typedef WStringPairList TStringPairList;

typedef WStringMap TStringMap;
typedef WStringMapIter TStringMapIter;
#else
typedef string tstring;
typedef StringList TStringList;
typedef StringIter TStringIter;

typedef StringPair TStringPair;
typedef StringPairIter TStringPairIter;
typedef StringPairList TStringPairList;

typedef StringMap TStringMap;
typedef StringMapIter TStringMapIter;
#endif

extern void startup(void (*f)(void*, const string&), void* p);
extern void shutdown();

#endif // !defined(DC_PLUS_PLUS_H)
