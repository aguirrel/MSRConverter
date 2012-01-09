// MSRConverterDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MSRConverter.h"
#include "MSRConverterDlg.h"
#include <stdio.h>
#include "winuser.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Global var for the Hook.
HHOOK TheKeyHook; 
HWND TheMainWndHnd;

// Forward reference for the procedure that will be hooked to the keyborad
LRESULT CALLBACK LowLevelKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam);

/////////////////////////////////////////////////////////////////////////////
// CMSRConverterDlg dialog

CMSRConverterDlg::CMSRConverterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMSRConverterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMSRConverterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_iTicMouseMove = 0;
}

void CMSRConverterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMSRConverterDlg)
	DDX_Control(pDX, IDC_IMAGE, m_BmpImage);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMSRConverterDlg, CDialog)
	//{{AFX_MSG_MAP(CMSRConverterDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSRConverterDlg message handlers
BOOL CMSRConverterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
    // The first thing we must do is maximize the window
    RECT rect;
    // Get the size of the screen.
    ////GetDesktopWindow()->GetClientRect (&rect);
    MoveWindow(&rect);
    HINSTANCE ppI = AfxGetInstanceHandle();
    
    // We create the keyboard hook
	TheKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, ppI,0);
    if (TheKeyHook == NULL)
    {
        // If it is an error, we show it and exit the program
        PVOID stmpMsg;
        DWORD itmpErrorCode = GetLastError();
        if (FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                            NULL, itmpErrorCode, 0, (char*)(&stmpMsg), 0, NULL))
        {
            MessageBox((char*)(stmpMsg),"Error hooking keyboard", MB_ICONSTOP | MB_OK);
            LocalFree(stmpMsg);
            _exit(-1);
        }
    }
    

    // Set the image path to .\Images
    m_Images.SetPath(".\\Images");

    // Initialize image and cursor
    ChangeBitmap();
    ChangeCursor();

    // Set the timers for the static image change and the cursor change
    SetTimer(_TIMER_CHANGEBMP_, _TIMER_ELAPSE_BMP_, NULL);
    SetTimer(_TIMER_CHANGEICO_, _TIMER_ELAPSE_ICO_, NULL);

    // Initialize the main window handle
    TheMainWndHnd = m_hWnd;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMSRConverterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
    
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMSRConverterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// This procedure will be called everytime the timer send a WM_TIMER message
void CMSRConverterDlg::OnTimer(UINT nIDEvent) 
{
    if (nIDEvent == _TIMER_CHANGEBMP_)
        ChangeBitmap();
    else if  (nIDEvent == _TIMER_CHANGEICO_)
        ChangeCursor();
	
	CDialog::OnTimer(nIDEvent);
}

// Everytime we get a mouse move, we increment the m_iTicMouseMove.
// If it is 100, then we change the cursor and begin to count again.
void CMSRConverterDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
    m_iTicMouseMove++;
    if (m_iTicMouseMove == 100)
    {
        m_iTicMouseMove = 0;
        ChangeCursor();
    }    
	CDialog::OnMouseMove(nFlags, point);
}

// We want to have the control over the cursor
BOOL CMSRConverterDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    // We ensure to change the cursor
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// CMSRConverterDlg public methods 
void CMSRConverterDlg::ChangeBitmap()
{
    m_Images.SetBitmap(&m_BmpImage);
}

void CMSRConverterDlg::ChangeCursor()
{
    m_Images.NewCursor();
}


/////////////////////////////////////////////////////////////////////////////
// CMSRConverterDlg global functions
LRESULT CALLBACK LowLevelKeyboardProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	//int i;
	int a[3]={0,0,0};
	static int shift_press=0;
    try
    {
        // By returning a non-zero value from the hook procedure, the
        // message does not get passed to the target window
        KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT *) lParam;
        int error=GetLastError();   
        switch (nCode)
        {
            case HC_ACTION:
            {
                
				// Disable all keys except CTRL + ALT + END. 
                // This combination will finish the aplication
                BOOL bControlKeyDown = GetAsyncKeyState (VK_CONTROL) >> ((sizeof(SHORT) * 8) - 1);
                if (pkbhs->vkCode == VK_END && LLKHF_ALTDOWN && bControlKeyDown)
                {
                    UnhookWindowsHookEx(TheKeyHook);
                    SendMessage(TheMainWndHnd,WM_CLOSE,0,0);
                }
                else
				{
					
					if(wParam == WM_KEYDOWN)
					{
						if(pkbhs->vkCode == 160) shift_press=1;

						keybd_event(pkbhs->vkCode, pkbhs->scanCode, 0, NULL);
					}
					else if(wParam == WM_KEYUP)
					{
						if(pkbhs->vkCode == 160 && shift_press == 1) return 1;
						
						keybd_event(pkbhs->vkCode, pkbhs->scanCode, KEYEVENTF_KEYUP, NULL);

						if(shift_press == 1)
						{
							keybd_event(160, 42, KEYEVENTF_KEYUP, NULL);
						}
						
					}

                    return 1;
				}

                break;
            } 

            default:
                break;
        }
        CallNextHookEx (TheKeyHook, nCode, wParam, lParam);
    }
    catch(...)
    {
    }
    return 0;
} 

