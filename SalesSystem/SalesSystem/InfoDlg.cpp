// InfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SalesSystem.h"
#include "InfoDlg.h"

#include "InfoFile.h"

// CInfoDlg

IMPLEMENT_DYNCREATE(CInfoDlg, CFormView)

CInfoDlg::CInfoDlg()
	: CFormView(IDD_DIALOG_INFO)
{

}

CInfoDlg::~CInfoDlg()
{
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CInfoDlg, CFormView)
END_MESSAGE_MAP()


// CInfoDlg 诊断

#ifdef _DEBUG
void CInfoDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoDlg 消息处理程序


void CInfoDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 设置扩展风格
	// LVS_EX_FULLROWSELECT选中整行 | LVS_EX_GRIDLINES 显示网格
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 初始化表示
	CString field[] = { TEXT("商品ID") ,TEXT("商品名称"),TEXT("商品价格") ,TEXT("库存数量") };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); i++)
	{
		m_list.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	CInfoFile file;
	file.ReadDocline();

	int row = 0;
	CString str;
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		str.Format(TEXT("%d"), it->id);
		m_list.InsertItem(row, str);
		int colume = 1;
		m_list.SetItemText(row, colume++, (CString)it->name.c_str());
		str.Format(TEXT("%d"), it->price);
		m_list.SetItemText(row, colume++, str);
		str.Format(TEXT("%d"), it->num);
		m_list.SetItemText(row, colume++, str);

		row++;
	}
}
