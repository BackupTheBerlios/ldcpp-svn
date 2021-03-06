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

#include "SearchFrm.h"
#include "LineDlg.h"

#include "../client/QueueManager.h"
#include "../client/StringTokenizer.h"
#include "../client/ClientManager.h"

TStringList SearchFrame::lastSearches;

int SearchFrame::columnIndexes[] = { COLUMN_FILENAME, COLUMN_NICK, COLUMN_TYPE, COLUMN_SIZE,
	COLUMN_PATH, COLUMN_SLOTS, COLUMN_CONNECTION, COLUMN_HUB, COLUMN_EXACT_SIZE, COLUMN_IP, COLUMN_TTH, COLUMN_CID };
int SearchFrame::columnSizes[] = { 200, 100, 50, 80, 100, 40, 70, 150, 80, 100, 125, 125 };

static ResourceManager::Strings columnNames[] = { ResourceManager::FILE, ResourceManager::USER, ResourceManager::TYPE, ResourceManager::SIZE,
	ResourceManager::PATH, ResourceManager::SLOTS, ResourceManager::CONNECTION,
	ResourceManager::HUB, ResourceManager::EXACT_SIZE, ResourceManager::IP_BARE, ResourceManager::TTH_ROOT, ResourceManager::CID };

SearchFrame::FrameMap SearchFrame::frames;

void SearchFrame::openWindow(const tstring& str /* = Util::emptyString */, LONGLONG size /* = 0 */, SearchManager::SizeModes mode /* = SearchManager::SIZE_ATLEAST */, SearchManager::TypeModes type /* = SearchManager::TYPE_ANY ( 0 ) */) {
	SearchFrame* pChild = new SearchFrame();
	pChild->setInitial(str, size, mode, type);
	pChild->CreateEx(WinUtil::mdiClient);

	frames.insert( FramePair(pChild->m_hWnd, pChild) );
}

void SearchFrame::closeAll() {
	for(FrameIter i = frames.begin(); i != frames.end(); ++i)
		::PostMessage(i->first, WM_CLOSE, 0, 0);
}

