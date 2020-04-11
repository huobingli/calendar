#include <windows.h>
#include <objbase.h>
#include <ATLComTime.h>
#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"
//#include "../ListDemo/bin/Duilib_u.lib"
using namespace DuiLib;

#ifdef _DEBUG
#ifdef _UNICODE
#pragma comment(lib,"..//bin//DuiLib_ud.lib")
#else
//#pragma comment(lib,"..//bin//DuiLib_d.lib")
#pragma comment(lib,"..//ListDemo//bin//DuiLib_d.lib")
#endif
#else
#ifdef _UNICODE
#pragma comment(lib,"..//bin//DuiLib_u.lib")
#else
#pragma comment(lib,"..//bin//DuiLib.lib")
#endif
#endif


class CFrameWindowWnd : public WindowImplBase
{
public:
	CFrameWindowWnd() { };

	void InitWindow() {  };

	CDuiString GetSkinFile() {
		return _T("Calendar1.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
	//UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	UINT GetClassStyle() const { return CS_DBLCLKS; };
	void OnFinalMessage(HWND /*hWnd*/) { delete this; };

	void Init() {}

	void OnPrepare()
	{
		::GetLocalTime(&m_sysTime);
		DrawCalendar(m_sysTime);
	}

	void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("windowinit")) OnPrepare();
		else if (msg.sType == _T("return"))
		{
			m_sysTime.wYear = SetTxtYear(0);
			m_sysTime.wMonth = GetCmbMonth();
			DrawCalendar(m_sysTime);
		}
		else if (msg.sType == _T("click"))
		{
			CControlUI* pOne = static_cast<CControlUI*>(m_pm.FindControl(msg.ptMouse));
			if (_tcsicmp(pOne->GetClass(), _T("ButtonUI")) == 0)
			{
				//��һ��
				if (_tcsicmp(pOne->GetName(), _T("BTN_UP_MONTH")) == 0)
				{
					m_sysTime.wMonth = m_sysTime.wMonth - 1 == 0 ? 12 : m_sysTime.wMonth - 1;
					DrawCalendar(m_sysTime);
				}
				//��һ��
				else if (_tcsicmp(pOne->GetName(), _T("BTN_UP_YEAR")) == 0)
				{
					m_sysTime.wYear = SetTxtYear(-1);
					m_sysTime.wMonth = GetCmbMonth();
					DrawCalendar(m_sysTime);
				}
				//��һ��
				else if (_tcsicmp(pOne->GetName(), _T("BTN_DOWN_YEAR")) == 0)
				{
					m_sysTime.wYear = SetTxtYear(1);
					m_sysTime.wMonth = GetCmbMonth();
					DrawCalendar(m_sysTime);
				}
			}
		}
		else if (msg.sType == _T("itemselect")) {
			if (_tcsicmp(msg.pSender->GetName(), _T("CMB_MONTH")) == 0)
			{
				m_sysTime.wMonth = GetCmbMonth();
				DrawCalendar(m_sysTime);
			}
		}
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE) {
			m_pm.Init(m_hWnd);
			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("Calendar1.xml"), (UINT)0, NULL, &m_pm);
			ASSERT(pRoot && "Failed to parse XML");
			m_pm.AttachDialog(pRoot);
			m_pm.AddNotifier(this);
			Init();
			return 0;
		}
		else if (uMsg == WM_DESTROY) {
			::PostQuitMessage(0L);
		}
		else if (uMsg == WM_ERASEBKGND) {
			return 1;
		}
		LRESULT lRes = 0;
		if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

	//��������
	void DrawCalendar(SYSTEMTIME m_sysTime)
	{
		int iDay = 0;
		char cDay[3] = { 0 };
		//int iStartDay = m_sysTime.wDayOfWeek;
		m_sysTime.wDay = 1;
		int iStartDay = GetDayOfWeek(m_sysTime);
		//��������
		int iLastMonthStartDays = 31 - iStartDay;
		if (m_sysTime.wMonth > 1)
			iLastMonthStartDays = GetMonthDays(m_sysTime.wYear, m_sysTime.wMonth - 1) - iStartDay;
		//��������
		int iMonthDays = GetMonthDays(m_sysTime.wYear, m_sysTime.wMonth);
		//��������
		int iNextMonthDays = 0;

		CControlUI* pButtonUI;
		CContainerUI* pControl = static_cast<CContainerUI*>(m_pm.FindControl(_T("ContainerUI3")));
		for (int i = 0; i < 42; i++)
		{
			pButtonUI = m_pm.FindSubControlByClass(pControl, _T("ButtonUI"), i);
			//����
			if (i < iStartDay)
			{
				iLastMonthStartDays++;
				sprintf(cDay, "%d", iLastMonthStartDays);
				pButtonUI->SetText(cDay);
				DrawBtnBackImage(pButtonUI, false);
			}
			else if (i > iStartDay - 1 && iDay < iMonthDays)
			{
				iDay++;
				sprintf(cDay, "%d", iDay);
				pButtonUI->SetText(cDay);
				DrawBtnBackImage(pButtonUI, true);
			}
			else
			{
				iNextMonthDays++;
				sprintf(cDay, "%d", iNextMonthDays);
				pButtonUI->SetText(cDay);
				DrawBtnBackImage(pButtonUI, false);
			}
		}

		CControlUI* pButtonUI1;
		CContainerUI* pControl1 = static_cast<CContainerUI*>(m_pm.FindControl(_T("ContainerUI13")));

		if (pControl1)
		{
			for (int i = 0; i < 42; i++)
			{
				pButtonUI1 = m_pm.FindSubControlByClass(pControl1, _T("ButtonUI1"), i);

				if (pButtonUI1 == NULL)
					continue;
				//����
				if (i < iStartDay)
				{
					iLastMonthStartDays++;
					sprintf(cDay, "%d", iLastMonthStartDays);
					pButtonUI1->SetText(cDay);
					DrawBtnBackImage(pButtonUI1, false);
				}
				else if (i > iStartDay - 1 && iDay < iMonthDays)
				{
					iDay++;
					sprintf(cDay, "%d", iDay);
					pButtonUI1->SetText(cDay);
					DrawBtnBackImage(pButtonUI1, true);
				}
				else
				{
					iNextMonthDays++;
					sprintf(cDay, "%d", iNextMonthDays);
					pButtonUI1->SetText(cDay);
					DrawBtnBackImage(pButtonUI1, false);
				}
			}
		}		
	}

	void DrawBtnBackImage(CControlUI* pButtonUI, bool isEnable)
	{
		if (isEnable)
		{
			pButtonUI->SetEnabled(true);
			pButtonUI->ApplyAttributeList(
				_T("normalimage=\"file='cells.png' source='0,0,81,81'\" ")\
				_T("hotimage=\"file='cells.png' source='0,81,81,162'\" "));
		}
		else
		{
			pButtonUI->SetBkImage(_T("calpad.jpg"));
			pButtonUI->ApplyAttributeList(
				_T("normalimage=\"file='calpad.jpg'\" ")\
				_T("hotimage=\"file='calpad.jpg'\" "));
		}
	}

	int GetMonthDays(int iY, int iM)
	{
		int iTotalDay = 31;
		if (iM == 2)
		{
			//������Ա�4����400���� ���ǲ��ܱ�100����
			if (iY % 4 == 0 && iY % 100 != 0 || iY % 400 == 0)
				iTotalDay = 29;
			else
				iTotalDay = 28;
		}
		else if (iM == 4 || iM == 6 || iM == 9 || iM == 11)
			iTotalDay = 30;
		return iTotalDay;
	}

	int GetDayOfWeek(SYSTEMTIME m_sysTime)
	{
		cTime.SetDate(m_sysTime.wYear, m_sysTime.wMonth, m_sysTime.wDay);
		return cTime.GetDayOfWeek() - 1;
	}

	int GetCmbMonth()
	{
		CComboUI* pCmb = static_cast<CComboUI*>(m_pm.FindControl(_T("CMB_MONTH")));
		CDuiString cCurMonth = pCmb->GetText();
		return atoi(cCurMonth.Left(cCurMonth.GetLength() - 1));
	}

	int SetTxtYear(int iY)
	{
		CEditUI* pTxt = static_cast<CEditUI*>(m_pm.FindControl(_T("TXT_YEAR")));
		CDuiString cCurYear = pTxt->GetText();
		int iCurYear = 0;
		iCurYear = atoi(cCurYear) + iY;
		cCurYear.Format("%d", iCurYear);
		pTxt->SetText(cCurYear);
		return iCurYear;
	}


