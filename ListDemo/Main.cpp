///////////////////////////////////////////////////////////////////////
//说明：此例子仅显示日历的功能，没有添加点击日期的响应等功能，
//如有其他要求可以自己去修改程序。
//修改时间：2012-06-06
//作者：寻觅
///////////////////////////////////////////////////////////////////////

#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_DEPRECATE
#define  WM_ADDLISTITEM  WM_USER+1001

#include <vector>
#include <windows.h>
#include <objbase.h>

#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib,"..//bin//DuiLib_ud.lib")
#else
#pragma comment(lib,"..//bin//DuiLib_d.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment(lib,"..//bin//DuiLib_u.lib")
#else
#pragma comment(lib,"..//bin//DuiLib.lib")
#endif
#endif

UINT Array[6][7];

class CFameWindowWnd:public CWindowWnd,public INotifyUI,public IListCallbackUI
{
	
public:
	CFrameWindowWnd() {};

	LPCTSTR GetWindowClassName() const 
	{
		return _T("UIMainFrame");
	};

	UINT GetClassStyle() const
	{
		return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
	};

	void Init() 
	{
		m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_monthcal_close")));
		m_pBeginCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_begin_year_month")));
		m_pEndCurentDate = static_cast<CLabelUI*>(m_pm.FindControl(_T("lab_end_year_month")));
		/*m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_max")));
		m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_restore")));
		m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("btn_min")));

		CComboUI* pAccountCombo = static_cast<CComboUI*>(m_pm.FindControl(_T("ComboUI1")));
		CEditUI* pAccountEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("EditUI2")));
		if( pAccountCombo && pAccountEdit ) pAccountEdit->SetText(pAccountCombo->GetText());
		pAccountEdit->SetFocus();*/
	}

	void OnFinalMessage(HWND)
	{
		delete this;
	};

	void OnPrepare(void) 
	{
		//m_pCurentDate->SetText("");
		::GetLocalTime(&m_sysTime);		
		CStdString sText;
		sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
		m_pBeginCurentDate->SetText(sText);
		//UINT istr = m_sysTime.wDay;
		//InsertList(m_sysTime.wYear,m_sysTime.wMonth);
		m_CurYear = m_sysTime.wYear;
		m_CurMonth = m_sysTime.wMonth;
		SetBeginDateInList(/*m_sysTime.wYear,m_sysTime.wMonth*/m_CurYear,m_CurMonth);

		sText.SmallFormat(_T("%4d-%02d"), m_sysTime.wYear, m_sysTime.wMonth);
		m_pEndCurentDate->SetText(sText);
		SetEndDateInList(m_CurYear, m_CurMonth);
	}