LRESULT SearchFrame::onCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	CreateSimpleStatusBar(ATL_IDS_IDLEMESSAGE, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | SBARS_SIZEGRIP);
	ctrlStatus.Attach(m_hWndStatusBar);

	ctrlSearchBox.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_VSCROLL | CBS_DROPDOWN | CBS_AUTOHSCROLL, 0);
	for(TStringIter i = lastSearches.begin(); i != lastSearches.end(); ++i) {
		ctrlSearchBox.InsertString(0, i->c_str());
	}
	searchBoxContainer.SubclassWindow(ctrlSearchBox.m_hWnd);
	ctrlSearchBox.SetExtendedUI();

	ctrlPurge.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		BS_PUSHBUTTON , 0, IDC_PURGE);
	ctrlPurge.SetWindowText(CTSTRING(PURGE));
	ctrlPurge.SetFont(WinUtil::systemFont);
	purgeContainer.SubclassWindow(ctrlPurge.m_hWnd);

	ctrlMode.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | CBS_DROPDOWNLIST, WS_EX_CLIENTEDGE);
	modeContainer.SubclassWindow(ctrlMode.m_hWnd);

	ctrlSize.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		ES_AUTOHSCROLL | ES_NUMBER, WS_EX_CLIENTEDGE);
	sizeContainer.SubclassWindow(ctrlSize.m_hWnd);

	ctrlSizeMode.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | CBS_DROPDOWNLIST, WS_EX_CLIENTEDGE);
	sizeModeContainer.SubclassWindow(ctrlSizeMode.m_hWnd);

	ctrlFiletype.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | CBS_DROPDOWNLIST, WS_EX_CLIENTEDGE);
	fileTypeContainer.SubclassWindow(ctrlFiletype.m_hWnd);

	ctrlResults.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SHAREIMAGELISTS, WS_EX_CLIENTEDGE, IDC_RESULTS);
	ctrlResults.SetExtendedListViewStyle(LVS_EX_LABELTIP | LVS_EX_HEADERDRAGDROP | LVS_EX_FULLROWSELECT);
	ctrlResults.SetImageList(WinUtil::fileImages, LVSIL_SMALL);
	resultsContainer.SubclassWindow(ctrlResults.m_hWnd);

	ctrlHubs.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		WS_HSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER, WS_EX_CLIENTEDGE, IDC_HUB);
	ctrlHubs.SetExtendedListViewStyle(LVS_EX_LABELTIP | LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);
	hubsContainer.SubclassWindow(ctrlHubs.m_hWnd);

	searchLabel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	searchLabel.SetFont(WinUtil::systemFont, FALSE);
	searchLabel.SetWindowText(CTSTRING(SEARCH_FOR));

	sizeLabel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	sizeLabel.SetFont(WinUtil::systemFont, FALSE);
	sizeLabel.SetWindowText(CTSTRING(SIZE));

	typeLabel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	typeLabel.SetFont(WinUtil::systemFont, FALSE);
	typeLabel.SetWindowText(CTSTRING(FILE_TYPE));

	optionLabel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	optionLabel.SetFont(WinUtil::systemFont, FALSE);
	optionLabel.SetWindowText(CTSTRING(SEARCH_OPTIONS));

	hubsLabel.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	hubsLabel.SetFont(WinUtil::systemFont, FALSE);
	hubsLabel.SetWindowText(CTSTRING(HUBS));

	ctrlSlots.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, NULL, IDC_FREESLOTS);
	ctrlSlots.SetButtonStyle(BS_AUTOCHECKBOX, FALSE);
	ctrlSlots.SetFont(WinUtil::systemFont, FALSE);
	ctrlSlots.SetWindowText(CTSTRING(ONLY_FREE_SLOTS));
	ctrlSlots.SetCheck(onlyFree);
	slotsContainer.SubclassWindow(ctrlSlots.m_hWnd);

	ctrlShowUI.Create(ctrlStatus.m_hWnd, rcDefault, _T("+/-"), WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	ctrlShowUI.SetButtonStyle(BS_AUTOCHECKBOX, false);
	ctrlShowUI.SetCheck(1);
	showUIContainer.SubclassWindow(ctrlShowUI.m_hWnd);

	ctrlDoSearch.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN |
		BS_PUSHBUTTON , 0, IDC_SEARCH);
	ctrlDoSearch.SetWindowText(CTSTRING(SEARCH));
	ctrlDoSearch.SetFont(WinUtil::systemFont);
	doSearchContainer.SubclassWindow(ctrlDoSearch.m_hWnd);

	ctrlSearchBox.SetFont(WinUtil::systemFont, FALSE);
	ctrlSize.SetFont(WinUtil::systemFont, FALSE);
	ctrlMode.SetFont(WinUtil::systemFont, FALSE);
	ctrlSizeMode.SetFont(WinUtil::systemFont, FALSE);
	ctrlFiletype.SetFont(WinUtil::systemFont, FALSE);

	ctrlMode.AddString(CTSTRING(NORMAL));
	ctrlMode.AddString(CTSTRING(AT_LEAST));
	ctrlMode.AddString(CTSTRING(AT_MOST));
	ctrlMode.SetCurSel(1);

	ctrlSizeMode.AddString(CTSTRING(B));
	ctrlSizeMode.AddString(CTSTRING(KiB));
	ctrlSizeMode.AddString(CTSTRING(MiB));
	ctrlSizeMode.AddString(CTSTRING(GiB));
	if(initialSize == 0)
		ctrlSizeMode.SetCurSel(2);
	else
		ctrlSizeMode.SetCurSel(0);

	ctrlFiletype.AddString(CTSTRING(ANY));
	ctrlFiletype.AddString(CTSTRING(AUDIO));
	ctrlFiletype.AddString(CTSTRING(COMPRESSED));
	ctrlFiletype.AddString(CTSTRING(DOCUMENT));
	ctrlFiletype.AddString(CTSTRING(EXECUTABLE));
	ctrlFiletype.AddString(CTSTRING(PICTURE));
	ctrlFiletype.AddString(CTSTRING(VIDEO));
	ctrlFiletype.AddString(CTSTRING(DIRECTORY));
	ctrlFiletype.AddString(_T("TTH"));
	ctrlFiletype.SetCurSel(SETTING(LAST_SEARCH_TYPE));

	// Create listview columns
	WinUtil::splitTokens(columnIndexes, SETTING(SEARCHFRAME_ORDER), COLUMN_LAST);
	WinUtil::splitTokens(columnSizes, SETTING(SEARCHFRAME_WIDTHS), COLUMN_LAST);

	for(int j=0; j<COLUMN_LAST; j++) {
		int fmt = (j == COLUMN_SIZE || j == COLUMN_EXACT_SIZE) ? LVCFMT_RIGHT : LVCFMT_LEFT;
		ctrlResults.InsertColumn(j, CTSTRING_I(columnNames[j]), fmt, columnSizes[j], j);
	}

	ctrlResults.SetColumnOrderArray(COLUMN_LAST, columnIndexes);

	ctrlResults.SetBkColor(WinUtil::bgColor);
	ctrlResults.SetTextBkColor(WinUtil::bgColor);
	ctrlResults.SetTextColor(WinUtil::textColor);
	ctrlResults.SetFont(WinUtil::systemFont, FALSE);	// use Util::font instead to obey Appearace settings

	ctrlHubs.InsertColumn(0, _T("Dummy"), LVCFMT_LEFT, LVSCW_AUTOSIZE, 0);
	ctrlHubs.SetBkColor(WinUtil::bgColor);
	ctrlHubs.SetTextBkColor(WinUtil::bgColor);
	ctrlHubs.SetTextColor(WinUtil::textColor);
	ctrlHubs.SetFont(WinUtil::systemFont, FALSE);	// use Util::font instead to obey Appearace settings

	initHubs();

	targetDirMenu.CreatePopupMenu();
	targetMenu.CreatePopupMenu();
	resultsMenu.CreatePopupMenu();

	resultsMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD, CTSTRING(DOWNLOAD));
	resultsMenu.AppendMenu(MF_POPUP, (UINT_PTR)(HMENU)targetMenu, CTSTRING(DOWNLOAD_TO));
	resultsMenu.AppendMenu(MF_STRING, IDC_DOWNLOADDIR, CTSTRING(DOWNLOAD_WHOLE_DIR));
	resultsMenu.AppendMenu(MF_POPUP, (UINT_PTR)(HMENU)targetDirMenu, CTSTRING(DOWNLOAD_WHOLE_DIR_TO));
	resultsMenu.AppendMenu(MF_STRING, IDC_VIEW_AS_TEXT, CTSTRING(VIEW_AS_TEXT));
	resultsMenu.AppendMenu(MF_SEPARATOR);
	resultsMenu.AppendMenu(MF_STRING, IDC_SEARCH_ALTERNATES, CTSTRING(SEARCH_FOR_ALTERNATES));
	resultsMenu.AppendMenu(MF_STRING, IDC_BITZI_LOOKUP, CTSTRING(LOOKUP_AT_BITZI));
	resultsMenu.AppendMenu(MF_STRING, IDC_COPY_MAGNET, CTSTRING(COPY_MAGNET));
	resultsMenu.AppendMenu(MF_SEPARATOR);
	appendUserItems(resultsMenu);
	resultsMenu.AppendMenu(MF_SEPARATOR);
	resultsMenu.AppendMenu(MF_STRING, IDC_REMOVE, CTSTRING(REMOVE));
	resultsMenu.SetMenuDefaultItem(IDC_DOWNLOAD);

	UpdateLayout();

	if(!initialString.empty()) {
		lastSearches.push_back(initialString);
		ctrlSearchBox.InsertString(0, initialString.c_str());
		ctrlSearchBox.SetCurSel(0);
		ctrlMode.SetCurSel(initialMode);
		ctrlSize.SetWindowText(Text::toT(Util::toString(initialSize)).c_str());
		ctrlFiletype.SetCurSel(initialType);
		onEnter();
	} else {
		SetWindowText(CTSTRING(SEARCH));
	}

	bHandled = FALSE;
	return 1;
}

