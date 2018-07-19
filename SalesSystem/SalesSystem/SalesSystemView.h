
// SalesSystemView.h : CSalesSystemView 类的接口
//

#pragma once


class CSalesSystemView : public CView
{
protected: // 仅从序列化创建
	CSalesSystemView();
	DECLARE_DYNCREATE(CSalesSystemView)

// 特性
public:
	CSalesSystemDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CSalesSystemView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // SalesSystemView.cpp 中的调试版本
inline CSalesSystemDoc* CSalesSystemView::GetDocument() const
   { return reinterpret_cast<CSalesSystemDoc*>(m_pDocument); }
#endif

