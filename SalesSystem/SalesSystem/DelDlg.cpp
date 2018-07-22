// DelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SalesSystem.h"
#include "DelDlg.h"
#include "InfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(IDD_DIALOG_DEL)
	, m_price(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化消息订单窗口

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


void CDelDlg::OnCbnSelchangeCombo1()
{
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
			m_storage = it->num;
			UpdateData(FALSE);
		}
	}
}


void CDelDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);

	if (m_num <= 0) {
		MessageBox(TEXT("删除数量要大于0"));
		return;
	}

	if (m_num > m_storage) {
		MessageBox(TEXT("删除数量不能大于库存量"));
		return;
	}

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
			it->num -= m_num;
			m_storage = it->num;

			UpdateData(FALSE);
			CString str;
			str.Format(_T("删除商品：%s \r\n单价：%d \r\n个数：%d"), name, m_price, m_num);
			MessageBox(str);
		}
	}

	m_num = 0;
	UpdateData(FALSE);
	file.WriteDocline();
}


void CDelDlg::OnBnClickedButton2()
{
	// 清空数据
	m_num = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	// 更新第一个商品里的数据
	OnCbnSelchangeCombo1();
}