void SearchFrame::onEnter() {
	StringList clients;

	// Change Default Settings If Changed
	if (onlyFree != BOOLSETTING(SEARCH_ONLY_FREE_SLOTS))
		SettingsManager::getInstance()->set(SettingsManager::SEARCH_ONLY_FREE_SLOTS, onlyFree);
	if (!initialType && ctrlFiletype.GetCurSel() != SETTING(LAST_SEARCH_TYPE))
		SettingsManager::getInstance()->set(SettingsManager::LAST_SEARCH_TYPE, ctrlFiletype.GetCurSel());

	if(!(ctrlSearch.GetWindowTextLength() > 0))
		return;

	int n = ctrlHubs.GetItemCount();
	for(int i = 0; i < n; i++) {
		if(ctrlHubs.GetCheckState(i)) {
			clients.push_back(Text::fromT(ctrlHubs.getItemData(i)->url));
		}
	}

	if(!clients.size())
		return;

	tstring s(ctrlSearch.GetWindowTextLength() + 1, _T('\0'));
	ctrlSearch.GetWindowText(&s[0], s.size());
	s.resize(s.size()-1);

	tstring size(ctrlSize.GetWindowTextLength() + 1, _T('\0'));
	ctrlSize.GetWindowText(&size[0], size.size());
	size.resize(size.size()-1);

	double lsize = Util::toDouble(Text::fromT(size));
	switch(ctrlSizeMode.GetCurSel()) {
	case 1:
		lsize*=1024.0; break;
	case 2:
		lsize*=1024.0*1024.0; break;
	case 3:
		lsize*=1024.0*1024.0*1024.0; break;
	}

	int64_t llsize = (int64_t)lsize;

	for(int i = 0; i != ctrlResults.GetItemCount(); i++) {
		delete ctrlResults.getItemData(i);
	}
	ctrlResults.DeleteAllItems();

	{
		Lock l(cs);
		search = StringTokenizer<tstring>(s, ' ').getTokens();
	}

	//strip out terms beginning with -
	s.clear();
	for (TStringList::const_iterator si = search.begin(); si != search.end(); ++si)
		if ((*si)[0] != _T('-')) s += *si + _T(' ');	//Shouldn't get 0-length tokens, so safely assume at least a first char.
	s = s.substr(0, max(s.size(), static_cast<tstring::size_type>(1)) - 1);

	SearchManager::SizeModes mode((SearchManager::SizeModes)ctrlMode.GetCurSel());
	if(llsize == 0)
		mode = SearchManager::SIZE_DONTCARE;

	int ftype = ctrlFiletype.GetCurSel();


	// Add new searches to the last-search dropdown list
	if(find(lastSearches.begin(), lastSearches.end(), s) == lastSearches.end())
	{
		int i = max(SETTING(SEARCH_HISTORY)-1, 0);

		if(ctrlSearchBox.GetCount() > i)
			ctrlSearchBox.DeleteString(i);
		ctrlSearchBox.InsertString(0, s.c_str());

		while(lastSearches.size() > (TStringList::size_type)i) {
			lastSearches.erase(lastSearches.begin());
		}
		lastSearches.push_back(s);
	}

	ctrlStatus.SetText(1, (TSTRING(SEARCHING_FOR) + s + _T("...")).c_str());
	ctrlStatus.SetText(2, _T(""));
	ctrlStatus.SetText(3, _T(""));
	droppedResults = 0;
	isHash = (ftype == SearchManager::TYPE_TTH);

	SetWindowText((TSTRING(SEARCH) + _T(" - ") + s).c_str());

	if(SearchManager::getInstance()->okToSearch()) {
		SearchManager::getInstance()->search(clients, Text::fromT(s), llsize,
			(SearchManager::TypeModes)ftype, mode, "manual");
		if(BOOLSETTING(CLEAR_SEARCH)) // Only clear if the search was sent
			ctrlSearch.SetWindowText(_T(""));
	} else {
		int32_t waitFor = SearchManager::getInstance()->timeToSearch();
		AutoArray<TCHAR> buf(TSTRING(SEARCHING_WAIT).size() + 16);
		_stprintf(buf, CTSTRING(SEARCHING_WAIT), waitFor);

		ctrlStatus.SetText(1, buf);
		ctrlStatus.SetText(2, _T(""));
		ctrlStatus.SetText(3, _T(""));

		SetWindowText((TSTRING(SEARCH) + _T(" - ") + tstring(buf)).c_str());
		// Start the countdown timer
		timerID = SetTimer(1, 1000);
	}

}

void SearchFrame::on(SearchManagerListener::SR, SearchResult* aResult) throw() {
	// Check that this is really a relevant search result...
	{
		Lock l(cs);

		if(search.empty()) {
			return;
		}

		if(isHash) {
			if(aResult->getType() != SearchResult::TYPE_FILE || TTHValue(Text::fromT(search[0])) != aResult->getTTH()) {
				droppedResults++;
				PostMessage(WM_SPEAKER, FILTER_RESULT);
				return;
			}
		} else {
			// match all here
			for(TStringIter j = search.begin(); j != search.end(); ++j) {
				if((*j->begin() != _T('-') && Util::findSubString(aResult->getFile(), Text::fromT(*j)) == -1) ||
					(*j->begin() == _T('-') && j->size() != 1 && Util::findSubString(aResult->getFile(), Text::fromT(j->substr(1))) != -1)
					)
				{
					droppedResults++;
					PostMessage(WM_SPEAKER, FILTER_RESULT);
					return;
				}
			}
		}
	}

	// Reject results without free slots
	if((onlyFree && aResult->getFreeSlots() < 1))
	{
		droppedResults++;
		PostMessage(WM_SPEAKER, FILTER_RESULT);
		return;
	}

	SearchInfo* i = new SearchInfo(aResult);
	PostMessage(WM_SPEAKER, ADD_RESULT, (LPARAM)i);
}

