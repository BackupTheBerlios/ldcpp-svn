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

#include "stdafx.h"
#include "../../client/DCPlusPlus.h"
#include "../resource.h"

#include "Fire-PropertiesDlg.h"
#include "../Sounds.h"

FirePropertiesDlg::FirePropertiesDlg(HWND parent, FireSettingsManager *s) : TreePropertySheet(FIRECTSTRING(FIRE_SETTINGS), 0, parent)
{
	int n = 0;

	pages[n++] = new Sounds(s);

	for(int i=0; i<numPages; i++) {
		AddPage(pages[i]->getPSP());
	}

	// Hide "Apply" button
	m_psh.dwFlags |= PSH_NOAPPLYNOW | PSH_NOCONTEXTHELP;
	m_psh.dwFlags &= ~PSH_HASHELP;
}

FirePropertiesDlg::~FirePropertiesDlg()
{
	for(int i=0; i<numPages; i++) {
		delete pages[i];
	}
}

void FirePropertiesDlg::write()
{
	for(int i=0; i<numPages; i++)
	{
		// Check HWND of page to see if it has been created
		const HWND page = PropSheet_IndexToHwnd((HWND)*this, i);

		if(page != NULL)
			pages[i]->write();
	}
}

LRESULT FirePropertiesDlg::onOK(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& bHandled)
{
	write();
	bHandled = FALSE;
	return TRUE;
}