	void Notify(TNotifyUI &msg)
	{
		if( msg.sType == _T("windowinit") ) 
			OnPrepare();
		if( msg.sType == _T("click"))
		{
			if(msg.pSender == m_pCloseBtn)
			{
				//Close();
				PostQuitMessage(0); // 因为activex的原因，使用close可能会出现错误
				return;
			}
			//单击下个月份
			if (msg.pSender->GetName() == _T("btn_begin_month_next"))
			{
				CStdString sText;
				UINT SelMonth = m_CurMonth%12;
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
				SetBeginDateInList(m_CurYear,m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pBeginCurentDate->SetText(sText);
			}
			//单击上个月份
			if (msg.pSender->GetName() == _T("btn_begin_month_last"))
			{
				CStdString sText;
				UINT SelMonth = m_CurMonth%12;
				if (SelMonth == 1)
				{
					--m_CurYear;
					m_CurMonth += 11;
				}
				else
				{
					--m_CurMonth;
				}
				SetBeginDateInList(m_CurYear,m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pBeginCurentDate->SetText(sText);
			}
			//单击下一年份
			if (msg.pSender->GetName() == _T("btn_begin_year_next"))
			{
				CStdString sText;
				++m_CurYear;
				SetBeginDateInList(m_CurYear,m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pBeginCurentDate->SetText(sText);
			}
			//单击上一年份
			if (msg.pSender->GetName() == _T("btn_begin_year_last"))
			{
				CStdString sText;
				--m_CurYear;
				SetBeginDateInList(m_CurYear,m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pBeginCurentDate->SetText(sText);
			}

			// end
			//单击下个月份
			if (msg.pSender->GetName() == _T("btn_end_month_next"))
			{
				CStdString sText;
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
				CStdString sText;
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
				CStdString sText;
				++m_CurYear;
				SetEndDateInList(m_CurYear, m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pEndCurentDate->SetText(sText);
			}
			//单击上一年份
			if (msg.pSender->GetName() == _T("btn_end_year_last"))
			{
				CStdString sText;
				--m_CurYear;
				SetEndDateInList(m_CurYear, m_CurMonth);
				sText.SmallFormat(_T("%4d-%02d"), m_CurYear, m_CurMonth);
				m_pEndCurentDate->SetText(sText);
			}
		}

	}
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pm.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI *pRoot = builder.Create(_T("MonthCal.xml"),(UINT)0,NULL,&m_pm);
		ASSERT(pRoot);
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		Init();

		return 0;
	}
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		return 0;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		::PostQuitMessage(0L);

		bHandled = FALSE;
		return 0;
	}

	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        if( ::IsIconic(*this) ) bHandled = FALSE;
        return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}

	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt; 
		pt.x = GET_X_LPARAM(lParam); 
		pt.y = GET_Y_LPARAM(lParam);
		::ScreenToClient(*this, &pt);

		RECT rcClient;
		::GetClientRect(*this, &rcClient);
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 && 
			_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0)
			return HTCAPTION;
	
		if( !::IsZoomed(*this) ) 
		{
			RECT rcSizeBox = m_pm.GetSizeBox();
			if( pt.y < rcClient.top + rcSizeBox.top ) 
			{
				if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
				return HTTOP;
			}
			else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) 
			{
				if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
				if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
				return HTBOTTOM;
			}
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
		}