LRESULT SearchFrame::onTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
	int32_t waitFor = SearchManager::getInstance()->timeToSearch();
	if(waitFor > 0) {
		AutoArray<TCHAR> buf(TSTRING(SEARCHING_WAIT).size() + 16);
		_stprintf(buf, CTSTRING(SEARCHING_WAIT), waitFor);

		ctrlStatus.SetText(1, buf);
		SetWindowText((TSTRING(SEARCH) + _T(" - ") + tstring(buf)).c_str());
	} else {
		if(timerID != 0) {
			KillTimer(timerID);
			timerID = 0;
		}

		ctrlStatus.SetText(1, (TSTRING(SEARCHING_READY)).c_str());
		SetWindowText((TSTRING(SEARCH) + _T(" - ") + TSTRING(SEARCHING_READY)).c_str());
	}

	ctrlStatus.SetText(2, _T(""));
	ctrlStatus.SetText(3, _T(""));
	return 0;
}

void SearchFrame::SearchInfo::view() {
	try {
		if(sr->getType() == SearchResult::TYPE_FILE) {
			QueueManager::getInstance()->add(Util::getTempPath() + sr->getFileName(),
				sr->getSize(), sr->getTTH(), sr->getUser(), 
				QueueItem::FLAG_CLIENT_VIEW | QueueItem::FLAG_TEXT);
		}
	} catch(const Exception&) {
	}
}

void SearchFrame::SearchInfo::Download::operator()(SearchInfo* si) {
	try {
		if(si->sr->getType() == SearchResult::TYPE_FILE) {
			string target = Text::fromT(tgt + si->columns[COLUMN_FILENAME]);
			QueueManager::getInstance()->add(target, si->sr->getSize(),
				si->sr->getTTH(), si->sr->getUser());

			if(WinUtil::isShift())
				QueueManager::getInstance()->setPriority(target, QueueItem::HIGHEST);
		} else {
			QueueManager::getInstance()->addDirectory(si->sr->getFile(), si->sr->getUser(), Text::fromT(tgt),
				WinUtil::isShift() ? QueueItem::HIGHEST : QueueItem::DEFAULT);
		}
	} catch(const Exception&) {
	}
}

void SearchFrame::SearchInfo::DownloadWhole::operator()(SearchInfo* si) {
	try {
		QueueItem::Priority prio = WinUtil::isShift() ? QueueItem::HIGHEST : QueueItem::DEFAULT;
		if(si->sr->getType() == SearchResult::TYPE_FILE) {
			QueueManager::getInstance()->addDirectory(Text::fromT(si->columns[COLUMN_PATH]), 
				si->sr->getUser(), Text::fromT(tgt), prio);
		} else {
			QueueManager::getInstance()->addDirectory(si->sr->getFile(), si->sr->getUser(), 
				Text::fromT(tgt), prio);
		}
	} catch(const Exception&) {
	}
}

void SearchFrame::SearchInfo::DownloadTarget::operator()(SearchInfo* si) {
	try {
		if(si->sr->getType() == SearchResult::TYPE_FILE) {
			string target = Text::fromT(tgt);
			QueueManager::getInstance()->add(target, si->sr->getSize(),
				si->sr->getTTH(), si->sr->getUser());

			if(WinUtil::isShift())
				QueueManager::getInstance()->setPriority(target, QueueItem::HIGHEST);
		} else {
			QueueManager::getInstance()->addDirectory(si->sr->getFile(), si->sr->getUser(), Text::fromT(tgt),
				WinUtil::isShift() ? QueueItem::HIGHEST : QueueItem::DEFAULT);
		}
	} catch(const Exception&) {
	}
}

void SearchFrame::SearchInfo::getList() {
	try {
		WinUtil::addInitalDir(sr->getUser(), Text::fromT(columns[COLUMN_PATH]));
		QueueManager::getInstance()->addList(sr->getUser(), QueueItem::FLAG_CLIENT_VIEW);
	} catch(const Exception&) {
		// Ignore for now...
	}
}

void SearchFrame::SearchInfo::browseList() {
	try {
		QueueManager::getInstance()->addPfs(sr->getUser(), Text::fromT(columns[COLUMN_PATH]));
	} catch(const Exception&) {
		// Ignore for now...
	}
}

void SearchFrame::SearchInfo::CheckTTH::operator()(SearchInfo* si) {
	if(firstTTH) {
		tth = si->columns[COLUMN_TTH];
		hasTTH = true;
		firstTTH = false;
	} else if(hasTTH) {
		if(tth != si->columns[COLUMN_TTH]) {
			hasTTH = false;
		}
	}

	if(firstHubs && hubs.empty()) {
		hubs = ClientManager::getInstance()->getHubs(si->sr->getUser()->getCID());
		firstHubs = false;
	} else if(!hubs.empty()) {
		Util::intersect(hubs, ClientManager::getInstance()->getHubs(si->sr->getUser()->getCID()));
	}
}

LRESULT SearchFrame::onDownloadTo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	if(ctrlResults.GetSelectedCount() == 1) {
		int i = ctrlResults.GetNextItem(-1, LVNI_SELECTED);
		dcassert(i != -1);
		SearchInfo* si = ctrlResults.getItemData(i);
		SearchResult* sr = si->sr;

		if(sr->getType() == SearchResult::TYPE_FILE) {
			tstring target = Text::toT(SETTING(DOWNLOAD_DIRECTORY)) + si->columns[COLUMN_FILENAME];
			if(WinUtil::browseFile(target, m_hWnd)) {
				WinUtil::addLastDir(Util::getFilePath(target));
				ctrlResults.forEachSelectedT(SearchInfo::DownloadTarget(target));
			}
		} else {
			tstring target = Text::toT(SETTING(DOWNLOAD_DIRECTORY));
			if(WinUtil::browseDirectory(target, m_hWnd)) {
				WinUtil::addLastDir(target);
				ctrlResults.forEachSelectedT(SearchInfo::Download(target));
			}
		}
	} else {
		tstring target = Text::toT(SETTING(DOWNLOAD_DIRECTORY));
		if(WinUtil::browseDirectory(target, m_hWnd)) {
			WinUtil::addLastDir(target);
			ctrlResults.forEachSelectedT(SearchInfo::Download(target));
		}
	}
	return 0;
}

LRESULT SearchFrame::onDownloadWholeTo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	tstring target = Text::toT(SETTING(DOWNLOAD_DIRECTORY));
	if(WinUtil::browseDirectory(target, m_hWnd)) {
		WinUtil::addLastDir(target);
		ctrlResults.forEachSelectedT(SearchInfo::DownloadWhole(target));
	}
	return 0;
}

