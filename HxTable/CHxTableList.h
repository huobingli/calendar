#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

//#include "jsoncpp/json.h"

#include <vector>

using namespace std;
using namespace DuiLib;

struct MyItem2
{
	CDuiString strCode;
	CDuiString strName;
	CDuiString strTime;
};

class CHxTableList : public CListUI
{
public:
	enum { SCROLL_TIMERID = 10 };
	CHxTableList(CPaintManagerUI* pm)
	{
		m_pm = pm;
	}
	~CHxTableList()
	{

	}

	bool Add(CControlUI* pControl)
	{
		if (!pControl)
			return false;

		//if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
//			return false;

		return CListUI::Add(pControl);
	}

	bool AddAt(CControlUI* pControl, int iIndex)
	{
		if (!pControl)
			return false;

		if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
			return false;

		return CListUI::AddAt(pControl, iIndex);
	}

	bool Remove(CControlUI* pControl)
	{
		if (!pControl)
			return false;

		if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
			return false;

		return CListUI::Remove(pControl);
	}

	bool RemoveAt(int iIndex)
	{
		CControlUI* pControl = GetItemAt(iIndex);
		if (!pControl)
			return false;

		if (_tcsicmp(pControl->GetClass(), DUI_CTR_LISTCONTAINERELEMENT) != 0)
			return false;

		return CListUI::RemoveAt(iIndex);
	}

	void RemoveAll()
	{
		CListUI::RemoveAll();
	}

	void AddItem(MyItem2& itemdata)
	{
		CListContainerElementUI* pItem = NULL;
		if (!m_dlgBuilder.GetMarkup()->IsValid())
		{
			pItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(_T("hxTableitem.xml"), (UINT)0, NULL, m_pm));
		}
		else {
			pItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create((UINT)0, m_pm));
		}
		if (!pItem) return;
		this->Add(pItem);
		//设置头像
		CButtonUI *pBtn = static_cast<CButtonUI*>(pItem->FindSubControl(_T("logo")));
		if (pBtn)
		{
			//pBtn->SetNormalImage(itemdata.str);
			pBtn->SetText(itemdata.strCode);
		}
		//设置昵称
		CLabelUI * pNickName = static_cast<CLabelUI*>(pItem->FindSubControl(_T("nickname")));
		if (pNickName)
		{
			pNickName->SetText(itemdata.strName);
		}
		//设置描述
		CLabelUI * pDes = static_cast<CLabelUI*>(pItem->FindSubControl(_T("description")));
		if (pDes)
		{
			pDes->SetText(itemdata.strTime);
		}
	}

private:
	CPaintManagerUI* m_pm;

	CDialogBuilder m_dlgBuilder;
};

class CHxTableListWnd : public WindowImplBase
{
public:
	CHxTableListWnd()
	{

	}
	~CHxTableListWnd()
	{

	}

	void InitWindow()
	{

	}

	CDuiString GetSkinFile() {
		return _T("hxTable.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIHxCalendar"); };

	virtual CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		if (_tcsicmp(pstrClass, _T("hxList")) == 0)
		{
			return new CHxTableList(&m_pm);
		}
		else
			return NULL;
	}

	virtual void Notify(TNotifyUI& msg)
	{
		if (msg.sType == DUI_MSGTYPE_CLICK && msg.pSender->GetName() == _T("btnstart"))
		{
			//点按钮往列表插入数据
			CHxTableList* pMyList2 = static_cast<CHxTableList*>(m_pm.FindControl(_T("list1")));
			if (pMyList2)
			{
				MyItem2 itemdata1;
				itemdata1.strCode = _T("600000");
				itemdata1.strName = _T("浦发银行");
				itemdata1.strTime = _T("暂无涨停");
				pMyList2->AddItem(itemdata1);

				MyItem2 itemdata2;
				itemdata2.strCode = _T("300033");
				itemdata2.strName = _T("同花顺");
				itemdata2.strTime = _T("2020-05-01");
				pMyList2->AddItem(itemdata2);

				MyItem2 itemdata3;
				itemdata3.strCode = _T("300750");
				itemdata3.strName = _T("宁德时代");
				itemdata3.strTime = _T("2020-04-05");
				pMyList2->AddItem(itemdata3);
			}
			return;
		}
	}	
	
};

