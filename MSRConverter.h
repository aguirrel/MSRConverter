// MSRConverter.h : main header file for the MSRConverter application
//

#if !defined(AFX_MSRConverter_H__AF90FF20_438D_491A_A9A3_5F3A449E5267__INCLUDED_)
#define AFX_MSRConverter_H__AF90FF20_438D_491A_A9A3_5F3A449E5267__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSRConverterApp:
// See MSRConverter.cpp for the implementation of this class
//

class CMSRConverterApp : public CWinApp
{
public:
	CMSRConverterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSRConverterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMSRConverterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSRConverter_H__AF90FF20_438D_491A_A9A3_5F3A449E5267__INCLUDED_)
