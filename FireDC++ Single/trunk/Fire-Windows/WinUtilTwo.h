/* 
 * Copyright (C) 2006 Michael J Jones, mrmikejj at hotmail dot com
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

#if !defined(WIN_UTIL_TWO_H)
#define WIN_UTIL_TWO_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../client/File.h"

namespace WinUtilTwo
{
	// For allowing for instances
	bool allowMoreInstances(size_t amountOfProcesses);

	void additionMenuStuff(CMenu& mainMenu);
	bool possibleCommand(tstring cmd, tstring param, tstring& message, tstring& status);
//	void winampSpam(tstring& message, tstring& status);

	void addFireStuffToExceptionInfo(char* buf, File& aFile);

//	void initilize();
};

#endif // !defined(WIN_UTIL_TWO_H)