LRESULT SearchFrame::onDownloadTarget(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	dcassert(wID >= IDC_DOWNLOAD_TARGET);
	size_t newId = (size_t)wID - IDC_DOWNLOAD_TARGET;

	if(newId < WinUtil::lastDirs.size()) {
		ctrlResults.forEachSelectedT(SearchInfo::Download(WinUtil::lastDirs[newId]));
	} else {
		dcassert((newId - WinUtil::lastDirs.size()) < targets.size());
		ctrlResults.forEachSelectedT(SearchInfo::DownloadTarget(Text::toT(targets[newId - WinUtil::lastDirs.size()])));
	}
	return 0;
}

LRESULT SearchFrame::onDownloadWholeTarget(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	dcassert((wID-IDC_DOWNLOAD_WHOLE_TARGET) < (int)WinUtil::lastDirs.size());
	ctrlResults.forEachSelectedT(SearchInfo::DownloadWhole(WinUtil::lastDirs[wID-IDC_DOWNLOAD_WHOLE_TARGET]));
	return 0;
}

LRESULT SearchFrame::onDownloadFavoriteDirs(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	dcassert(wID >= IDC_DOWNLOAD_FAVORITE_DIRS);
	size_t newId = (size_t)wID - IDC_DOWNLOAD_FAVORITE_DIRS;

	StringPairList spl = FavoriteManager::getInstance()->getFavoriteDirs();
	if(newId < spl.size()) {
		ctrlResults.forEachSelectedT(SearchInfo::Download(Text::toT(spl[newId].first)));
	} else {
		dcassert((newId - spl.size()) < targets.size());
		ctrlResults.forEachSelectedT(SearchInfo::DownloadTarget(Text::toT(targets[newId - spl.size()])));
	}
	return 0;
}

LRESULT SearchFrame::onDownloadWholeFavoriteDirs(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	StringPairList spl = FavoriteManager::getInstance()->getFavoriteDirs();
	dcassert((wID-IDC_DOWNLOAD_WHOLE_FAVORITE_DIRS) < (int)spl.size());
	ctrlResults.forEachSelectedT(SearchInfo::DownloadWhole(Text::toT(spl[wID-IDC_DOWNLOAD_WHOLE_FAVORITE_DIRS].first)));
	return 0;
}

LRESULT SearchFrame::onDoubleClickResults(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/) {
	ctrlResults.forEachSelectedT(SearchInfo::Download(Text::toT(SETTING(DOWNLOAD_DIRECTORY))));
	return 0;
}

LRESULT SearchFrame::onClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	if(!closed) {
		SearchManager::getInstance()->removeListener(this);
 		ClientManager* clientMgr = ClientManager::getInstance();
 		clientMgr->removeListener(this);

		frames.erase(m_hWnd);

		closed = true;
		PostMessage(WM_CLOSE);
		return 0;
	} else {
		for(int i = 0; i < ctrlResults.GetItemCount(); i++) {
			delete ctrlResults.getItemData(i);
		}
		ctrlResults.DeleteAllItems();
		for(int i = 0; i < ctrlHubs.GetItemCount(); i++) {
			delete ctrlHubs.getItemData(i);
		}
		ctrlHubs.DeleteAllItems();

		WinUtil::saveHeaderOrder(ctrlResults, SettingsManager::SEARCHFRAME_ORDER,
			SettingsManager::SEARCHFRAME_WIDTHS, COLUMN_LAST, columnIndexes, columnSizes);

		bHandled = FALSE;
		return 0;
	}
}

void SearchFrame::UpdateLayout(BOOL bResizeBars)
{
	RECT rect;
	GetClientRect(&rect);
	// position bars and offset their dimensions
	UpdateBarsPosition(rect, bResizeBars);

	if(ctrlStatus.IsWindow()) {
		CRect sr;
		int w[4];
		ctrlStatus.GetClientRect(sr);
		int tmp = (sr.Width()) > 316 ? 216 : ((sr.Width() > 116) ? sr.Width()-100 : 16);

		w[0] = 15;
		w[1] = sr.right - tmp;
		w[2] = w[1] + (tmp-16)/2;
		w[3] = w[1] + (tmp-16);

		ctrlStatus.SetParts(4, w);

		// Layout showUI button in statusbar part #0
		ctrlStatus.GetRect(0, sr);
		ctrlShowUI.MoveWindow(sr);
	}

	if(showUI)
	{
		int const width = 220, spacing = 50, labelH = 16, comboH = 140, lMargin = 2, rMargin = 4;
		CRect rc = rect;

		rc.left += width;
		ctrlResults.MoveWindow(rc);

		// "Search for"
		rc.right = width - rMargin;
		rc.left = lMargin;
		rc.top += 25;
		rc.bottom = rc.top + comboH + 21;
		ctrlSearchBox.MoveWindow(rc);

		searchLabel.MoveWindow(rc.left + lMargin, rc.top - labelH, width - rMargin, labelH-1);

		// "Purge"
		rc.right = rc.left + spacing;
		rc.left = lMargin;
		rc.top += 25;
		rc.bottom = rc.top + 21;
		ctrlPurge.MoveWindow(rc);

		// "Size"
		int w2 = width - rMargin - lMargin;
		rc.top += spacing;
		rc.bottom = rc.top + comboH;
		rc.right = w2/3;
		ctrlMode.MoveWindow(rc);

		sizeLabel.MoveWindow(rc.left + lMargin, rc.top - labelH, width - rMargin, labelH-1);

		rc.left = rc.right + lMargin;
		rc.right += w2/3;
		rc.bottom = rc.top + 21;
		ctrlSize.MoveWindow(rc);

		rc.left = rc.right + lMargin;
		rc.right = width - rMargin;
		rc.bottom = rc.top + comboH;
		ctrlSizeMode.MoveWindow(rc);

		// "File type"
		rc.left = lMargin;
		rc.right = width - rMargin;
		rc.top += spacing;
		rc.bottom = rc.top + comboH + 21;
		ctrlFiletype.MoveWindow(rc);
		rc.bottom -= comboH;

		typeLabel.MoveWindow(rc.left + lMargin, rc.top - labelH, width - rMargin, labelH-1);

		// "Search options"
		rc.left = lMargin;
		rc.right = width - rMargin;
		rc.top += spacing;
		rc.bottom += spacing;
		ctrlSlots.MoveWindow(rc);

		optionLabel.MoveWindow(rc.left + lMargin, rc.top - labelH, width - rMargin, labelH-1);

		// "Hubs"
		rc.left = lMargin;
		rc.right = width - rMargin;
		rc.top += spacing;
		rc.bottom = rc.top + comboH;
		if (rc.bottom + labelH + 21 > rect.bottom) {
			rc.bottom = rect.bottom - labelH - 21;
			if (rc.bottom < rc.top + (labelH*3)/2)
				rc.bottom = rc.top + (labelH*3)/2;
		}

		ctrlHubs.MoveWindow(rc);

		hubsLabel.MoveWindow(rc.left + lMargin, rc.top - labelH, width - rMargin, labelH-1);

		// "Search"
		rc.right = width - rMargin;
		rc.left = rc.right - 100;
		rc.top = rc.bottom + labelH;
		rc.bottom = rc.top + 21;
		ctrlDoSearch.MoveWindow(rc);
	}
	else
	{
		CRect rc = rect;
		ctrlResults.MoveWindow(rc);

		rc.SetRect(0,0,0,0);
		ctrlSearchBox.MoveWindow(rc);
		ctrlMode.MoveWindow(rc);
		ctrlPurge.MoveWindow(rc);
		ctrlSize.MoveWindow(rc);
		ctrlSizeMode.MoveWindow(rc);
		ctrlFiletype.MoveWindow(rc);
	}

	POINT pt;
	pt.x = 10;
	pt.y = 10;
	HWND hWnd = ctrlSearchBox.ChildWindowFromPoint(pt);
	if(hWnd != NULL && !ctrlSearch.IsWindow() && hWnd != ctrlSearchBox.m_hWnd) {
		ctrlSearch.Attach(hWnd);
		searchContainer.SubclassWindow(ctrlSearch.m_hWnd);
	}
}

