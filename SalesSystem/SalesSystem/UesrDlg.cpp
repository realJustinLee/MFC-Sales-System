// UesrDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SalesSystem.h"
#include "UesrDlg.h"
#include "InfoFile.h"

// CUesrDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(IDD_DIALOG_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_cfmPwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_cfmPwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUesrDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUesrDlg 消息处理程序


void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	// 初始化
	m_user = TEXT("销售员");

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	m_name = name;

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton1()
{
	// 修改密码功能

	UpdateData(TRUE);

	if (m_newPwd.IsEmpty() || m_cfmPwd.IsEmpty()) {
		MessageBox(TEXT("新密码不能为空"));
		return;
	}

	if (m_newPwd != m_cfmPwd) {
		MessageBox(TEXT("新密码与确认密码不一致"));
		return;
	}

	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	if (m_newPwd == pwd) {
		MessageBox(TEXT("新密码与旧密码不能一致"));
		return;
	}

	// CString 转 char*
	CStringA tmpName, tmpPwd;
	tmpName = name;
	tmpPwd = m_newPwd;

	file.WritePwd(tmpName.GetBuffer(),tmpPwd.GetBuffer());

	MessageBox(TEXT("修改成功"));

	m_newPwd.Empty();
	m_cfmPwd.Empty();

	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// 取消按钮
	m_newPwd.Empty();
	m_cfmPwd.Empty();

	UpdateData(FALSE);
}
