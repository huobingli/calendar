#include "OpenCalendarWnd.h"
#include "HxCalendarWnd.h"


OpenCalendarWnd::OpenCalendarWnd()
{
}


OpenCalendarWnd::~OpenCalendarWnd()
{
}

void OpenCalendarWnd::InitWindow()
{

}


void OpenCalendarWnd::Notify(TNotifyUI& msg)
{
	CDuiString strName = msg.pSender->GetName();

	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		if (strName.CompareNoCase(_T("closebtn")) == 0)
		{
			Close();
			return;
		}
		else if (strName.CompareNoCase(_T("calendar")) == 0)
		{
			ShowHxCalendar();
		}
	}
}

void OpenCalendarWnd::ShowHxCalendar()
{
	HxCalendarWnd *pFrame = new HxCalendarWnd;

	pFrame->CreateDuiWindow(NULL, _T("ÈÕÀú²âÊÔ"), UI_WNDSTYLE_DIALOG, 0L);
	pFrame->CenterWindow();
}

LRESULT OpenCalendarWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}