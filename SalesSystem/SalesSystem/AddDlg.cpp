// AddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SalesSystem.h"
#include "AddDlg.h"
#include "InfoFile.h"


// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(IDD_DIALOG_ADD)
	, m_price(0)
	, m_num(0)
	, m_newName(_T(""))
	, m_newPrice(0)
	, m_newNum(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT7, m_newName);
	DDX_Text(pDX, IDC_EDIT5, m_newPrice);
	DDX_Text(pDX, IDC_EDIT6, m_newNum);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 初始化下拉框
	CInfoFile file;
	// 把商品读到file对象中
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}

	m_combo.SetCurSel(0);
	// 更新第一个商品里的数据
	 OnCbnSelchangeCombo1();
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 切换商品触发的事件

	// 获取商品名称
	int index = m_combo.GetCurSel();

	CString name;
	m_combo.GetLBText(index, name);

	// 根据商品的名称获取价格和库存 并且显示到控件中

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			m_price = it->price;
			UpdateData(FALSE);
		}
	}
}


void CAddDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	// 添加商品的功能实现
	if (m_num <= 0) {
		MessageBox(TEXT("添加数量要大于0"));
		return;
	}

	// 购买
	// 获取具体要添加的商品名称
	int index = m_combo.GetCurSel();

	CString name;
	m_combo.GetLBText(index, name);

	// 根据商品的名称获取价格和库存 并且显示到控件中

	CInfoFile file;
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		if (CString(it->name.c_str()) == name)
		{
			// 添加库存
			it->num += m_num;
			m_num = 0;

			UpdateData(FALSE);
			MessageBox(TEXT("添加成功"));
		}
	}

	file.WriteDocline();
}


void CAddDlg::OnBnClickedButton4()
{
	// 清空数据
	m_num = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	// 更新第一个商品里的数据
	OnCbnSelchangeCombo1();
}
