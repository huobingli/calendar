#include "SuperWindowWnd.h"


CBackGroundWnd::CBackGroundWnd()
{

}

CBackGroundWnd::~CBackGroundWnd()
{

}

void CBackGroundWnd::InitWindow()
{

}

void CBackGroundWnd::Notify(TNotifyUI& msg)
{

}

LRESULT CBackGroundWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

CControlUI* CBackGroundWnd::CreateControl(LPCTSTR pstrClass)
{

}


CSuperWindowWnd::CSuperWindowWnd()
{

}

CSuperWindowWnd::~CSuperWindowWnd()
{

}

void CSuperWindowWnd::InitWindow()
{

}

void CSuperWindowWnd::Notify(TNotifyUI& msg)
{

}

LRESULT CSuperWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

CControlUI* CSuperWindowWnd::CreateControl(LPCTSTR pstrClass)
{

}