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

#if !defined(HASH_VALUE_H)
#define HASH_VALUE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FastAlloc.h"

template<class Hasher>
struct HashValue : FastAlloc<HashValue<Hasher> >{
	static const size_t SIZE = Hasher::HASH_SIZE;

	struct Hash {
#ifdef _MSC_VER
		static const size_t bucket_size = 4;
		static const size_t min_buckets = 8;
#endif
		size_t operator()(const HashValue& rhs) const { return *(size_t*)&rhs; }
		bool operator()(const HashValue& a, const HashValue& b) const { return a < b; }
	};

	HashValue() { }
	explicit HashValue(uint8_t* aData) { memcpy(data, aData, SIZE); }
	explicit HashValue(const string& base32) { Encoder::fromBase32(base32.c_str(), data, SIZE); }
	HashValue(const HashValue& rhs) { memcpy(data, rhs.data, SIZE); }
	HashValue& operator=(const HashValue& rhs) { memcpy(data, rhs.data, SIZE); return *this; }
	bool operator!=(const HashValue& rhs) const { return !(*this == rhs); }
	bool operator==(const HashValue& rhs) const { return memcmp(data, rhs.data, SIZE) == 0; }
	bool operator<(const HashValue& rhs) const { return memcmp(data, rhs.data, SIZE) < 0; }

	string toBase32() const { return Encoder::toBase32(data, SIZE); }
	string& toBase32(string& tmp) const { return Encoder::toBase32(data, SIZE, tmp); }

	uint8_t data[SIZE];
};

#endif // !defined(HASH_VALUE_H)
