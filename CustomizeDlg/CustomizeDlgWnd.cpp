#include"CustomizeDlgWnd.h"


CustomizeDlgWnd::CustomizeDlgWnd()
{

}

CustomizeDlgWnd::~CustomizeDlgWnd()
{

}


void CustomizeDlgWnd::InitWindow()
{

}


void CustomizeDlgWnd::Notify(TNotifyUI& msg)
{
	CDuiString name = msg.pSender->GetName();

	if (msg.sType == _T("click"))
	{
		if (_tcsicmp(name, _T("btn_close")) == 0)
		{
			Close(IDCANCEL);
			return;
		}
	}
}