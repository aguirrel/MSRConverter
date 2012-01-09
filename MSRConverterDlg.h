// MSRConverterDlg.h : header file
//

#if !defined(AFX_MSRConverterDLG_H__B45B2C1E_7D32_468B_B152_22912079949E__INCLUDED_)
#define AFX_MSRConverterDLG_H__B45B2C1E_7D32_468B_B152_22912079949E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _TIMER_CHANGEBMP_   7769
#define _TIMER_CHANGEICO_   7770
#define _TIMER_ELAPSE_BMP_  2500
#define _TIMER_ELAPSE_ICO_  1800

#include "ImageLoader.h"

/////////////////////////////////////////////////////////////////////////////
// CMSRConverterDlg dialog

class CMSRConverterDlg : public CDialog
{
// Construction
public:
	CMSRConverterDlg(CWnd* pParent = NULL);	// standard constructor
    /**
     * Change the static image using the CImageLoader
     */
    void ChangeBitmap();
    /**
     * Change the cursor aperance using the CImageLoader
     */
    void ChangeCursor();


// Dialog Data
	//{{AFX_DATA(CMSRConverterDlg)
	enum { IDD = IDD_MSRConverter_DIALOG };
	CStatic	m_BmpImage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMSRConverterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
    /// The CImageLoader
    CImageLoader m_Images;
    /// It increments everytime the mouse moves.
    int m_iTicMouseMove;

	// Generated message map functions
	//{{AFX_MSG(CMSRConverterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSRConverterDLG_H__B45B2C1E_7D32_468B_B152_22912079949E__INCLUDED_)
