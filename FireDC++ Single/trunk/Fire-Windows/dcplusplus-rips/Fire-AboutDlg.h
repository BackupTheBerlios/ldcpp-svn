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

#if !defined(ABOUT_DLG_H)
#define ABOUT_DLG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../client/HttpConnection.h"
#include "../../client/SimpleXML.h"
#include "../../client/ResourceManager.h"
#include "../../windows/WinUtil.h"
#include "../../Fire-Client/dcplusplus-rips/Fire-Version.h"

static const TCHAR fdmThanks[] = _T("Big thanks to everyone mentioned by Arnetheduck in the other about page. And to Arne himself. :)\r\n")
_T("Thanks go out to berlios for hosting the project.\r\n")
_T("Fire++ uses a few more projects than DC++, so I would like to also thank\r\n")
_T("Pothead for the help and for the idea to add other projects to the original one.\r\n")
_T("\r\nI would also thank these people:\r\n")
_T("arnetheduck, GargoyleMT, Pothead.\r\n")
_T("And also thank to all the testers or friends that helped me developing the client, really thank you.");

class FireAboutDlg : public CDialogImpl<FireAboutDlg>, private HttpConnectionListener
{
public:
	enum { IDD = IDD_FIRE_ABOUT };
	enum { WM_VERSIONDATA = WM_APP + 53 };

	FireAboutDlg() { }
	virtual ~FireAboutDlg() { }

	BEGIN_MSG_MAP(FireAboutDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_VERSIONDATA, onVersionData)
		COMMAND_ID_HANDLER(IDOK, OnCloseCmd)
		COMMAND_ID_HANDLER(IDCANCEL, OnCloseCmd)
	END_MSG_MAP()

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
		SetDlgItemText(IDC_FIRE_ABOUT_VERSION, _T("Fire v") _T(FIREVERSIONSTRING) _T(" ") _T(FIRESVNVERSIONSTRING) _T("\n(c) Copyright 2006 Michael Jones\nFire  is licenced under GPL\nhttp://fdm.berlios.de/"));
		CEdit ctrl(GetDlgItem(IDC_FIRE_ABOUT_THANKS));
		ctrl.FmtLines(TRUE);
		ctrl.AppendText(fdmThanks, TRUE);
		ctrl.Detach();
		SetDlgItemText(IDC_FIRE_ABOUT_TTH, WinUtil::tth.c_str());
		SetDlgItemText(IDC_FIRE_ABOUT_LATEST, CTSTRING(DOWNLOADING));
		CenterWindow(GetParent());
		c.addListener(this);
		c.downloadFile("http://dcplusplus.sourceforge.net/version.xml");
		return TRUE;
	}

	LRESULT onVersionData(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
		tstring* x = (tstring*) wParam;
		SetDlgItemText(IDC_LATEST, x->c_str());
		delete x;
		return 0;
	}
		
	LRESULT OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
		EndDialog(wID);
		return 0;
	}

private:
	HttpConnection c;

	FireAboutDlg(const FireAboutDlg&) { dcassert(0); }
	
	virtual void on(HttpConnectionListener::Data, HttpConnection* /*conn*/, const uint8_t* buf, size_t len) throw() {
		downBuf.append((char*)buf, len);
	}

	virtual void on(HttpConnectionListener::Complete, HttpConnection* conn, const string&) throw() {
		if(!downBuf.empty()) {
			SimpleXML xml;
			xml.fromXML(downBuf);
			if(xml.findChild("DCUpdate")) {
				xml.stepIn();
				if(xml.findChild("Version")) {
					tstring* x = new tstring(Text::toT(xml.getChildData()));
					PostMessage(WM_VERSIONDATA, (WPARAM) x);
				}
			}
		}
		conn->removeListener(this);
	}

	virtual void on(HttpConnectionListener::Failed, HttpConnection* conn, const string& aLine) throw() {
		tstring* x = new tstring(Text::toT(aLine));
		PostMessage(WM_VERSIONDATA, (WPARAM) x);
		conn->removeListener(this);
	}

	string downBuf;
};

#endif // !defined(ABOUT_DLG_H)
