
// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "SalesSystem.h"

#include "MainFrm.h"
#include "InfoFile.h"
#include "SelectView.h"
#include "DisplayView.h"
#include "UesrDlg.h"
#include "SellDlg.h"
#include "InfoDlg.h"
#include "AddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	// ON_MESSAGE响应的是自定义消息
	// 产生NM_X消息，自动调用onMyChange函数
	ON_MESSAGE(NM_A, OnMyChange)
	ON_MESSAGE(NM_B, OnMyChange)
	ON_MESSAGE(NM_C, OnMyChange)
	ON_MESSAGE(NM_D, OnMyChange)
	ON_MESSAGE(NM_E, OnMyChange)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));

	// 设置图标
	SetClassLong(m_hWnd, GCL_HICON, (LONG)AfxGetApp()->LoadIconW(IDI_ICON_WIN));

	SetTitle(TEXT("Sales System"));

	MoveWindow(0, 0, 800, 500);

	CenterWindow();

	// 测试 CInfoFile
	//CInfoFile file;
	//CString name;
	//CString pwd;
	//file.ReadLogin(name,pwd);
	//MessageBox(TEXT("用户名：") + name + TEXT("；密码：") + pwd);
	//file.WritePwd("李欣", "123");
	//MessageBox(TEXT("用户名：") + name + TEXT("；密码：") + pwd);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	// 拆分成一行两列
	m_spliter.CreateStatic(this, 1, 2);

	// 左侧右侧显示内容
	m_spliter.CreateView(0, 0, RUNTIME_CLASS(CSelectView), CSize(200, 500), pContext);
	m_spliter.CreateView(0, 1, RUNTIME_CLASS(CDisplayView), CSize(600, 500), pContext);

	//return CFrameWnd::OnCreateClient(lpcs, pContext);
	return TRUE;
}

LRESULT CMainFrame::OnMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext context;

	switch (wParam)
	{
	case NM_A:
	{
		//MessageBox(TEXT("个人信息界面挂载"));
		// 挂载界面
		context.m_pNewViewClass = RUNTIME_CLASS(CUserDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CUserDlg), CSize(600, 500), &context);
		CUserDlg *pNewView = (CUserDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_B:
	{
		//MessageBox(TEXT("销售管理界面挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CSellDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CSellDlg), CSize(600, 500), &context);
		CSellDlg *pNewView = (CSellDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_C:
	{
		//MessageBox(TEXT("库存信息界面挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CInfoDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CInfoDlg), CSize(600, 500), &context);
		CInfoDlg *pNewView = (CInfoDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_D:
	{
		//MessageBox(TEXT("库存添加界面挂载"));
		context.m_pNewViewClass = RUNTIME_CLASS(CAddDlg);
		context.m_pCurrentFrame = this;
		context.m_pLastView = (CFormView*)m_spliter.GetPane(0, 1);
		m_spliter.DeleteView(0, 1);
		m_spliter.CreateView(0, 1, RUNTIME_CLASS(CAddDlg), CSize(600, 500), &context);
		CAddDlg *pNewView = (CAddDlg *)m_spliter.GetPane(0, 1);
		m_spliter.RecalcLayout();
		pNewView->OnInitialUpdate();
		m_spliter.SetActivePane(0, 1);
		break;
	}
	case NM_E:
	{
		//MessageBox(TEXT("库存删除界面挂载"));
		break;
	}
	default:
		break;
	}
	return 0;
}