void SearchFrame::runUserCommand(UserCommand& uc) {
	if(!WinUtil::getUCParams(m_hWnd, uc, ucLineParams))
		return;

	StringMap ucParams = ucLineParams;

	set<CID> users;

	int sel = -1;
	while((sel = ctrlResults.GetNextItem(sel, LVNI_SELECTED)) != -1) {
		SearchResult* sr = ctrlResults.getItemData(sel)->sr;

		if(!sr->getUser()->isOnline())
			continue;

		if(uc.getType() == UserCommand::TYPE_RAW_ONCE) {
			if(users.find(sr->getUser()->getCID()) != users.end())
				continue;
			users.insert(sr->getUser()->getCID());
		}

		ucParams["fileFN"] = sr->getFile();
		ucParams["fileSI"] = Util::toString(sr->getSize());
		ucParams["fileSIshort"] = Util::formatBytes(sr->getSize());
		if(sr->getType() == SearchResult::TYPE_FILE) {
			ucParams["fileTR"] = sr->getTTH().toBase32();
		}

		// compatibility with 0.674 and earlier
		ucParams["file"] = ucParams["fileFN"];
		ucParams["filesize"] = ucParams["fileSI"];
		ucParams["filesizeshort"] = ucParams["fileSIshort"];
		ucParams["tth"] = ucParams["fileTR"];

		StringMap tmp = ucParams;
		ClientManager::getInstance()->userCommand(sr->getUser(), uc, tmp, true);
	}
}

LRESULT SearchFrame::onCtlColor(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/) {
	HWND hWnd = (HWND)lParam;
	HDC hDC = (HDC)wParam;

	if(hWnd == searchLabel.m_hWnd || hWnd == sizeLabel.m_hWnd || hWnd == optionLabel.m_hWnd || hWnd == typeLabel.m_hWnd
		|| hWnd == hubsLabel.m_hWnd || hWnd == ctrlSlots.m_hWnd) {
		::SetBkColor(hDC, ::GetSysColor(COLOR_3DFACE));
		::SetTextColor(hDC, ::GetSysColor(COLOR_BTNTEXT));
		return (LRESULT)::GetSysColorBrush(COLOR_3DFACE);
	} else {
		::SetBkColor(hDC, WinUtil::bgColor);
		::SetTextColor(hDC, WinUtil::textColor);
		return (LRESULT)WinUtil::bgBrush;
	}
}

LRESULT SearchFrame::onChar(UINT uMsg, WPARAM wParam, LPARAM /*lParam*/, BOOL& bHandled) {
	switch(wParam) {
	case VK_TAB:
		if(uMsg == WM_KEYDOWN) {
			onTab(WinUtil::isShift());
		}
		break;
	case VK_RETURN:
		if( WinUtil::isShift() || WinUtil::isCtrl() || WinUtil::isAlt() ) {
			bHandled = FALSE;
		} else {
			if(uMsg == WM_KEYDOWN) {
				onEnter();
			}
		}
		break;
	default:
		bHandled = FALSE;
	}
	return 0;
}

void SearchFrame::onTab(bool shift) {
	HWND wnds[] = {
		ctrlSearch.m_hWnd, ctrlPurge.m_hWnd, ctrlMode.m_hWnd, ctrlSize.m_hWnd, ctrlSizeMode.m_hWnd,
		ctrlFiletype.m_hWnd, ctrlSlots.m_hWnd, ctrlDoSearch.m_hWnd, ctrlSearch.m_hWnd,
		ctrlResults.m_hWnd
	};

	HWND focus = GetFocus();
	if(focus == ctrlSearchBox.m_hWnd)
		focus = ctrlSearch.m_hWnd;

	static const int size = sizeof(wnds) / sizeof(wnds[0]);
	int i;
	for(i = 0; i < size; i++) {
		if(wnds[i] == focus)
			break;
	}

	::SetFocus(wnds[(i + (shift ? -1 : 1)) % size]);
}

