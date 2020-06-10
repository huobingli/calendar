#include "HxCalendarWnd.h"

//////////////////////////////////////////////////////////////////////////
MonthCalendar::MonthCalendar()
{
	//m_vcDays.clear();
}

MonthCalendar::~MonthCalendar()
{

}

void MonthCalendar::Request()
{

}

void MonthCalendar::ParseReturn()
{
	Json::Reader JsonReader;
	Json::Value JsonValue;


}

//////////////////////////////////////////////////////////////////////////
HxCalendarUI::HxCalendarUI()
{

}

HxCalendarUI::~HxCalendarUI()
{

}

PVOID HxCalendarUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcsicmp(pstrName, "HxCalendarUI") == 0)
	{
		return static_cast<HxCalendarUI*>(this);
	}

	return CTileLayoutUI::GetInterface(pstrName);
}

//////////////////////////////////////////////////////////////////////////
CCalendarItemUI::CCalendarItemUI()
{
}


CCalendarItemUI::~CCalendarItemUI(void)
{
	if (m_hIcon != NULL)
		::DestroyIcon(m_hIcon);
}

void CCalendarItemUI::DoEvent(DuiLib::TEventUI& event)
{
	if (event.Type == DuiLib::UIEVENT_DBLCLICK)
	{
		m_pManager->SendNotify(this, _T("ldbclick"), event.wParam, event.lParam);
		m_pManager->ReleaseCapture();
	}

	if (event.Type == DuiLib::UIEVENT_SETCURSOR)
	{
		::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_ARROW)));
		return;
	}

	if (event.Type == DuiLib::UIEVENT_BUTTONUP)
	{
		int i = 0;
	}

	if (event.Type == DuiLib::UIEVENT_BUTTONDOWN)
	{
		int i = 0;
	}

	return COptionUI::DoEvent(event);
}

void CCalendarItemUI::PaintStatusImage(HDC hDC)
{
	COptionUI::PaintStatusImage(hDC);
	if (m_hIcon != NULL)
	{
		ICONINFO ii;
		if (::GetIconInfo(m_hIcon, &ii))
		{
			BITMAP bmp;
			if (::GetObject(ii.hbmColor, sizeof(bmp), &bmp))
				::DrawIcon(hDC, m_rcItem.left + (m_rcItem.right - m_rcItem.left - bmp.bmWidth) / 2, m_rcItem.top + 4, m_hIcon);
			::DeleteObject(ii.hbmColor);
			::DeleteObject(ii.hbmMask);
		}
	}
}

void CCalendarItemUI::SetIcon(HICON hIcon)
{
	m_hIcon = hIcon;
}

//////////////////////////////////////////////////////////////////////////
HxCalendarWnd::HxCalendarWnd()
{
}


HxCalendarWnd::~HxCalendarWnd()
{

}

void HxCalendarWnd::ResetSelect()
{
	CTileLayoutUI* pList = static_cast<CTileLayoutUI*>(m_pm.FindControl("datelist"));
	if (pList == NULL)
	{
		return;
	}

	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
			if (pOption)
			{
				pOption->Selected(FALSE, FALSE);
			}
		}
	}
}

void HxCalendarWnd::InitTileList()
{
	CDuiString str = "datelist";
	CDuiString strGroup = "group";

	HxCalendarUI* pList = static_cast<HxCalendarUI*>(m_pm.FindControl(str));
	if (pList == NULL)
	{
		return;
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			CDialogBuilderCallbackEx callback;
			CDialogBuilder builder;
			CCalendarItemUI* pCalendar = static_cast<CCalendarItemUI*>(builder.Create(_T("CalendarItem.xml"), NULL, &callback, &m_pm));
			pList->Add(pCalendar);
			CDuiString str;
			str.Format(_T("%d"), i * j);
			//pGameItem->SetTag()
			pCalendar->SetText(str);
			pCalendar->SetGroup(strGroup);
		}
	}
}

void HxCalendarWnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_monthcal_close")));
	m_pCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_year_month")));

	// 获取当前时间 设置到
	::GetLocalTime(&m_sysTime);

	// 设置当前时间
	m_CurYear = m_sysTime.wYear;
	m_CurMonth = m_sysTime.wMonth;

	CDuiString sText;
	// 设置结束时间
	sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
	if (m_pCurentDate)
		m_pCurentDate->SetText(sText);
	InitTileList();
	SetDateInList(m_CurYear, m_CurMonth);
}

void HxCalendarWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (strName.CompareNoCase(_T("lab_year_month")) == 0)
		{
			int n = 0;
		}

		if (strName.CompareNoCase(_T("CalendarItem")) == 0)
		{
			//m_strSelectDate = msg.pSender->GetText();

			CCalendarItemUI* pItem = static_cast<CCalendarItemUI*>(msg.pSender);
			if (pItem)
			{
				m_strSelectDate.SmallFormat(_T("%4d-%02d-%02d"), m_CurYear, m_CurMonth, atoi(pItem->GetText()));
			}
		}

// 		if (strName.CompareNoCase(_T("btn_monthcal_close")) == 0)
// 		{
// 			Close(IDCANCEL);
// 			return;
// 		}
		//单击下个月份
		if (msg.pSender->GetName() == _T("btn_month_next"))
		{
			CDuiString sText;
			UINT SelMonth = m_CurMonth % 12;
			if (SelMonth == 0)
			{
				++m_CurYear;
				m_CurMonth -= 11;
			}
			else
			{
				++m_CurMonth;
			}
			SetDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pCurentDate->SetText(sText);
		}
		//单击上个月份
		if (msg.pSender->GetName() == _T("btn_month_last"))
		{
			CDuiString sText;
			UINT SelMonth = m_CurMonth % 12;
			if (SelMonth == 1)
			{
				--m_CurYear;
				m_CurMonth += 11;
			}
			else
			{
				--m_CurMonth;
			}
			SetDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pCurentDate->SetText(sText);
		}
		//单击下一年份
		if (msg.pSender->GetName() == _T("btn_year_next"))
		{
			CDuiString sText;
			++m_CurYear;
			SetDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pCurentDate->SetText(sText);
		}
		//单击上一年份
		if (msg.pSender->GetName() == _T("btn_year_last"))
		{
			CDuiString sText;
			--m_CurYear;
			SetDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pCurentDate->SetText(sText);
		}

		if (msg.pSender->GetName() == _T("CalendarItem"))
		{
			int n = 0;
		}
	}

	WindowImplBase::Notify(msg);
}

CControlUI* HxCalendarWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, "HxCalendarUI") == 0)
	{
		return new HxCalendarUI;
	}

	return WindowImplBase::CreateControl(pstrClass);
}

LRESULT HxCalendarWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

//获取该月的天数
UINT HxCalendarWnd::GetMonthOfDays(UINT year, UINT month)
{
	UINT mDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//12个月的天数(平年的情况)
															//闰年时，二月加一天
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	{
		mDay[1] = 29;
	}
	return mDay[month - 1];
}

UINT HxCalendarWnd::GetWeek(UINT year, UINT month, UINT day)
{
	UINT week;
	UINT sum_day = day;

	for (UINT i = 1; i < month; i++)
	{
		sum_day += GetMonthOfDays(year, i);
	}

	week = (year - 1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + sum_day) % 7;
	return week;
}

void HxCalendarWnd::SetDateInList(UINT year, UINT month)
{
	// 重置
	ResetSelect();

	// 	//初始化数组
	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			m_Array[i][j] = 0;
		}
	}

	SetDateInArray(year, month);

	HxCalendarUI* pList = static_cast<HxCalendarUI*>(m_pm.FindControl("datelist"));

	if (pList)
	{
		for (UINT i = 0; i < 6; i++)
		{
			for (UINT j = 0; j < 7; j++)
			{
				COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
				if (pOption)
				{
					if (m_Array[i][j] == 0)
					{
						pOption->SetText(_T(""));
						pOption->SetEnabled(false);
					}
					else if (j == 0 || j == 6)
					{
						CDuiString str;
						str.Format(_T("%d"), m_Array[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(false);
					}
					else
					{
						CDuiString str;
						str.Format(_T("%d"), m_Array[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(true);
					}
				}
			}
		}
	}
}

void HxCalendarWnd::InsertNewList(CTileLayoutUI *pList, UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				k++;
			}
		}
	}
}

