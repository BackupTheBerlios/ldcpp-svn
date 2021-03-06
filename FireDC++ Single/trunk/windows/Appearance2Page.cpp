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
#include "../client/DCPlusPlus.h"
#include "Resource.h"

#include "Appearance2Page.h"
#include "../client/SettingsManager.h"
#include "../client/StringTokenizer.h"
#include "WinUtil.h"

PropPage::TextItem Appearance2Page::texts[] = {
	{ IDC_SETTINGS_BOLD_CONTENTS, ResourceManager::SETTINGS_BOLD_OPTIONS },
	{ IDC_SETTINGS_COLORS, ResourceManager::SETTINGS_COLORS },
	{ IDC_SELWINCOLOR, ResourceManager::SETTINGS_SELECT_WINDOW_COLOR },
	{ IDC_SELTEXT, ResourceManager::SETTINGS_SELECT_TEXT_FACE },
	{ IDC_COLOREXAMPLE, ResourceManager::SETTINGS_EXAMPLE_TEXT },
	{ IDC_SETTINGS_REQUIRES_RESTART, ResourceManager::SETTINGS_REQUIRES_RESTART },
	{ IDC_SETTINGS_UPLOAD_BAR_COLOR, ResourceManager::UPLOADS },
	{ IDC_SETTINGS_SOUNDS, ResourceManager::SETTINGS_SOUNDS },
	{ IDC_SETTINGS_DOWNLOAD_BAR_COLOR, ResourceManager::DOWNLOADS },
	{ 0, ResourceManager::SETTINGS_AUTO_AWAY }
};

PropPage::Item Appearance2Page::items[] = {
	{ 0, 0, PropPage::T_END }
};

PropPage::ListItem Appearance2Page::listItems[] = {
	{ SettingsManager::BOLD_FINISHED_DOWNLOADS, ResourceManager::FINISHED_DOWNLOADS },
	{ SettingsManager::BOLD_FINISHED_UPLOADS, ResourceManager::FINISHED_UPLOADS },
	{ SettingsManager::BOLD_QUEUE, ResourceManager::DOWNLOAD_QUEUE },
	{ SettingsManager::BOLD_HUB, ResourceManager::HUB },
	{ SettingsManager::BOLD_PM, ResourceManager::PRIVATE_MESSAGE },
	{ SettingsManager::BOLD_SEARCH, ResourceManager::SEARCH },
	{ SettingsManager::BOLD_WAITING_USERS, ResourceManager::WAITING_USERS },
	{ SettingsManager::BOLD_SYSTEM_LOG, ResourceManager::SYSTEM_LOG },
	{ 0, ResourceManager::SETTINGS_AUTO_AWAY }
};

Appearance2Page::~Appearance2Page()
{
	::DeleteObject(bgbrush);
	::DeleteObject(fontObj);
}

LRESULT Appearance2Page::onInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	PropPage::translate((HWND)(*this), texts);
	ctrlExample.Attach(GetDlgItem(IDC_COLOREXAMPLE));

	PropPage::read((HWND)*this, items, listItems,GetDlgItem(IDC_BOLD_BOOLEANS));
	WinUtil::decodeFont(Text::toT(SETTING(TEXT_FONT)), font);

	// Do specialized reading here
	fg = SETTING(TEXT_COLOR);
	bg = SETTING(BACKGROUND_COLOR);
	bgbrush = ::CreateSolidBrush(bg);
	fontObj = ::CreateFontIndirect(&font);
	upBar = SETTING(UPLOAD_BAR_COLOR);
	downBar = SETTING(DOWNLOAD_BAR_COLOR);
	return TRUE;
}

void Appearance2Page::write()
{
	PropPage::write((HWND)*this, items, listItems,GetDlgItem(IDC_BOLD_BOOLEANS));

	settings->set(SettingsManager::TEXT_COLOR, (int)fg);
	settings->set(SettingsManager::BACKGROUND_COLOR, (int)bg);
	settings->set(SettingsManager::UPLOAD_BAR_COLOR, (int)upBar);
	settings->set(SettingsManager::DOWNLOAD_BAR_COLOR, (int)downBar);

	tstring f = WinUtil::encodeFont(font);
	settings->set(SettingsManager::TEXT_FONT, Text::fromT(f));
}

LRESULT Appearance2Page::onClickedBackground(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CColorDialog d(SETTING(BACKGROUND_COLOR), 0, *this);
	if(d.DoModal() == IDOK)
	{
		::DeleteObject(bgbrush);
		bg = d.GetColor();
		bgbrush = CreateSolidBrush(bg);
		ctrlExample.Invalidate();
	}
	return TRUE;
}


LRESULT Appearance2Page::onClickedText(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	LOGFONT tmp = font;
	CFontDialog d(&tmp, CF_EFFECTS | CF_SCREENFONTS, NULL, *this);
	d.m_cf.rgbColors = fg;
	if(d.DoModal() == IDOK)
	{
		font = tmp;
		fg = d.GetColor();
		::DeleteObject(fontObj);
		fontObj = ::CreateFontIndirect(&font);
		ctrlExample.Invalidate();
	}
	return TRUE;
}

LRESULT Appearance2Page::onCtlColor(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	HWND hwnd = (HWND)lParam;

	if(hwnd == (HWND)ctrlExample)
	{
		HDC hdc = (HDC)wParam;
		::SetBkMode(hdc, TRANSPARENT);
		::SetTextColor(hdc, fg);
		::SelectObject(hdc, fontObj);
		return (LRESULT)bgbrush;
	}
	else
		return FALSE;
}

LRESULT Appearance2Page::onPickColor(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	switch (wID) {
		case IDC_SETTINGS_UPLOAD_BAR_COLOR:
			{
				CColorDialog colPicker(upBar, 0, *this);
				if(colPicker.DoModal() == IDOK)
				{
					upBar = colPicker.GetColor();
				}
			}
			break;
		case IDC_SETTINGS_DOWNLOAD_BAR_COLOR:
			{
				CColorDialog colPicker(downBar, 0, *this);
				if(colPicker.DoModal() == IDOK)
				{
					downBar = colPicker.GetColor();
				}
			}
			break;
		default:
			break;
	}
	return true;
}

LRESULT Appearance2Page::onHelpInfo(LPNMHDR /*pnmh*/) {
	HtmlHelp(m_hWnd, WinUtil::getHelpFile().c_str(), HH_HELP_CONTEXT, IDD_APPEARANCE2PAGE);
	return 0;
}

LRESULT Appearance2Page::onHelp(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
	HtmlHelp(m_hWnd, WinUtil::getHelpFile().c_str(), HH_HELP_CONTEXT, IDD_APPEARANCE2PAGE);
	return 0;
}