LRESULT SearchFrame::onSearchByTTH(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	if(ctrlResults.GetSelectedCount() == 1) {
		int i = ctrlResults.GetNextItem(-1, LVNI_SELECTED);
		SearchResult* sr = ctrlResults.getItemData(i)->sr;
		if(sr->getType() == SearchResult::TYPE_FILE) {
			WinUtil::searchHash(sr->getTTH());
		}
	}

	return 0;
}

LRESULT SearchFrame::onBitziLookup(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	if(ctrlResults.GetSelectedCount() == 1) {
		int i = ctrlResults.GetNextItem(-1, LVNI_SELECTED);
		SearchResult* sr = ctrlResults.getItemData(i)->sr;
		if(sr->getType() == SearchResult::TYPE_FILE) {
			WinUtil::bitziLink(sr->getTTH());
		}
	}
	return 0;
}

LRESULT SearchFrame::onCopyMagnet(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	if(ctrlResults.GetSelectedCount() == 1) {
		int i = ctrlResults.GetNextItem(-1, LVNI_SELECTED);
		SearchResult* sr = ctrlResults.getItemData(i)->sr;
		if(sr->getType() == SearchResult::TYPE_FILE) {
			WinUtil::copyMagnet(sr->getTTH(), Text::toT(sr->getFileName()));
		}
	}
	return 0;
}


LRESULT SearchFrame::onSpeaker(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/) {
 	switch(wParam) {
	case ADD_RESULT:
		{
			SearchInfo* si = (SearchInfo*)lParam;
			SearchResult* sr = si->sr;
			// Check previous search results for dupes
			for(int i = 0, j = ctrlResults.GetItemCount(); i < j; ++i) {
				SearchInfo* si2 = ctrlResults.getItemData(i);
				SearchResult* sr2 = si2->sr;
				if((sr->getUser()->getCID() == sr2->getUser()->getCID()) && (sr->getFile() == sr2->getFile())) {
					delete si;
					return 0;
				}
			}

			int image = sr->getType() == SearchResult::TYPE_FILE ? WinUtil::getIconIndex(Text::toT(sr->getFile())) : WinUtil::getDirIconIndex();
			ctrlResults.insertItem(si, image);
			ctrlStatus.SetText(2, Text::toT(Util::toString(ctrlResults.GetItemCount()) + ' ' + STRING(ITEMS)).c_str());
			if (BOOLSETTING(BOLD_SEARCH)) {
				setDirty();
			}
		}
		break;
	case FILTER_RESULT:
		ctrlStatus.SetText(3, Text::toT(Util::toString(droppedResults) + ' ' + STRING(FILTERED)).c_str());
		break;
	case HUB_ADDED:
		onHubAdded((HubInfo*)(lParam));
		break;
	case HUB_CHANGED:
		onHubChanged((HubInfo*)(lParam));
		break;
	case HUB_REMOVED:
 		onHubRemoved((HubInfo*)(lParam));
		break;
 	}

	return 0;
}

LRESULT SearchFrame::onContextMenu(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled) {
	if (reinterpret_cast<HWND>(wParam) == ctrlResults && ctrlResults.GetSelectedCount() > 0) {
		POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };

		if(pt.x == -1 && pt.y == -1) {
			WinUtil::getContextMenuPos(ctrlResults, pt);
		}

		while(targetMenu.GetMenuItemCount() > 0) {
			targetMenu.DeleteMenu(0, MF_BYPOSITION);
		}
		while(targetDirMenu.GetMenuItemCount() > 0) {
			targetDirMenu.DeleteMenu(0, MF_BYPOSITION);
		}

		int n = 0;

		//Append favorite download dirs
		StringPairList spl = FavoriteManager::getInstance()->getFavoriteDirs();
		if (spl.size() > 0) {
			for(StringPairIter i = spl.begin(); i != spl.end(); i++) {
				targetMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD_FAVORITE_DIRS + n, Text::toT(i->second).c_str());
				n++;
			}
			targetMenu.AppendMenu(MF_SEPARATOR);
		}

		n = 0;
		targetMenu.AppendMenu(MF_STRING, IDC_DOWNLOADTO, CTSTRING(BROWSE));
		if(WinUtil::lastDirs.size() > 0) {
			targetMenu.AppendMenu(MF_SEPARATOR);
			for(TStringIter i = WinUtil::lastDirs.begin(); i != WinUtil::lastDirs.end(); ++i) {
				targetMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD_TARGET + n, i->c_str());
				n++;
			}
		}

		SearchInfo::CheckTTH cs = ctrlResults.forEachSelectedT(SearchInfo::CheckTTH());

		if(cs.hasTTH) {
			targets.clear();
			QueueManager::getInstance()->getTargets(TTHValue(Text::fromT(cs.tth)), targets);

			if(targets.size() > 0) {
				targetMenu.AppendMenu(MF_SEPARATOR);
				for(StringIter i = targets.begin(); i != targets.end(); ++i) {
					targetMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD_TARGET + n, Text::toT(*i).c_str());
					n++;
				}
			}
		}

		n = 0;
		//Append favorite download dirs
		if (spl.size() > 0) {
			for(StringPairIter i = spl.begin(); i != spl.end(); ++i) {
				targetDirMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD_WHOLE_FAVORITE_DIRS + n, Text::toT(i->second).c_str());
				n++;
			}
			targetDirMenu.AppendMenu(MF_SEPARATOR);
		}

		n = 0;
		targetDirMenu.AppendMenu(MF_STRING, IDC_DOWNLOADDIRTO, CTSTRING(BROWSE));
		if(WinUtil::lastDirs.size() > 0) {
			targetDirMenu.AppendMenu(MF_SEPARATOR);
			for(TStringIter i = WinUtil::lastDirs.begin(); i != WinUtil::lastDirs.end(); ++i) {
				targetDirMenu.AppendMenu(MF_STRING, IDC_DOWNLOAD_WHOLE_TARGET + n, i->c_str());
				n++;
			}
		}

		prepareMenu(resultsMenu, UserCommand::CONTEXT_SEARCH, cs.hubs);
		checkAdcItems(resultsMenu);
		resultsMenu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, m_hWnd);
		cleanMenu(resultsMenu);
		return TRUE;
	}
	bHandled = FALSE;
	return FALSE;
}

