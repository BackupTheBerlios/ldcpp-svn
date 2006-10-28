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
#include "../client/SettingsManager.h"
#include "../client/SoundManager.h"
#include "WinUtil.h"

PropPage::TextItem Sounds::texts[] = {
	{ IDC_PRIVATE_MESSAGE_BEEP,							ResourceManager::SETTINGS_PM_BEEP },
	{ IDC_PRIVATE_MESSAGE_BEEP_OPEN,					ResourceManager::SETTINGS_PM_BEEP_OPEN },
	{ IDC_FIREDC_PM_SOUND,								ResourceManager::LAST, ResourceManager::SETFIREDC_PRIVATE_SOUND },
	{ IDC_BROWSE,										ResourceManager::BROWSE },
	{ IDC_NONE,											ResourceManager::LAST, ResourceManager::NONE },
	{ IDC_TEST,											ResourceManager::LAST, ResourceManager::TEST},
	{ IDC_SETTINGS_SOUND,								ResourceManager::SETTINGS_SOUNDS },
	{ IDC_SETTINGS_FILE_SOUND,							ResourceManager::FILE },
	{ 0, ResourceManager::SETTINGS_AUTO_AWAY }
};

PropPage::Item Sounds::items[] = {
	{ IDC_PRIVATE_MESSAGE_BEEP, SettingsManager::PRIVATE_MESSAGE_BEEP, PropPage::T_BOOL },
	{ IDC_PRIVATE_MESSAGE_BEEP_OPEN, SettingsManager::PRIVATE_MESSAGE_BEEP_OPEN, PropPage::T_BOOL },
	{ 0, 0, PropPage::T_END }
};

PropPage::ListItem Sounds::listItems[] = {
	{ SettingsManager::DOWNLOAD_BEGINS_SOUND_ACTIVE,	ResourceManager::SOUND_DOWNLOAD_BEGINS },
	{ SettingsManager::DOWNLOAD_FINISHED_SOUND_ACTIVE,	ResourceManager::SOUND_DOWNLOAD_FINISHED },
//	{ SettingsManager::SOURCE_ADDED_SOUND_ACTIVE,		ResourceManager::SOUND_SOURCE_ADDED }, 
	{ SettingsManager::UPLOAD_FINISHED_SOUND_ACTIVE,	ResourceManager::SOUND_UPLOAD_FINISHED },
	{ SettingsManager::PM_SOUND_ACTIVE,					ResourceManager::LAST, ResourceManager::SETFIREDC_PRIVATE_SOUND },
//	{ SettingsManager::MYNICK_SOUND_ACTIVE,				ResourceManager::MYNICK_IN_CHAT },
//	{ SettingsManager::TTH_INVALID_SOUND_ACTIVE,		ResourceManager::SOUND_TTH_INVALID },
	{ SettingsManager::EXCEPTION_SOUND_ACTIVE,			ResourceManager::SOUND_EXCEPTION },
	{ SettingsManager::HUB_CONNECTED_SOUND_ACTIVE,		ResourceManager::HUB_CONNECTED },
	{ SettingsManager::HUB_DISCONNECTED_SOUND_ACTIVE,	ResourceManager::HUB_DISCONNECTED },
	{ SettingsManager::FAVUSER_ONLINE_SOUND_ACTIVE,		ResourceManager::FAVUSER_ONLINE },
	{ SettingsManager::URL_CLICK_SOUND_ACTIVE,			ResourceManager::LAST, ResourceManager::SOUND_URL_CLICK },
	{ SettingsManager::START_UPLOAD_SOUND_ACTIVE,		ResourceManager::LAST, ResourceManager::SOUND_START_UPLOAD },
	{ SettingsManager::SOUND_TYPING_NOTIFY_ACTIVE,		ResourceManager::SOUND_TYPING_NOTIFY },
	{ 0,												ResourceManager::SETTINGS_AUTO_AWAY }
};


LRESULT Sounds::onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PropPage::translate((HWND)(*this), texts);
	PropPage::read((HWND)*this, items, listItems, GetDlgItem(IDC_SOUND_OPTIONS));

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
	PropPage::write((HWND)*this, items, listItems, GetDlgItem(IDC_SOUND_OPTIONS));

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

