// PSMapMaker.h : main header file for the PSMAPMAKER application
//

#if !defined(AFX_PSMAPMAKER_H__2EDEFEE2_CAAE_40AB_8312_86D10446D5DF__INCLUDED_)
#define AFX_PSMAPMAKER_H__2EDEFEE2_CAAE_40AB_8312_86D10446D5DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerApp:
// See PSMapMaker.cpp for the implementation of this class
//

class CPSMapMakerApp : public CWinApp
{
public:
	CPSMapMakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSMapMakerApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPSMapMakerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PSMAPMAKER_H__2EDEFEE2_CAAE_40AB_8312_86D10446D5DF__INCLUDED_)
