#pragma once

#include "..\DuiLib\UIlib.h"
#include "..\DuiLib\Core\UIBase.h"

#include "pugixml/pugixml.hpp"

using namespace pugi;
using namespace std;
using namespace DuiLib;

struct ListItem
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

		return CListUI::Add(pControl);
	}

	bool AddAt(CControlUI* pControl, int iIndex)
	{
		if (!pControl)
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

	void AddItem(vector<CDuiString> itemdata)
	{
		int nCount = GetHeader()->GetCount();
		CListTextElementUI* pItem = new CListTextElementUI;

		CListContainerElementUI* pItemUI = new CListContainerElementUI;
		pItemUI->ApplyAttributeList(m_pm->GetStyle("element_style"));
		Add(pItemUI);
		nCount = nCount > itemdata.size() ? itemdata.size() : nCount;

		// 增加 不同的风格 align color etc.
		for (int i = 0; i < nCount; i++)
		{
			CLabelUI* pLabel = new CLabelUI;
			if (i == 0)
			{
				pLabel->ApplyAttributeList(m_pm->GetStyle("label_style"));
				pLabel->ApplyAttributeList(m_pm->GetStyle("label_style_grey"));
			}				
			else
			{
				pLabel->ApplyAttributeList(m_pm->GetStyle("label_style_right"));
			}

			if (i == 1)
				pLabel->ApplyAttributeList(m_pm->GetStyle("label_style_red"));
			if (i == 2)
				pLabel->ApplyAttributeList(m_pm->GetStyle("label_style_green"));
			
			if (pLabel)
			{
				pLabel->SetText(itemdata[i]);
			}
			pItemUI->Add(pLabel);
		}
	}

private:
	CPaintManagerUI * m_pm;

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
		ReadTableHeader();
	}

	CDuiString GetSkinFile() {
		return _T("hxTable.xml");
	}
	LPCTSTR GetWindowClassName() const { return _T("UIHxList"); };

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
			CHxTableList* pList = static_cast<CHxTableList*>(m_pm.FindControl(_T("hxlist")));
			if (pList)
			{
				//点按钮往列表插入数据

				vector<CDuiString> vcItem;

				ListItem itemdata1;
				itemdata1.strCode = _T("600000");
				itemdata1.strName = _T("浦发银行");
				itemdata1.strTime = _T("暂无涨停");
				vcItem.push_back(itemdata1.strCode);
				vcItem.push_back(itemdata1.strName);
				vcItem.push_back(itemdata1.strTime);
				pList->AddItem(vcItem);

				vcItem.clear();
				ListItem itemdata2;
				itemdata2.strCode = _T("300033");
				itemdata2.strName = _T("同花顺");
				itemdata2.strTime = _T("2020-05-01");
				vcItem.push_back(itemdata2.strCode);
				vcItem.push_back(itemdata2.strName);
				vcItem.push_back(itemdata2.strTime);
				pList->AddItem(vcItem);

				vcItem.clear();
				ListItem itemdata3;
				itemdata3.strCode = _T("300750");
				itemdata3.strName = _T("宁德时代");
				itemdata3.strTime = _T("2020-04-05");
				vcItem.push_back(itemdata3.strCode);
				vcItem.push_back(itemdata3.strName);
				vcItem.push_back(itemdata3.strTime);
				pList->AddItem(vcItem);
			}
			return;
		}

		WindowImplBase::Notify(msg);
	}

	// to do!!  read table header from xml file 
	void ReadTableHeader()
	{

	}
};