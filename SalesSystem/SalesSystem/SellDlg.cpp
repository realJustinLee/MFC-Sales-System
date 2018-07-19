// SellDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SalesSystem.h"
#include "SellDlg.h"
#include "InfoFile.h"

// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(IDD_DIALOG_SELL)
	, m_price(0)
	, m_storage(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_storage);
	DDX_Text(pDX, IDC_EDIT2, m_num);
	DDX_Text(pDX, IDC_EDIT4, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
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


void CSellDlg::OnCbnSelchangeCombo1()
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


void CSellDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// 购买的功能实现
	if (m_num <= 0) {
		MessageBox(TEXT("购买数量要大于0"));
		return;
	}

	if (m_num > m_storage) {
		MessageBox(TEXT("购买数量不能大于库存量"));
		return;
	}

	// 购买
	// 获取具体要购买的商品名称
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

			// 告诉用户集体购买信息
			CString str;
			str.Format(_T("商品：%s \r\n单价：%d \r\n个数：%d \r\n总价：%d"), name, m_price, m_num, m_price*m_num);
			m_sellInfo = str;
			UpdateData(FALSE);
			MessageBox(TEXT("购买成功"));
		}
	}

	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
	file.WriteDocline();
}


void CSellDlg::OnBnClickedButton2()
{
	// 清空数据
	m_num = 0;
	m_sellInfo.Empty();
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	// 更新第一个商品里的数据
	OnCbnSelchangeCombo1();
}
