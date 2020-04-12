#include "HxCalendarWnd.h"



HxCalendarWnd::HxCalendarWnd()
{
}


HxCalendarWnd::~HxCalendarWnd()
{
}

void HxCalendarWnd::InitWindow()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_monthcal_close")));
	m_pBeginCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_begin_year_month")));
	m_pEndCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_end_year_month")));

// 	::GetLocalTime(&m_sysTime);
// 	CDuiString sText;
// 	sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
// 	if (m_pBeginCurentDate)
// 		m_pBeginCurentDate->SetText(sText);
// 	m_CurYear = m_sysTime.wYear;
// 	m_CurMonth = m_sysTime.wMonth;
// 	SetBeginDateInList(/*m_sysTime.wYear,m_sysTime.wMonth*/m_CurYear, m_CurMonth);
// 
// 	sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
// 	if (m_pEndCurentDate)
// 		m_pEndCurentDate->SetText(sText);
// 	SetEndDateInList(m_CurYear, m_CurMonth);
}

void HxCalendarWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();

	if (msg.sType == _T("windowinit"))
	{
		::GetLocalTime(&m_sysTime);
		CDuiString sText;
		sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
		if(m_pBeginCurentDate)
			m_pBeginCurentDate->SetText(sText);
		//UINT istr = m_sysTime.wDay;
		//InsertList(m_sysTime.wYear,m_sysTime.wMonth);
		m_CurYear = m_sysTime.wYear;
		m_CurMonth = m_sysTime.wMonth;
		SetBeginDateInList(/*m_sysTime.wYear,m_sysTime.wMonth*/m_CurYear, m_CurMonth);

		sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
		if (m_pEndCurentDate)
			m_pEndCurentDate->SetText(sText);
		SetEndDateInList(m_CurYear, m_CurMonth);
	}
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (strName.CompareNoCase(_T("closebtn")) == 0)
		{
			Close(IDCANCEL);
			return;
		}
		//单击下个月份
		if (msg.pSender->GetName() == _T("btn_begin_month_next"))
		{
			CDuiString sText;
			UINT SelMonth = m_CurMonth % 12;
			if (SelMonth == 0)
			{
				//SetDateInList(m_CurYear+1,SelMonth+1);
				++m_CurYear;
				m_CurMonth -= 11;
			}
			else
			{
				//SetDateInList(m_CurYear,SelMonth+1);
				++m_CurMonth;
			}
			SetBeginDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击上个月份
		if (msg.pSender->GetName() == _T("btn_begin_month_last"))
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
			SetBeginDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击下一年份
		if (msg.pSender->GetName() == _T("btn_begin_year_next"))
		{
			CDuiString sText;
			++m_CurYear;
			SetBeginDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pBeginCurentDate->SetText(sText);
		}
		//单击上一年份
		if (msg.pSender->GetName() == _T("btn_begin_year_last"))
		{
			CDuiString sText;
			--m_CurYear;
			SetBeginDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pBeginCurentDate->SetText(sText);
		}

		// end
		//单击下个月份
		if (msg.pSender->GetName() == _T("btn_end_month_next"))
		{
			CDuiString sText;
			UINT SelMonth = m_CurMonth % 12;
			if (SelMonth == 0)
			{
				//SetDateInList(m_CurYear+1,SelMonth+1);
				++m_CurYear;
				m_CurMonth -= 11;
			}
			else
			{
				//SetDateInList(m_CurYear,SelMonth+1);
				++m_CurMonth;
			}
			SetEndDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击上个月份
		if (msg.pSender->GetName() == _T("btn_end_month_last"))
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
			SetEndDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击下一年份
		if (msg.pSender->GetName() == _T("btn_end_year_next"))
		{
			CDuiString sText;
			++m_CurYear;
			SetEndDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pEndCurentDate->SetText(sText);
		}
		//单击上一年份
		if (msg.pSender->GetName() == _T("btn_end_year_last"))
		{
			CDuiString sText;
			--m_CurYear;
			SetEndDateInList(m_CurYear, m_CurMonth);
			sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
			m_pEndCurentDate->SetText(sText);
		}
	}
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

void HxCalendarWnd::SetBeginDateInList(UINT year, UINT month)
{
	CListUI *pList = static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
	if (pList == NULL)
	{
		return;
	}

	pList->RemoveAll();

	//初始化数组
	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			m_Array[i][j] = 0;
		}
	}
	//pList->SetTextCallback(this);
	InsertList(pList, year, month);
}

void HxCalendarWnd::SetEndDateInList(UINT year, UINT month)
{
	CListUI *pList = static_cast<CListUI*>(m_pm.FindControl("EndDateList"));
	if (pList == NULL)
	{
		return;
	}

	pList->RemoveAll();

	//初始化数组
	for (UINT i = 0; i < 6; i++)
	{
		for (UINT j = 0; j < 7; j++)
		{
			m_Array[i][j] = 0;
		}
	}
	//pList->SetTextCallback(this);
	InsertList(pList, year, month);
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

		CListTextElementUI* pListElement = new CListTextElementUI;
		//CListContainerElementUI* pListElement = new CListContainerElementUI;
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

LPCTSTR HxCalendarWnd::GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
{
	TCHAR szBuf[MAX_PATH] = { 0 };
	CDuiString sText;
	sText.SmallFormat(_T("%d"), m_Array[iIndex][iSubItem]);
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
	//CListContainerElementUI* pListElement = (CListContainerElementUI*)lParam;
	CListUI*pListBegin = static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
	if (pListBegin)
		pListBegin->Add(pListElement);

	// 		CListUI*pListEnd = static_cast<CListUI*>(m_pm.FindControl("EndDateList"));
	// 		if (pListEnd)
	// 			pListEnd->Add(pListElement);
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