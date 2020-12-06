#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

using namespace std;
using namespace DuiLib;

class CustomizeDlgWnd : public WindowImplBase
{
public:
	CustomizeDlgWnd();
	~CustomizeDlgWnd();

	void InitWindow();

	CDuiString GetSkinFile() {
		return _T("CustomizeDlg.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UICustomizeDlg"); };

};