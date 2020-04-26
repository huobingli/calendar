#pragma once
//////////////////////////////////////////////////////////////////////////
// 上下两层 ，下层不透明，上层全透明控件

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

using namespace DuiLib;

class CBackGroundWnd : public WindowImplBase
{
public:
	CBackGroundWnd();
	~CBackGroundWnd();


	void InitWindow();

	CDuiString GetSkinFile() {
		return _T("BackWindow.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIBackWindow"); };

	void Notify(TNotifyUI& msg);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CControlUI* CreateControl(LPCTSTR pstrClass);
};

class CSuperWindowWnd : public WindowImplBase
{
public:
	CSuperWindowWnd();
	~CSuperWindowWnd();

	void InitWindow();

	CDuiString GetSkinFile() {
		return _T("FrontWindow.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIFrontWindow"); };

	void Notify(TNotifyUI& msg);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	CControlUI* CreateControl(LPCTSTR pstrClass);
};