		RECT rcCaption = m_pm.GetCaptionRect();
		if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
			&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) 
		{
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
				if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
					_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
					_tcscmp(pControl->GetClass(), _T("TextUI")) != 0 )
					return HTCAPTION;
		}

		return HTCLIENT;

	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
        SIZE szRoundCorner = m_pm.GetRoundCorner();
        if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) 
		{
            CRect rcWnd;
            ::GetWindowRect(*this, &rcWnd);
            rcWnd.Offset(-rcWnd.left, -rcWnd.top);
            rcWnd.right++; 
			rcWnd.bottom++;
            HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
            ::SetWindowRgn(*this, hRgn, TRUE);
            ::DeleteObject(hRgn);
        }

        bHandled = FALSE;
        return 0;
	}

	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		MONITORINFO oMonitor = {};
		oMonitor.cbSize = sizeof(oMonitor);
		::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
		CRect rcWork = oMonitor.rcWork;
		rcWork.Offset(-rcWork.left, -rcWork.top);

		LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
		lpMMI->ptMaxPosition.x	= rcWork.left;
		lpMMI->ptMaxPosition.y	= rcWork.top;
		lpMMI->ptMaxSize.x		= rcWork.right;
		lpMMI->ptMaxSize.y		= rcWork.bottom;

		bHandled = FALSE;
		return 0;
	}

	/*LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if( ::IsZoomed(*this) != bZoomed ) {
			if( !bZoomed ) {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("btn_max")));
				if( pControl ) pControl->SetVisible(false);
				pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("btn_restore")));
				if( pControl ) pControl->SetVisible(true);
			}
			else {
				CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("btn_max")));
				if( pControl ) pControl->SetVisible(true);
				pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("btn_restore")));
				if( pControl ) pControl->SetVisible(false);
			}
		}
		return lRes;
	}*/

	LRESULT HandleMessage(UINT uMsg,WPARAM wParam,LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		switch(uMsg)
		{
		case WM_CREATE:
			lRes = OnCreate(uMsg, wParam, lParam, bHandled);
			break;
		case WM_CLOSE:
			lRes = OnClose(uMsg, wParam, lParam, bHandled);
			break;
		case WM_DESTROY:
			lRes = OnDestroy(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_NCACTIVATE:    
			lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_NCCALCSIZE:    
			lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_NCPAINT:       
			lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_NCHITTEST:     
			lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_SIZE:          
			lRes = OnSize(uMsg, wParam, lParam, bHandled); 
			break;
		case WM_GETMINMAXINFO: 
			lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); 
			break;
		/*case WM_SYSCOMMAND:    
			lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); 
			break;*/
		case WM_ADDLISTITEM:
			lRes = OnAddListItem(uMsg, wParam, lParam, bHandled);
			break;
		default:
			bHandled = FALSE;
		}
		if( bHandled ) return lRes;
		if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}
	//获取该月的天数
	UINT GetMonthOfDays(UINT year,UINT month)
	{
		UINT mDay[12] = {31,28,31,30,31,30,31,31,30,31,30,31};//12个月的天数(平年的情况)
		//闰年时，二月加一天
		if (year % 400 ==0 || (year % 4 == 0 && year % 100 != 0))
		{
			mDay[1] = 29;
		}
		return mDay[month-1];
	}

	UINT GetWeek(UINT year,UINT month,UINT day)
	{
		UINT week;
		UINT sum_day = day;
	
		for (UINT i=1; i<month; i++)
		{
			sum_day += GetMonthOfDays(year,i);
		}

		week = (year-1 + (year-1)/4 - (year-1)/100  + (year-1)/400  + sum_day)%7; 
		return week;		
	}
	
	void SetBeginDateInList(UINT year,UINT month)
	{
		CListUI *pList = static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
		if (pList == NULL)
		{
			return;
		}

		pList->RemoveAll();

		//初始化数组
		for (UINT i=0; i<6; i++)
		{
			for (UINT j=0; j<7; j++)
			{
				Array[i][j] = 0;
			}
		}
		pList->SetTextCallback(this);
		InsertList(pList, year,month);
	}

	void SetEndDateInList(UINT year, UINT month)
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
				Array[i][j] = 0;
			}
		}
		pList->SetTextCallback(this);
		InsertList(pList, year, month);
	}

	void InsertList(CListUI *pList, UINT year,UINT month)
	{
		UINT FirstDay;//该月份的第一天星期几
		UINT MonthOfDays;//该月的天数
		MonthOfDays = GetMonthOfDays(year,month);
		FirstDay = GetWeek(year,month,1);
		UINT k=1;

		for (UINT i=0; i<6; i++)
		{
			if (0 == i)
			{
				for (UINT j=FirstDay; j<7; j++)
				{
					Array[i][j] = k;
					k++;
				}
			}
			else
			{
				for (UINT j=0; j<7; j++)
				{
					if(k>MonthOfDays) break;
					Array[i][j] = k;
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
					pList->Add(pListElement);
			}
		}

	}

	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem)
	{
		TCHAR szBuf[MAX_PATH] = {0};
		CStdString sText;
		sText.SmallFormat(_T("%d"),Array[iIndex][iSubItem]);
		if (sText == "0")
		{
			sText = "";
		}
		_stprintf(szBuf,/*Array[iIndex][iSubItem]*/sText);
		pControl->SetUserData(szBuf);
		return pControl->GetUserData();
	}
	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CListTextElementUI* pListElement = (CListTextElementUI*)lParam;
		//CListContainerElementUI* pListElement = (CListContainerElementUI*)lParam;
		CListUI*pListBegin=static_cast<CListUI*>(m_pm.FindControl("BeginDateList"));
		if(pListBegin)
			pListBegin->Add(pListElement);

// 		CListUI*pListEnd = static_cast<CListUI*>(m_pm.FindControl("EndDateList"));
// 		if (pListEnd)
// 			pListEnd->Add(pListElement);
		return 0;
	}


public:
	UINT m_CurYear;
	UINT m_CurMonth;
	CPaintManagerUI m_pm;
	SYSTEMTIME m_sysTime;
private:
	CButtonUI* m_pCloseBtn;
	/*CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;*/
	CLabelUI * m_pBeginCurentDate;
	CLabelUI * m_pEndCurentDate;
};

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE,LPSTR,int nComdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;

	CFameWindowWnd *pFrame = new CFameWindowWnd();
    if( pFrame == NULL ) return 0;
    pFrame->Create(NULL, _T("MonthCal"), UI_WNDSTYLE_DIALOG, 0L);

	LONG styleValue = ::GetWindowLong(pFrame->GetHWND(), GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(pFrame->GetHWND(), GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	pFrame->CenterWindow();
    pFrame->ShowWindow(true);
    CPaintManagerUI::MessageLoop();

	::CoUninitialize();

    return 0;

}