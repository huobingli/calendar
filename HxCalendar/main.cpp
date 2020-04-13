#include <windows.h>
#include <objbase.h>
#include <ATLComTime.h>

#include "HxCalendarWnd.h"
#include "OpenCalendarWnd.h"

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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	OpenCalendarWnd *pFrame = new OpenCalendarWnd;

	pFrame->CreateDuiWindow(NULL, _T("日历测试"), UI_WNDSTYLE_DIALOG, 0L);
	pFrame->CenterWindow();


// 	HRESULT Hr = ::CoInitialize(NULL);
// 	if (FAILED(Hr)) return 0;
// 	HxCalendarWnd *pFrame = new HxCalendarWnd;
// 	pFrame->CreateDuiWindow(NULL, _T("日历测试"), UI_WNDSTYLE_DIALOG, 0L);
// 	pFrame->CenterWindow();

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}
