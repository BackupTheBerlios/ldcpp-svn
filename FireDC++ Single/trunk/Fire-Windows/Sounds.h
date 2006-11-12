/* 
 * Copyright (C) 2001-2004 Jacek Sieka, j_s at telia com
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

#ifndef Sounds_H
#define Sounds_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlcrack.h>
#include "../Fire-Windows/dcplusplus-rips/Fire-PropPage.h"
#include "../windows/ExListViewCtrl.h"


class Sounds : public CPropertyPage<IDD_SOUNDS>, public FirePropPage
{
public:
	Sounds(FireSettingsManager *s) : FirePropPage(s) {
		title = _tcsdup(/*(FIRETSTRINGTWO(SETTINGS_FIREDC) + _T('\\') + */FIRETSTRING(SETTINGS_SOUNDS)/*)*/.c_str());
		SetTitle(title);
	};

	~Sounds() { free(title); };

	BEGIN_MSG_MAP_EX(Sounds)
		MESSAGE_HANDLER(WM_INITDIALOG, onInitDialog)
		COMMAND_HANDLER(IDC_BROWSED, BN_CLICKED, onBrowse)
		NOTIFY_HANDLER(IDC_SOUND_OPTIONS, LVN_ITEMCHANGED, onItemChanged)
		COMMAND_ID_HANDLER(IDC_NONE, onClickedNone)
		COMMAND_ID_HANDLER(IDC_TEST, onTest)
	END_MSG_MAP()

	LRESULT onInitDialog(UINT, WPARAM, LPARAM, BOOL&);
	LRESULT onBrowse(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT onItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/);
	LRESULT onClickedNone(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT onTest(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);

	// Common PropPage interface
	PROPSHEETPAGE *getPSP() { return (PROPSHEETPAGE *)*this; }
	virtual void write();

protected:
	static Item items[];
	static TextItem texts[];
	static ListItem listItems[];
	TCHAR* title;

	ExListViewCtrl soundOptions;
	int oldSelection;
	TStringList options;
};

#endif //Sounds_H

/**
 * @file
 * $Id: Sounds.h,v 1.6 2004/10/03 09:50:15 Legolas Exp $
 */