public:
	CPaintManagerUI m_pm;
	SYSTEMTIME m_sysTime;
	COleDateTime cTime;
};


class CFrameWindow : public WindowImplBase
{
public:
	CFrameWindow() { };
	LPCTSTR GetWindowClassName() const { return _T("UIFrameWindow"); };
	void OnFinalMessage(HWND /*hWnd*/) { delete this; };

	void InitWindow() {  };

	CDuiString GetSkinFile() {
		return _T("test.xml");
	}
	void Notify(TNotifyUI& msg)
	{
		CDuiString name = msg.pSender->GetName();
		if (msg.sType == _T("click"))
		{
			//if (name.CompareNoCase(_T()))

			if (name.CompareNoCase(_T("closebtn")) == 0)
			{
				Close(IDCANCEL);
				return;
			}

			else if (name.CompareNoCase(_T("calendar")) == 0)
			{
				ShowCalendar();
			}
		}

	}

	void ShowCalendar()
	{
		CFrameWindowWnd* pFrame = new CFrameWindowWnd;

		pFrame->CreateDuiWindow(NULL, _T("��������"), UI_WNDSTYLE_DIALOG, 0L);
		pFrame->CenterWindow();
	}

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
};

int ShowCalendar(HINSTANCE hInstance)
{
  	CPaintManagerUI::SetInstance(hInstance);
   	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//  
//  	HRESULT Hr = ::CoInitialize(NULL);
//  	if (FAILED(Hr)) return 0;
//  
//  	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
//  	if (pFrame == NULL) return 0;
//  	//   pFrame->Create(NULL, _T("�����ؼ�����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
//  	pFrame->Create(NULL, _T("�����ؼ�����"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);   //��ֹ˫���Ŵ�
//  	pFrame->CenterWindow();
//  	pFrame->ShowWindow(true);
//  	CPaintManagerUI::MessageLoop();
//  
//  	::CoUninitialize();

// 	CFrameWindowWnd* pFrame = new CFrameWindowWnd;
// 
// 	pFrame->CreateDuiWindow(NULL, _T("test.xml"), UI_WNDSTYLE_DIALOG, 0L);
// 	pFrame->CenterWindow();

	CFrameWindow* pFrame = new CFrameWindow();
	pFrame->CreateDuiWindow(NULL, _T("test.xml"), UI_WNDSTYLE_DIALOG, 0L);
	pFrame->CenterWindow();

	CPaintManagerUI::MessageLoop();
	return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
// 	CPaintManagerUI::SetInstance(hInstance);
// 	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
// 
// 	HRESULT Hr = ::CoInitialize(NULL);
// 	if (FAILED(Hr)) return 0;
// 
// 	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
// 	if (pFrame == NULL) return 0;
// 	//   pFrame->Create(NULL, _T("�����ؼ�����"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
// 	pFrame->Create(NULL, _T("�����ؼ�����"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 600, 320);   //��ֹ˫���Ŵ�
// 	pFrame->CenterWindow();
// 	pFrame->ShowWindow(true);
// 	CPaintManagerUI::MessageLoop();
// 
// 	::CoUninitialize();

	//CPaintManagerUI::SetInstance(hInstance);
// 	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
// 
// 	HRESULT Hr = ::CoInitialize(NULL);
// 	if (FAILED(Hr)) return 0;
// 	CFrameWindow* pWnd = new CFrameWindow();
// 	if (pWnd == NULL) return 0;
// 
// 	pWnd->Create(NULL, _T("�����ؼ�����"), UI_WNDSTYLE_DIALOG, WS_EX_STATICEDGE | WS_EX_APPWINDOW, 0, 0, 300, 200);

	ShowCalendar(hInstance);
	return 0;
}


