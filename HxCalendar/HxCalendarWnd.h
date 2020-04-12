#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

#define  WM_ADDLISTITEM  WM_USER+1001

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

protected:
	UINT GetMonthOfDays(UINT year, UINT month);

	UINT GetWeek(UINT year, UINT month, UINT day);

	void SetBeginDateInList(UINT year, UINT month);
	void SetEndDateInList(UINT year, UINT month);
	void InsertList(CListUI *pList, UINT year, UINT month);
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
	LRESULT OnAddListItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	UINT m_Array[6][7];
	UINT m_CurYear;
	UINT m_CurMonth;
	CPaintManagerUI m_pm;
	SYSTEMTIME m_sysTime;

	CButtonUI * m_pCloseBtn;
	CLabelUI * m_pBeginCurentDate;
	CLabelUI * m_pEndCurentDate;
};

