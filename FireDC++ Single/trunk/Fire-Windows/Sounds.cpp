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

#include "stdafx.h"
#include "../client/DCPlusPlus.h"
#include "Resource.h"

#include "Sounds.h"
#include "../Fire-Client/dcplusplus-rips/Fire-SettingsManager.h"
#include "../Fire-Client/SoundManager.h"
#include "../windows/WinUtil.h"

FirePropPage::TextItem Sounds::texts[] = {
	{ IDC_PRIVATE_MESSAGE_BEEP,							FireResourceManager::SETTINGS_PM_BEEP },
	{ IDC_PRIVATE_MESSAGE_BEEP_OPEN,					FireResourceManager::SETTINGS_PM_BEEP_OPEN },
	{ IDC_FIREDC_PM_SOUND,								FireResourceManager::LAST, FireResourceManager::SETFIREDC_PRIVATE_SOUND },
	{ IDC_BROWSED,										FireResourceManager::BROWSE },
	{ IDC_NONE,											FireResourceManager::LAST, FireResourceManager::NONE },
	{ IDC_TEST,											FireResourceManager::LAST, FireResourceManager::TEST},
	{ IDC_SETTINGS_SOUND,								FireResourceManager::SETTINGS_SOUNDS },
	{ IDC_SETTINGS_FILE_SOUND,							FireResourceManager::FILE },
	{ 0, FireResourceManager::FIRE_SETTINGS_AUTO_AWAY }
};

FirePropPage::Item Sounds::items[] = {
	{ IDC_PRIVATE_MESSAGE_BEEP, FireSettingsManager::PRIVATE_MESSAGE_BEEP, FirePropPage::T_BOOL },
	{ IDC_PRIVATE_MESSAGE_BEEP_OPEN, FireSettingsManager::PRIVATE_MESSAGE_BEEP_OPEN, FirePropPage::T_BOOL },
	{ 0, 0, FirePropPage::T_END }
};

FirePropPage::ListItem Sounds::listItems[] = {
	{ FireSettingsManager::DOWNLOAD_BEGINS_SOUND_ACTIVE,		FireResourceManager::SOUND_DOWNLOAD_BEGINS },
	{ FireSettingsManager::DOWNLOAD_FINISHED_SOUND_ACTIVE,	FireResourceManager::SOUND_DOWNLOAD_FINISHED },
//	{ FireSettingsManager::SOURCE_ADDED_SOUND_ACTIVE,		FireResourceManager::SOUND_SOURCE_ADDED }, 
	{ FireSettingsManager::UPLOAD_FINISHED_SOUND_ACTIVE,		FireResourceManager::SOUND_UPLOAD_FINISHED },
	{ FireSettingsManager::PM_SOUND_ACTIVE,					FireResourceManager::LAST, FireResourceManager::SETFIREDC_PRIVATE_SOUND },
//	{ FireSettingsManager::MYNICK_SOUND_ACTIVE,				FireResourceManager::MYNICK_IN_CHAT },
//	{ FireSettingsManager::TTH_INVALID_SOUND_ACTIVE,			FireResourceManager::SOUND_TTH_INVALID },
	{ FireSettingsManager::EXCEPTION_SOUND_ACTIVE,			FireResourceManager::SOUND_EXCEPTION },
	{ FireSettingsManager::HUB_CONNECTED_SOUND_ACTIVE,		FireResourceManager::HUB_CONNECTED },
	{ FireSettingsManager::HUB_DISCONNECTED_SOUND_ACTIVE,	FireResourceManager::HUB_DISCONNECTED },
	{ FireSettingsManager::FAVUSER_ONLINE_SOUND_ACTIVE,		FireResourceManager::FAVUSER_ONLINE },
	{ FireSettingsManager::URL_CLICK_SOUND_ACTIVE,			FireResourceManager::LAST, FireResourceManager::SOUND_URL_CLICK },
	{ FireSettingsManager::START_UPLOAD_SOUND_ACTIVE,		FireResourceManager::LAST, FireResourceManager::SOUND_START_UPLOAD },
	{ FireSettingsManager::SOUND_TYPING_NOTIFY_ACTIVE,		FireResourceManager::SOUND_TYPING_NOTIFY },
	{ 0,													FireResourceManager::FIRE_SETTINGS_AUTO_AWAY }
};


LRESULT Sounds::onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	FirePropPage::translate((HWND)(*this), texts);
	FirePropPage::read((HWND)*this, items, listItems, GetDlgItem(IDC_SOUND_OPTIONS));

	for(int i = 0; i < SoundManager::LAST; ++i) {
		options.push_back(Text::toT(SoundManager::getInstance()->getSetting(i, SoundManager::FILE)));
	}

	::EnableWindow(GetDlgItem(IDC_SOUND_FILE), false);

	// Do specialized reading here
	return TRUE;
}

LRESULT Sounds::onItemChanged(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/) {
	soundOptions.Attach(GetDlgItem(IDC_SOUND_OPTIONS));

	TCHAR buf[512];
	
	if(GetDlgItemText(IDC_SOUND_FILE, buf, 512) > 0)
		options[oldSelection] = buf;
	
	int sel = soundOptions.GetSelectedIndex();
		
	if(sel >= 0) {
		bool checkState = soundOptions.GetCheckState(sel) == BST_CHECKED ? TRUE : FALSE;
		::EnableWindow(GetDlgItem(IDC_SOUND_FILE), checkState);
		SetDlgItemText(IDC_SOUND_FILE, options[sel].c_str());
		//save the old selection so we know where to save the values
		oldSelection = sel;
	}

	soundOptions.Detach();
	return 0;
}

void Sounds::write()
{
	FirePropPage::write((HWND)*this, items, listItems, GetDlgItem(IDC_SOUND_OPTIONS));

	//make sure we save the last edit too, the user
	//might not have changed the selection
	TCHAR buf[512];

	if(GetDlgItemText(IDC_SOUND_FILE, buf, 512) > 0)
		options[oldSelection] = buf;

	for(int i = 0; i < SoundManager::LAST; ++i) {
		string tmp = Text::fromT(options[i]);
		SoundManager::getInstance()->saveSetting(i, SoundManager::FILE, tmp);
	}
}

LRESULT Sounds::onBrowse(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	soundOptions.Attach(GetDlgItem(IDC_SOUND_OPTIONS));
	int sel = soundOptions.GetSelectedIndex();
	if(sel >= 0) {
		tstring x = _T("");	
		if(WinUtil::browseFile(x, m_hWnd, false) == IDOK) {
			SetDlgItemText(IDC_SOUND_FILE, x.c_str());
			options[sel] = x;
		}
	}
	soundOptions.Detach();
	return 0;
}

LRESULT Sounds::onClickedNone(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	soundOptions.Attach(GetDlgItem(IDC_SOUND_OPTIONS));
	int sel = soundOptions.GetSelectedIndex();
	if(sel >= 0) {
		tstring x = _T("");
		SetDlgItemText(IDC_SOUND_FILE, x.c_str());
		options[sel] = x;
	}
	soundOptions.Detach();
	return 0;
}

LRESULT Sounds::onTest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	soundOptions.Attach(GetDlgItem(IDC_SOUND_OPTIONS));
	int sel = soundOptions.GetSelectedIndex();
	if(sel >= 0) {
		PlaySound(options[sel].c_str(), NULL, SND_FILENAME | SND_ASYNC);

	}
	soundOptions.Detach();
	return 0;
}
/**
 * @file
 * $Id: Sounds.cpp,v 1.11 2005/02/22 16:49:49 Legolas Exp $
 */