void SearchFrame::initHubs() {
	ctrlHubs.insertItem(new HubInfo(Util::emptyStringT, TSTRING(ONLY_WHERE_OP), false), 0);
	ctrlHubs.SetCheckState(0, false);

	ClientManager* clientMgr = ClientManager::getInstance();
	clientMgr->lock();
	clientMgr->addListener(this);

	Client::List& clients = clientMgr->getClients();

	Client::List::iterator it;
	Client::List::iterator endIt = clients.end();
	for(it = clients.begin(); it != endIt; ++it) {
		Client* client = *it;
		if (!client->isConnected())
			continue;

		onHubAdded(new HubInfo(Text::toT(client->getHubUrl()), Text::toT(client->getHubName()), client->getMyIdentity().isOp()));
	}

	clientMgr->unlock();
	ctrlHubs.SetColumnWidth(0, LVSCW_AUTOSIZE);

}

void SearchFrame::onHubAdded(HubInfo* info) {
	int nItem = ctrlHubs.insertItem(info, 0);
	ctrlHubs.SetCheckState(nItem, (ctrlHubs.GetCheckState(0) ? info->op : true));
	ctrlHubs.SetColumnWidth(0, LVSCW_AUTOSIZE);
}

void SearchFrame::onHubChanged(HubInfo* info) {
	int nItem = 0;
	int n = ctrlHubs.GetItemCount();
	for(; nItem < n; nItem++) {
		if(ctrlHubs.getItemData(nItem)->url == info->url)
			break;
	}
	if (nItem == n)
		return;

	delete ctrlHubs.getItemData(nItem);
	ctrlHubs.SetItemData(nItem, (DWORD_PTR)info);
	ctrlHubs.updateItem(nItem);

	if (ctrlHubs.GetCheckState(0))
		ctrlHubs.SetCheckState(nItem, info->op);

	ctrlHubs.SetColumnWidth(0, LVSCW_AUTOSIZE);
}

void SearchFrame::onHubRemoved(HubInfo* info) {
	int nItem = 0;
	int n = ctrlHubs.GetItemCount();
	for(; nItem < n; nItem++) {
		if(ctrlHubs.getItemData(nItem)->url == info->url)
			break;
	}
	if (nItem == n)
		return;

	delete ctrlHubs.getItemData(nItem);
	ctrlHubs.DeleteItem(nItem);
	ctrlHubs.SetColumnWidth(0, LVSCW_AUTOSIZE);
}

LRESULT SearchFrame::onGetList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	ctrlResults.forEachSelected(&SearchInfo::getList);
	return 0;
}

LRESULT SearchFrame::onBrowseList(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	ctrlResults.forEachSelected(&SearchInfo::browseList);
	return 0;
}

LRESULT SearchFrame::onItemChangedHub(int /* idCtrl */, LPNMHDR pnmh, BOOL& /* bHandled */) {
	NMLISTVIEW* lv = (NMLISTVIEW*)pnmh;
	if(lv->iItem == 0 && (lv->uNewState ^ lv->uOldState) & LVIS_STATEIMAGEMASK) {
		if (((lv->uNewState & LVIS_STATEIMAGEMASK) >> 12) - 1) {
			for(int iItem = 0; (iItem = ctrlHubs.GetNextItem(iItem, LVNI_ALL)) != -1; ) {
				HubInfo* client = ctrlHubs.getItemData(iItem);
				if (!client->op)
					ctrlHubs.SetCheckState(iItem, false);
			}
		}
	}

	return 0;
}

LRESULT SearchFrame::onPurge(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	ctrlSearchBox.ResetContent();
	lastSearches.clear();
	return 0;
}


void SearchFrame::SearchInfo::update() {
	if(sr->getType() == SearchResult::TYPE_FILE) {
		if(sr->getFile().rfind(_T('\\')) == tstring::npos) {
			columns[COLUMN_FILENAME] = Text::toT(sr->getFile());
		} else {
			columns[COLUMN_FILENAME] = Text::toT(Util::getFileName(sr->getFile()));
			columns[COLUMN_PATH] = Text::toT(Util::getFilePath(sr->getFile()));
		}

		columns[COLUMN_TYPE] = Text::toT(Util::getFileExt(Text::fromT(columns[COLUMN_FILENAME])));
		if(!columns[COLUMN_TYPE].empty() && columns[COLUMN_TYPE][0] == _T('.'))
			columns[COLUMN_TYPE].erase(0, 1);
		columns[COLUMN_SIZE] = Text::toT(Util::formatBytes(sr->getSize()));
		columns[COLUMN_EXACT_SIZE] = Text::toT(Util::formatExactSize(sr->getSize()));
	} else {
		columns[COLUMN_FILENAME] = Text::toT(sr->getFileName());
		columns[COLUMN_PATH] = Text::toT(sr->getFile());
		columns[COLUMN_TYPE] = TSTRING(DIRECTORY);
		if(sr->getSize() > 0) {
			columns[COLUMN_SIZE] = Text::toT(Util::formatBytes(sr->getSize()));
			columns[COLUMN_EXACT_SIZE] = Text::toT(Util::formatExactSize(sr->getSize()));
		}
	}
	columns[COLUMN_NICK] = WinUtil::getNicks(sr->getUser());
	columns[COLUMN_CONNECTION] = Text::toT(ClientManager::getInstance()->getConnection(sr->getUser()->getCID()));
	columns[COLUMN_HUB] = Text::toT(sr->getHubName());
	columns[COLUMN_SLOTS] = Text::toT(sr->getSlotString());
	columns[COLUMN_IP] = Text::toT(sr->getIP());
	if (!columns[COLUMN_IP].empty()) {
		// Only attempt to grab a country mapping if we actually have an IP address
		tstring tmpCountry = Text::toT(Util::getIpCountry(sr->getIP()));
		if(!tmpCountry.empty())
			columns[COLUMN_IP] = tmpCountry + _T(" (") + columns[COLUMN_IP] + _T(")");
	}
	if(sr->getType() == SearchResult::TYPE_FILE) {
        columns[COLUMN_TTH] = Text::toT(sr->getTTH().toBase32());
	}
	columns[COLUMN_CID] = Text::toT(sr->getUser()->getCID().toBase32());

}
