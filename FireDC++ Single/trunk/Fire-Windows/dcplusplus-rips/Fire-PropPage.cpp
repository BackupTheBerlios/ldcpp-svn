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

#include "Fire-PropPage.h"

#include "../../Fire-Client/dcplusplus-rips/Fire-SettingsManager.h"

#define SETTING_STR_MAXLEN 1024

void FirePropPage::read(HWND page, Item const* items, ListItem* listItems /* = NULL */, HWND list /* = 0 */)
{
	dcassert(page != NULL);

	bool const useDef = true;
	for(Item const* i = items; i->type != T_END; i++)
	{
		switch(i->type)
		{
		case T_STR:
			if(!FireSettingsManager::getInstance()->isDefault(i->setting)) {
				::SetDlgItemText(page, i->itemID,
					Text::toT(settings->get((FireSettingsManager::StrSetting)i->setting, useDef)).c_str());
			}
			break;
		case T_INT:
			if(!FireSettingsManager::getInstance()->isDefault(i->setting)) {
				::SetDlgItemInt(page, i->itemID,
					settings->get((FireSettingsManager::IntSetting)i->setting, useDef), FALSE);
			}
			break;
		case T_BOOL:
			if(settings->getBool((FireSettingsManager::IntSetting)i->setting, useDef))
				::CheckDlgButton(page, i->itemID, BST_CHECKED);
			else
				::CheckDlgButton(page, i->itemID, BST_UNCHECKED);
		}
	}

	if(listItems != NULL) {
		CListViewCtrl ctrl;

		ctrl.Attach(list);
		CRect rc;
		ctrl.GetClientRect(rc);
		ctrl.SetExtendedListViewStyle(LVS_EX_LABELTIP | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
		ctrl.InsertColumn(0, _T("Dummy"), LVCFMT_LEFT, rc.Width(), 0);

		LVITEM lvi;
		lvi.mask = LVIF_TEXT;
		lvi.iSubItem = 0;

		for(int i = 0; listItems[i].setting != 0; i++) {
			lvi.iItem = i;
			if(listItems[i].desc != FireResourceManager::LAST)
			lvi.pszText = const_cast<TCHAR*>(FIRECTSTRING_I(listItems[i].desc));
			else
				lvi.pszText = const_cast<TCHAR*>(FIRECTSTRINGTWO_I(listItems[i].descTwo));
			ctrl.InsertItem(&lvi);
			ctrl.SetCheckState(i, FireSettingsManager::getInstance()->getBool(FireSettingsManager::IntSetting(listItems[i].setting), true));
		}
		ctrl.SetColumnWidth(0, LVSCW_AUTOSIZE);
		ctrl.Detach();
	}
}

void FirePropPage::write(HWND page, Item const* items, ListItem* listItems /* = NULL */, HWND list /* = NULL */)
{
	dcassert(page != NULL);

	AutoArray<TCHAR> buf(SETTING_STR_MAXLEN);
	for(Item const* i = items; i->type != T_END; i++)
	{
		switch(i->type)
		{
		case T_STR:
			{
				::GetDlgItemText(page, i->itemID, buf, SETTING_STR_MAXLEN);
				settings->set((FireSettingsManager::StrSetting)i->setting, Text::fromT(tstring(buf)));

				break;
			}
		case T_INT:
			{
				::GetDlgItemText(page, i->itemID, buf, SETTING_STR_MAXLEN);
				settings->set((FireSettingsManager::IntSetting)i->setting, Text::fromT(tstring(buf)));
				break;
			}
		case T_BOOL:
			{
				if(::IsDlgButtonChecked(page, i->itemID) == BST_CHECKED)
					settings->set((FireSettingsManager::IntSetting)i->setting, true);
				else
					settings->set((FireSettingsManager::IntSetting)i->setting, false);
			}
		}
	}

	if(listItems != NULL) {
		CListViewCtrl ctrl;
		ctrl.Attach(list);

		int i;
		for(i = 0; listItems[i].setting != 0; i++) {
			FireSettingsManager::getInstance()->set(FireSettingsManager::IntSetting(listItems[i].setting), ctrl.GetCheckState(i));
		}

		ctrl.Detach();
	}
}

void FirePropPage::translate(HWND page, TextItem* textItems)
{
	if (textItems != NULL) {
		for(int i = 0; textItems[i].itemID != 0; i++) {
			if(textItems[i].translatedString != FireResourceManager::LAST)
			::SetDlgItemText(page, textItems[i].itemID,
				FIRECTSTRING_I(textItems[i].translatedString));
			else
				::SetDlgItemText(page, textItems[i].itemID,
					FIRECTSTRINGTWO_I(textItems[i].translatedStringTwo));
		}
	}
}
