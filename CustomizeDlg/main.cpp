#include <windows.h>
#include <objbase.h>
#include <ATLComTime.h>

#include "CustomizeDlgWnd.h"

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"
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

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	CustomizeDlgWnd* pFrame = new CustomizeDlgWnd;
	pFrame->CreateDuiWindow(NULL, _T("²âÊÔÍøÒ³"), UI_WNDSTYLE_DIALOG, 0L);
	pFrame->CenterWindow();

	CPaintManagerUI::MessageLoop();
	::CoUninitialize();
	return 0;
}
