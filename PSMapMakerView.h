// PSMapMakerView.h : interface of the CPSMapMakerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSMAPMAKERVIEW_H__9357087F_B833_4709_8899_99ED2C5684CE__INCLUDED_)
#define AFX_PSMAPMAKERVIEW_H__9357087F_B833_4709_8899_99ED2C5684CE__INCLUDED_

#include "DXRender.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPSMapMakerView : public CView
{
protected: // create from serialization only
	CPSMapMakerView();
	DECLARE_DYNCREATE(CPSMapMakerView)

// Attributes
public:
	CPSMapMakerDoc* GetDocument();

	DXRender m_renderer;
	static CPSMapMakerView* cela;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSMapMakerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnIdle();
	virtual ~CPSMapMakerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPSMapMakerView)
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnButtonDoor();
	afx_msg void OnButtonLockedDoor();
	afx_msg void OnButtonMagicalDoor();
	afx_msg void OnButtonStairDown();
	afx_msg void OnButtonStairUp();
	afx_msg void OnButtonNextmap();
	afx_msg void OnButtonPrevmap();
	afx_msg void OnButtonExplicit();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PSMapMakerView.cpp
inline CPSMapMakerDoc* CPSMapMakerView::GetDocument()
   { return (CPSMapMakerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSMAPMAKERVIEW_H__9357087F_B833_4709_8899_99ED2C5684CE__INCLUDED_)
