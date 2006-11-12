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

#include "stdafx.h"
#include "../../client/DCPlusPlus.h"
#include "../../Fire-Client/dcplusplus-rips/Fire-SettingsManager.h"

#include "Fire-MainFrm.h"
#include "Fire-PropertiesDlg.h"
#include "Fire-AboutDlg.h"
//#include "Fire-NotepadFrame.h"
//#include "AutoSearchFrame.h"

#include "../../windows/WinUtil.h"

void FireMainFrame::destroyFireToolbar(CImageList& fdmLargeImages, CImageList& fdmLargeImagesHot) {
	fdmLargeImages.Destroy();
	fdmLargeImagesHot.Destroy();
}

HWND FireMainFrame::createFireToolbar(CImageList& fdmLargeImages, CImageList& fdmLargeImagesHot) {
	CToolBarCtrl ctrlToolbar;
	fdmLargeImages.CreateFromImage(IDB_FIRE_TOOLBAR20, 20, 15, CLR_DEFAULT, IMAGE_BITMAP, LR_CREATEDIBSECTION | LR_SHARED);
	fdmLargeImagesHot.CreateFromImage(IDB_FIRE_TOOLBAR20_HOT, 20, 15, CLR_DEFAULT, IMAGE_BITMAP, LR_CREATEDIBSECTION | LR_SHARED);

	ctrlToolbar.Create(WinUtil::mainWnd, NULL, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE | TBSTYLE_FLAT | TBSTYLE_TOOLTIPS, 0, ATL_IDW_TOOLBAR);
	ctrlToolbar.SetImageList(fdmLargeImages);
	ctrlToolbar.SetHotImageList(fdmLargeImagesHot);

	const int numButtons = 5;

	TBBUTTON tb[numButtons];
	memset(tb, 0, sizeof(tb));
	int n = 0, bitmap = 0;

	tb[n].iBitmap = bitmap++;
	tb[n].idCommand = ID_FIRE_FILE_SETTINGS;
	tb[n].fsState = TBSTATE_ENABLED;
	tb[n].fsStyle = TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;


	n++;
	tb[n].fsStyle = TBSTYLE_SEP;

/*	n++;
	tb[n].iBitmap = bitmap++;
	tb[n].idCommand = ID_AUTO_SEARCH_FRAME;
	tb[n].fsState = TBSTATE_ENABLED;
	tb[n].fsStyle = TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;


	n++;
	tb[n].fsStyle = TBSTYLE_SEP;

	n++;
	tb[n].iBitmap = bitmap++;
	tb[n].idCommand = ID_FIRE_NOTEPAD_FRAME;
	tb[n].fsState = TBSTATE_ENABLED;
	tb[n].fsStyle = TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE;*/

	ctrlToolbar.SetButtonStructSize();
	ctrlToolbar.AddButtons(numButtons, tb);
	ctrlToolbar.AutoSize();

	return ctrlToolbar.m_hWnd;
}

void FireMainFrame::fdmToolTips(int& idCtrl, LPNMTTDISPINFO& pDispInfo, int& stringId) {
	switch(idCtrl) {
		case ID_FIRE_FILE_SETTINGS: stringId = FireResourceManager::MENU_FIRE_SETTINGS; break;
//		case ID_FIRE_NOTEPAD_FRAME: stringId = FireResourceManager::MENU_NOTEPAD_FRAME; break;
//		case ID_AUTO_SEARCH_FRAME: stringId = FireResourceManager::MENU_AUTO_SEARCH; break;
	}

	if (stringId != -1) {
		_tcsncpy(pDispInfo->lpszText, FIRECTSTRING_I((FireResourceManager::FireStrings)stringId), 79); 
		pDispInfo->uFlags |= TTF_DI_SETITEM;
	}

	stringId = -1;
}

LRESULT FireMainFrame::OnFireAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	FireAboutDlg dlg;
	dlg.DoModal(WinUtil::mainWnd);
	return 0;
}

LRESULT FireMainFrame::OnFireFileSettings(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	FirePropertiesDlg dlg(WinUtil::mainWnd, FireSettingsManager::getInstance());

	if(dlg.DoModal(WinUtil::mainWnd) == IDOK)
		SettingsManager::getInstance()->save();
	return 0;
}

//LRESULT FireMainFrame::OnFireNotepadFrame(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
/*{
	FireNotepadFrame::openWindow();
	return 0;
}*/

//LRESULT FireMainFrame::OnAutoSearchFrame(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
/*{
	AutoSearchFrame::openWindow();
	return 0;
}*/
/**
 * @file
 * $Id: MainFrm.cpp,v 1.109 2006/01/23 08:00:50 arnetheduck Exp $
 */
