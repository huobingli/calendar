#include <windows.h>
#include <objbase.h>
#include <ATLComTime.h>

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

	return 0;
}
