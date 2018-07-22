// DelDlg.cpp : ʵ���ļ�
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


// CDelDlg ���

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


// CDelDlg ��Ϣ��������


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ�����ר�ô����/����û���
	// ��ʼ����Ϣ��������

	// ��ʼ��������
	CInfoFile file;
	// ����Ʒ����file������
	file.ReadDocline();
	for (list<msg>::iterator it = file.ls.begin(); it != file.ls.end(); it++)
	{
		m_combo.AddString(CString(it->name.c_str()));
	}

	m_combo.SetCurSel(0);
	// ���µ�һ����Ʒ�������
	OnCbnSelchangeCombo1();
}


void CDelDlg::OnCbnSelchangeCombo1()
{
	// �л���Ʒ�������¼�

	// ��ȡ��Ʒ����
	int index = m_combo.GetCurSel();

	CString name;
	m_combo.GetLBText(index, name);

	// ������Ʒ�����ƻ�ȡ�۸�Ϳ�� ������ʾ���ؼ���

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
		MessageBox(TEXT("ɾ������Ҫ����0"));
		return;
	}

	if (m_num > m_storage) {
		MessageBox(TEXT("ɾ���������ܴ��ڿ����"));
		return;
	}

	int index = m_combo.GetCurSel();

	CString name;
	m_combo.GetLBText(index, name);

	// ������Ʒ�����ƻ�ȡ�۸�Ϳ�� ������ʾ���ؼ���

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
			str.Format(_T("ɾ����Ʒ��%s \r\n���ۣ�%d \r\n������%d"), name, m_price, m_num);
			MessageBox(str);
		}
	}

	m_num = 0;
	UpdateData(FALSE);
	file.WriteDocline();
}


void CDelDlg::OnBnClickedButton2()
{
	// �������
	m_num = 0;
	UpdateData(FALSE);
	m_combo.SetCurSel(0);
	// ���µ�һ����Ʒ�������
	OnCbnSelchangeCombo1();
}