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

#include "stdafx.h"
#include "../client/DCPlusPlus.h"
#include "resource.h"

#include "WinUtilTwo.h"
#include "../Fire-Client/dcplusplus-rips/Fire-Version.h"
#include "../Fire-Client/dcplusplus-rips/Fire-ResourceManager.h"
#include "../Fire-Client/dcplusplus-rips/Fire-SettingsManager.h"

bool WinUtilTwo::allowMoreInstances(size_t amountOfProcesses) {
	if(amountOfProcesses == 0)
		if (::MessageBox(NULL, _T("There is already an instance of ") _T(FIREAPPNAME) _T(" running.\nDo you want to launch another instance anyway?"), _T(FIREAPPNAME) _T(" ") _T(FIREVERSIONSTRING), MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2 | MB_TOPMOST) == IDYES)
			return true;
	return false;
}

void WinUtilTwo::additionMenuStuff(CMenu& mainMenu) {
	CMenuHandle fireMenu;
	fireMenu.CreatePopupMenu();

	fireMenu.AppendMenu(MF_STRING, IDD_FIRE_ABOUT, FIRECTSTRING(MENU_FIRE_ABOUT));
	fireMenu.AppendMenu(MF_SEPARATOR);

	mainMenu.AppendMenu(MF_POPUP, (UINT_PTR)(HMENU)fireMenu, FIRECTSTRING(MENU_FIRE));
}

bool WinUtilTwo::possibleCommand(tstring cmd, tstring /*param*/, tstring& message, tstring& status) {
	if(Util::stricmp(cmd.c_str(), _T("fire")) == 0 || Util::stricmp(cmd.c_str(), _T("fire++")) == 0) {
		string tmp = "\r\nSmile and be happy. :)\r\nhttp://ldcpp.berlios.de/ <";
		tmp += FIREAPPNAME;
		tmp += " ";
		tmp += FIREVERSIONSTRING;
		tmp += ">";
		message = Text::toT(tmp);
	} else if(Util::stricmp(cmd.c_str(), _T("huh")) == 0) {
		string tmp = "\r\n\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?              huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?      huh?        huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?                         huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?                           huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?                            huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?                           huh?\r\n";
		tmp += "huh?huh?huh?huh?huh?          huh?                            huh?          huh?huh?huh?huh?huh?                       huh?\r\n";
		tmp += "huh?huh?huh?huh?huh?          huh?                            huh?          huh?huh?huh?huh?huh?                  huh?\r\n";
		tmp += "huh?huh?huh?huh?huh?          huh?                            huh?          huh?huh?huh?huh?huh?              huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?            huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?            huh?\r\n";
		tmp += "huh?                        huh?          huh?                            huh?          huh?                        huh?            huh?\r\n";
		tmp += "huh?                        huh?             huh?                       huh?            huh?                        huh?            huh?\r\n";
		tmp += "huh?                        huh?                 huh?              huh?                 huh?                        huh?\r\n";
		tmp += "huh?                        huh?                        huh?huh?                        huh?                        huh?            huh?\r\n";
	    tmp += "\r\n";
		message = Text::toT(tmp); 
	} else {
		return false;
	}
	return true;
}

void WinUtilTwo::addFireStuffToExceptionInfo(char* buf, File& aFile) {
	sprintf(buf, "Fire++ Version: %s\t %s\r\n", FIREVERSIONSTRING, FIRESVNVERSIONSTRING);
	aFile.write(buf, strlen(buf));
}