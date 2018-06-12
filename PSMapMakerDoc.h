// PSMapMakerDoc.h : interface of the CPSMapMakerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PSMAPMAKERDOC_H__A57847DA_B9F7_420F_AFDE_E84C845FD7D3__INCLUDED_)
#define AFX_PSMAPMAKERDOC_H__A57847DA_B9F7_420F_AFDE_E84C845FD7D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "PSLevel.h"

class CPSMapMakerDoc : public CDocument
{
protected: // create from serialization only
	CPSMapMakerDoc();
	DECLARE_DYNCREATE(CPSMapMakerDoc)

// Attributes
public:
	CPSLevel m_level;
 
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSMapMakerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSMapMakerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPSMapMakerDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSMAPMAKERDOC_H__A57847DA_B9F7_420F_AFDE_E84C845FD7D3__INCLUDED_)