void HxCalendarWnd::SetDateInArray(UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				m_Array[i][j] = k;
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				m_Array[i][j] = k;
				k++;
			}
		}
	}
}

void HxCalendarWnd::InsertList(CListUI *pList, UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				k++;
			}
		}

		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		if (pListElement != NULL)
		{
			if (pList)
			{
				pList->Add(pListElement);
				pListElement->SetOwner(pList);

			}
		}
	}

}

LPCTSTR HxCalendarWnd::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	CDuiString sText;
	//sText.SmallFormat(_T("%d"), m_Array[iIndex][iSubItem]);
	if (sText == "0")
	{
		sText = "";
	}
	_stprintf(szBuf,/*Array[iIndex][iSubItem]*/sText);
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}

LRESULT HxCalendarWnd::OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
	CListUI*pListBegin = static_cast<CListUI*>(m_pm.FindControl("datelist"));
	if (pListBegin)
		pListBegin->Add(pListElement);
	return 0;
}

LRESULT HxCalendarWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}

LRESULT HxCalendarWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
	if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
		_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 &&
		_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0)
		return HTCAPTION;

	if (!::IsZoomed(*this))
	{
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom)
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("TextUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}


//////////////////////////////////////////////////////////////////////////
HxMutiCalendarWnd::HxMutiCalendarWnd()
{
	m_dwProcess = clickprocess::startclick;
}


HxMutiCalendarWnd::~HxMutiCalendarWnd()
{

}

void HxMutiCalendarWnd::ResetEndSelect()
{
	CTileLayoutUI* pList = static_cast<CTileLayoutUI*>(m_pm.FindControl("EndDataList"));
	if (pList == NULL)
	{
		return;
	}

	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
			if (pOption)
			{
				pOption->Selected(FALSE, FALSE);
			}
		}
	}
}

void HxMutiCalendarWnd::ResetBeginSelect()
{
	CTileLayoutUI* pList = static_cast<CTileLayoutUI*>(m_pm.FindControl("BeginDataList"));
	if (pList == NULL)
	{
		return;
	}

	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
			if (pOption)
			{
				pOption->Selected(FALSE, FALSE);
			}
		}
	}
}


void HxMutiCalendarWnd::InitEndTileList(int nMode)
{
	CDuiString str = "BeginDataList";
	CDuiString strGroup = "BeginGroup";
	if (nMode == 0)
	{
		str = "EndDataList";
		strGroup = "EndGroup";
	}

	HxCalendarUI* pList = static_cast<HxCalendarUI*>(m_pm.FindControl(str));
	if (pList == NULL)
	{
		return ;
	}

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			CDialogBuilderCallbackEx callback;
			CDialogBuilder builder;
			CCalendarItemUI* pCalendar = static_cast<CCalendarItemUI*>(builder.Create(_T("CalendarItem.xml"), NULL, &callback, &m_pm));
			pList->Add(pCalendar);
			CDuiString str;
			str.Format(_T("%d"), i * j);
			//pGameItem->SetTag()
			pCalendar->SetText(str);
			pCalendar->SetGroup(strGroup);
		}
	}
}

void HxMutiCalendarWnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_monthcal_close")));
	m_pBeginCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_begin_year_month")));
	m_pEndCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_end_year_month")));

	// 获取当前时间 设置到
	::GetLocalTime(&m_sysTime);

	// 设置当前时间
	m_EndCurYear = m_sysTime.wYear;
	m_EndCurMonth = m_sysTime.wMonth;
	
	

	CDuiString sText;
	// 设置结束时间
	sText.SmallFormat(_T("%4d-%02d"), m_EndCurYear, m_EndCurMonth);
	if (m_pEndCurentDate)
		m_pEndCurentDate->SetText(sText);
	InitEndTileList(0);
	SetEndDateInList(m_EndCurYear, m_EndCurMonth);

	// 设置开始时间
	m_BeginCurMonth = m_EndCurMonth;
	m_BeginCurYear = m_EndCurYear;
	if (m_EndCurMonth == 1)
	{
		m_BeginCurMonth = 12;
		--m_BeginCurYear;
	}
	else
	{
		--m_BeginCurMonth;
	}

	sText.SmallFormat(_T("%4d-%02d"), m_BeginCurYear, m_BeginCurMonth);
	if (m_pBeginCurentDate)
		m_pBeginCurentDate->SetText(sText);
	
	//SetBeginDateInList(/*m_sysTime.wYear,m_sysTime.wMonth*/m_CurYear, m_CurMonth);
	InitEndTileList(1);
	SetBeginDateInList(m_BeginCurYear, m_BeginCurMonth);
}

void HxMutiCalendarWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (strName.CompareNoCase(_T("lab_begin_year_month")) == 0)
		{
			int n = 0;
		}

		if (strName.CompareNoCase(_T("CalendarItem")) == 0)
		{
			CDuiString str = msg.pSender->GetText();
			
			CCalendarItemUI* pItem = static_cast<CCalendarItemUI*>(msg.pSender);
			if (pItem)
			{
				
				if (clickprocess::startclick == m_dwProcess)
				{
					pItem->SetGroup("1");
					m_dwProcess = firstclick;
					m_strBeginDate.SmallFormat(_T("%4d-%02d-%02d"), m_BeginCurYear, m_BeginCurMonth, atoi(pItem->GetText()));
				}
				else if(m_dwProcess == firstclick)
				{
					m_dwProcess = secondclick;
					pItem->SetGroup(_T("2"));
					m_dwProcess = endclick;
					m_strEndDate.SmallFormat(_T("%4d-%02d-%02d"), m_EndCurYear, m_EndCurMonth, atoi(pItem->GetText()));
				}
			}

			CDuiString strSelectTime;
			
			strSelectTime = m_strBeginDate + _T(" - ") + m_strEndDate;
			

		}

		if (strName.CompareNoCase(_T("btn_monthcal_close")) == 0)
		{
			Close(IDCANCEL);
			//return;
		}
		//单击下个月份
		if (msg.pSender->GetName() == _T("btn_begin_month_next"))
		{
			CDuiString sText;
			UINT SelMonth = m_BeginCurMonth % 12;
			if (SelMonth == 0)
			{
				//SetDateInList(m_CurYear+1,SelMonth+1);
				++m_BeginCurYear;
				m_BeginCurMonth -= 11;
			}
			else
			{
				//SetDateInList(m_CurYear,SelMonth+1);
				++m_BeginCurMonth;
			}
			SetBeginDateInList(m_BeginCurYear, m_BeginCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_BeginCurYear, m_BeginCurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击上个月份
		if (msg.pSender->GetName() == _T("btn_begin_month_last"))
		{
			CDuiString sText;
			UINT SelMonth = m_BeginCurMonth % 12;
			if (SelMonth == 1)
			{
				--m_BeginCurYear;
				m_BeginCurMonth += 11;
			}
			else
			{
				--m_BeginCurMonth;
			}
			SetBeginDateInList(m_BeginCurYear, m_BeginCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_BeginCurYear, m_BeginCurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击下一年份
		if (msg.pSender->GetName() == _T("btn_begin_year_next"))
		{
			CDuiString sText;
			++m_BeginCurYear;
			SetBeginDateInList(m_BeginCurYear, m_BeginCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_BeginCurYear, m_BeginCurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击上一年份
		if (msg.pSender->GetName() == _T("btn_begin_year_last"))
		{
			CDuiString sText;
			--m_BeginCurYear;
			SetBeginDateInList(m_BeginCurYear, m_BeginCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_BeginCurYear, m_BeginCurMonth);
			m_pBeginCurentDate->SetText(sText);
		}

		// end
		//单击下个月份
		if (msg.pSender->GetName() == _T("btn_end_month_next"))
		{
			CDuiString sText;
			UINT SelMonth = m_EndCurMonth % 12;
			if (SelMonth == 0)
			{
				//SetDateInList(m_CurYear+1,SelMonth+1);
				++m_EndCurYear;
				m_EndCurMonth -= 11;
			}
			else
			{
				//SetDateInList(m_CurYear,SelMonth+1);
				++m_EndCurMonth;
			}
			SetEndDateInList(m_EndCurYear, m_EndCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_EndCurYear, m_EndCurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击上个月份
		if (msg.pSender->GetName() == _T("btn_end_month_last"))
		{
			CDuiString sText;
			UINT SelMonth = m_EndCurMonth % 12;
			if (SelMonth == 1)
			{
				--m_EndCurYear;
				m_EndCurMonth += 11;
			}
			else
			{
				--m_EndCurMonth;
			}
			SetEndDateInList(m_EndCurYear, m_EndCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_EndCurYear, m_EndCurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击下一年份
		if (msg.pSender->GetName() == _T("btn_end_year_next"))
		{
			CDuiString sText;
			++m_EndCurYear;
			SetEndDateInList(m_EndCurYear, m_EndCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_EndCurYear, m_EndCurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击上一年份
		if (msg.pSender->GetName() == _T("btn_end_year_last"))
		{
			CDuiString sText;
			--m_EndCurYear;
			SetEndDateInList(m_EndCurYear, m_EndCurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_EndCurYear, m_EndCurMonth);
			m_pEndCurentDate->SetText(sText);
		}

		if (msg.pSender->GetName() == _T("CalendarItem"))
		{
			int n = 0;
		}
	}

	WindowImplBase::Notify(msg);
}

CControlUI* HxMutiCalendarWnd::CreateControl(LPCTSTR pstrClass)
{
	if (_tcsicmp(pstrClass, "HxCalendarUI") == 0)
	{
		return new HxCalendarUI;
	}

	return WindowImplBase::CreateControl(pstrClass);
}

LRESULT HxMutiCalendarWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

//获取该月的天数
UINT HxMutiCalendarWnd::GetMonthOfDays(UINT year, UINT month)
{
	UINT mDay[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };//12个月的天数(平年的情况)
															//闰年时，二月加一天
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	{
		mDay[1] = 29;
	}
	return mDay[month - 1];
}

UINT HxMutiCalendarWnd::GetWeek(UINT year, UINT month, UINT day)
{
	UINT week;
	UINT sum_day = day;

	for (UINT i = 1; i < month; i++)
	{
		sum_day += GetMonthOfDays(year, i);
	}

	week = (year - 1 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400 + sum_day) % 7;
	return week;
}

void HxMutiCalendarWnd::SetBeginDateInList(UINT year, UINT month)
{
	// 重置
	ResetBeginSelect();

	// 	//初始化数组
	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			m_BeginArray[i][j] = 0;
		}
	}

	SetBeginDateInArray(year, month);

	HxCalendarUI* pList = static_cast<HxCalendarUI*>(m_pm.FindControl("BeginDataList"));

	if (pList)
	{
		for (UINT i = 0; i < 6; i++)
		{
			for (UINT j = 0; j < 7; j++)
			{
				COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
				if (pOption)
				{
					if (m_BeginArray[i][j] == 0)
					{
						pOption->SetText(_T(""));
						pOption->SetEnabled(false);
					}
					else if (j == 0 || j == 6)
					{
						CDuiString str;
						str.Format(_T("%d"), m_BeginArray[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(false);
					}
					else
					{
						CDuiString str;
						str.Format(_T("%d"), m_BeginArray[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(true);
					}
				}
			}
		}
	}
}

void HxMutiCalendarWnd::SetEndDateInList(UINT year, UINT month)
{
	// 重置
	ResetBeginSelect();

	// 	//初始化数组
	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			m_EndArray[i][j] = 0;
		}
	}

	SetEndDateInArray(year, month);

	HxCalendarUI* pList = static_cast<HxCalendarUI*>(m_pm.FindControl("EndDataList"));

	if (pList)
	{
		for (UINT i = 0; i < 6; i++)
		{
			for (UINT j = 0; j < 7; j++)
			{
				COptionUI* pOption = static_cast<COptionUI*>(pList->GetItemAt(7 * i + j));
				if (pOption)
				{
					if (m_EndArray[i][j] == 0)
					{
						pOption->SetText(_T(""));
						pOption->SetEnabled(false);
					}
					else if (j == 0 || j == 6)
					{
						CDuiString str;
						str.Format(_T("%d"), m_EndArray[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(false);
					}
					else
					{
						CDuiString str;
						str.Format(_T("%d"), m_EndArray[i][j]);
						pOption->SetText(str);
						pOption->SetEnabled(true);
					}
				}
			}
		}
	}
}

void HxMutiCalendarWnd::InsertNewList(CTileLayoutUI *pList, UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				//m_Array[i][j] = k;
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				//m_Array[i][j] = k;
				k++;
			}
		}

		//CCalendarItemUI* pListElement = new CCalendarItemUI;
// 		CListTextElementUI* pListElement = new CListTextElementUI;
// 		pListElement->SetTag(i);
// 		if (pListElement != NULL)
// 		{
// 			if (pList)
// 			{
// 				pList->Add(pListElement);
// 				pListElement->SetOwner(pList);
// 
// 			}
// 		}

// 		CDialogBuilderCallbackEx callback;
// 		CDialogBuilder builder;
// 		CContainerUI* pGameItem = static_cast<CContainerUI*>(builder.Create(_T("CalendarItem.xml"), (UINT)0, &callback));
// 
// 		pList->Add(pGameItem);
// 		CDuiString str;
// 		str.Format("%d", m_Array[i]);
// 		pGameItem->SetText(str);
	}
}

void HxMutiCalendarWnd::SetBeginDateInArray(UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				m_BeginArray[i][j] = k;
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				m_BeginArray[i][j] = k;
				k++;
			}
		}
	}
}

void HxMutiCalendarWnd::SetEndDateInArray(UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				m_EndArray[i][j] = k;
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				m_EndArray[i][j] = k;
				k++;
			}
		}
	}
}

void HxMutiCalendarWnd::InsertList(CListUI *pList, UINT year, UINT month)
{
	UINT FirstDay;//该月份的第一天星期几
	UINT MonthOfDays;//该月的天数
	MonthOfDays = GetMonthOfDays(year, month);
	FirstDay = GetWeek(year, month, 1);
	UINT k = 1;

	for (UINT i = 0; i < 6; i++)
	{
		if (0 == i)
		{
			for (UINT j = FirstDay; j < 7; j++)
			{
				//m_Array[i][j] = k;
				k++;
			}
		}
		else
		{
			for (UINT j = 0; j < 7; j++)
			{
				if (k > MonthOfDays) break;
				//m_Array[i][j] = k;
				k++;
			}
		}

		//CCalendarItemUI* pListElement = new CCalendarItemUI;
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		if (pListElement != NULL)
		{
			//::PostMessage()
			//SendMessage(WM_ADDLISTITEM,0L,(LPARAM)pListElement);
			//CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
			//CListContainerElementUI* pListElement = (CListContainerElementUI*)lParam;
			//CListUI*pListBegin = static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
			if (pList)
			{
				pList->Add(pListElement);
				pListElement->SetOwner(pList);

			}
		}
	}

}

LPCTSTR HxMutiCalendarWnd::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	CDuiString sText;
	//sText.SmallFormat(_T("%d"), m_Array[iIndex][iSubItem]);
	if (sText == "0")
	{
		sText = "";
	}
	_stprintf(szBuf,/*Array[iIndex][iSubItem]*/sText);
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}

LRESULT HxMutiCalendarWnd::OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//CCalendarTextElementUI* pListElement = (CCalendarTextElementUI*)lParam;
	CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
	CListUI*pListBegin = static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
	if (pListBegin)
		pListBegin->Add(pListElement);

	// 		CListUI*pListEnd = static_cast<CListUI*>(m_pm.FindControl("EndDateList"));
	// 		if (pListEnd)
	// 			pListEnd->Add(pListElement);
	return 0;
}

LRESULT HxMutiCalendarWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}

LRESULT HxMutiCalendarWnd::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);
	//::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));

	if (m_dwProcess == clickprocess::firstclick)
	{
		if (pControl && _tcscmp(pControl->GetName(), _T("Calendaritem")) == 0)
		{
			CDuiString strClass = pControl->GetName();
			CCalendarItemUI* pItem = static_cast<CCalendarItemUI*>(pControl);
			if (pItem)
			{
				CDuiString strClass = pControl->GetName();
			}
			int n = 0;
		}
	}	

	return WindowImplBase::OnMouseMove(uMsg, wParam, lParam, bHandled);
}

LRESULT HxMutiCalendarWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt;
	pt.x = GET_X_LPARAM(lParam);
	pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);
	CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
	if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
		_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 &&
		_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0)
		return HTCAPTION;

	if (!::IsZoomed(*this))
	{
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom)
		{
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom)
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("TextUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}