#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

using namespace DuiLib;

class OpenCalendarWnd : public WindowImplBase
{
public:
	OpenCalendarWnd();
	~OpenCalendarWnd();

	void InitWindow();

	CDuiString GetSkinFile() {
		return _T("OpenCalendar.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIOpenCalendar"); };

	void Notify(TNotifyUI& msg);
	void ShowHxCalendar();
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

