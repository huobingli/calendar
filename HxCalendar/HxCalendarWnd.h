#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

using namespace DuiLib;
class HxCalendarWnd : public WindowImplBase
{
public:
	HxCalendarWnd();
	~HxCalendarWnd();

	void InitWindow();

	CDuiString GetSkinFile() {
		return _T("hxCalendar.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIHxCalendar"); };

	void Notify(TNotifyUI& msg);

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

