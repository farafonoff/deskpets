// pets3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "pets3.h"
#include "pets3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// Cpets3Dlg dialog




Cpets3Dlg::Cpets3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cpets3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cpets3Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK1, cbFlip);
    DDX_Control(pDX, IDC_RADIO1, rbA);
    DDX_Control(pDX, IDC_RADIO2, rbB);
    DDX_Control(pDX, IDC_RADIO3, rbC);
}

BEGIN_MESSAGE_MAP(Cpets3Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_KEYDOWN()
    ON_BN_CLICKED(IDC_CHECK1, &Cpets3Dlg::OnBnClickedCheck1)
    ON_BN_CLICKED(IDC_RADIO1, &Cpets3Dlg::OnBnClickedRadio1)
    ON_BN_CLICKED(IDC_RADIO2, &Cpets3Dlg::OnBnClickedRadio2)
    ON_BN_CLICKED(IDC_RADIO3, &Cpets3Dlg::OnBnClickedRadio3)
END_MESSAGE_MAP()


// Cpets3Dlg message handlers

CString type("carbot");
CString num("1");
CString path("wave");
CString flip("flip");
CString ext(".wav");
CString sep("\\");
//CString path("");
char* dfire;
char* dfire2;
char* dboost;

char* movements[100];

char* loadFile(CString fname) {
    HANDLE file = CreateFile(fname,GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    DWORD fsize = GetFileSize(file, NULL);
    char* data = (char*)malloc(fsize);
    DWORD read;
    ReadFile(file,data,fsize,&read,NULL);
    CloseHandle(file);
    return data;
}
bool isFlip;

char* loadCommand(char* cs) {
    CString rfile;
    if (isFlip) {
        rfile = path+sep+type+flip+sep+CString(cs)+type+num+flip+ext;
    } else {
        rfile = path+sep+type+sep+CString(cs)+type+num+ext;
    }
    return loadFile(rfile);
}
void loadData() {
    dfire = loadCommand("FIRE");
    dfire2 = loadCommand("FIRE2");
    dboost = loadCommand("BOOSTER");
    memset(movements,0,sizeof(movements));
}

BOOL Cpets3Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    loadData();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ShowWindow(SW_MINIMIZE);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cpets3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cpets3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cpets3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int engState;
int LEFT_ON=1;
int LEFT_FW=2;
int RIGHT_ON=4;
int RIGHT_FW=8;
void playSnd(char* data) {
    sndPlaySound(reinterpret_cast<LPCWSTR>(data),SND_MEMORY|SND_SYNC);
    /*Sleep(80);
    sndPlaySound(reinterpret_cast<LPCWSTR>(data),SND_MEMORY|SND_SYNC);*/
}


void Cpets3Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
    switch(nChar) {
        case ' ':
            playSnd(dfire);
            break;
    }
}


int ST_FW = LEFT_ON|RIGHT_ON|RIGHT_FW|LEFT_FW;
int ST_STOP = 0;
int ST_BACK = LEFT_ON|RIGHT_ON;
int ST_LEFT = LEFT_ON|RIGHT_ON|RIGHT_FW;
int ST_RIGHT = RIGHT_ON|LEFT_ON|LEFT_FW;

int sendState(int engState) {
    if (movements[engState]==0) {
        char* left;
        char* right;
        if (engState&LEFT_ON) {
            if (engState&LEFT_FW) {
                left = "LF";
            } else {
                left = "LB";
            }
        } else {
            left = "LS";
        }
        if (engState&RIGHT_ON) {
            if (engState&RIGHT_FW) {
                right = "RF";
            } else {
                right = "RB";
            }
        } else {
            right = "RS";
        }
        char cbuf[5];
        cbuf[0] = 0;
        strcat(cbuf,left);
        strcat(cbuf,right);
        movements[engState] = loadCommand(cbuf);
    }
    playSnd(movements[engState]);
    return 0;
}

int state(int newState) {
    engState = newState;
    if (newState==ST_STOP) {
        sendState(engState);
        Sleep(80);
        return sendState(engState);
    } else
        return sendState(engState);
}
DWORD minstep = 10;
int shift = 0;

bool isUp;
bool isDown;
bool isLeft;
bool isRight;

void sendCurrentState() {
    if (isUp) {
        if (isLeft&&!isRight) {
            sendState(RIGHT_ON|RIGHT_FW);
        } else
        if (isRight&&!isLeft) {
            sendState(LEFT_ON|LEFT_FW);
        } else {
            sendState(ST_FW);
        }
    } else if (isDown) {
        if (isLeft&&!isRight) {
            sendState(LEFT_ON);
        } else
        if (isRight&&!isLeft) {
            sendState(RIGHT_ON);
        } else {
            sendState(ST_BACK);
        }
    } else {
        if (isLeft&&!isRight) {
            sendState(ST_LEFT);
        } else
        if (isRight&&!isLeft) {
            sendState(ST_RIGHT);
        } else {
            sendState(ST_STOP);
        }
    }
    if (shift) {
        Sleep(minstep);
        state(ST_STOP);
    }
}

BOOL Cpets3Dlg::PreTranslateMessage(MSG * msg) {
    if (msg->message==WM_KEYDOWN) {
        int rpt = msg->lParam&(1<<30);
        if (rpt==1) {
            return TRUE;
        }
        if (msg->wParam==0x5A) {
            playSnd(dfire);
        }
        if (msg->wParam==0x58) {
            playSnd(dfire2);
        }
        if (msg->wParam==0x43) {
            playSnd(dboost);
        }
        if (msg->wParam==VK_SPACE) {
            state(ST_STOP);
        }
        if (msg->wParam==VK_SHIFT) {
            shift = 1;
        }
        if (msg->wParam==VK_UP) {
            isUp = true;
        }
        if (msg->wParam==VK_DOWN) {
            isDown = true;
        }
        if (msg->wParam==VK_LEFT) {
            isLeft = true;
        }
        if (msg->wParam==VK_RIGHT) {
            isRight = true;
        }
        sendCurrentState();
        return TRUE;
    }
    if (msg->message==WM_KEYUP) {
        if (msg->wParam==VK_SHIFT) {
            shift = 0;
        }
        if (msg->wParam==VK_UP) {
            isUp = false;
        }
        if (msg->wParam==VK_DOWN) {
            isDown = false;
        }
        if (msg->wParam==VK_LEFT) {
            isLeft = false;
        }
        if (msg->wParam==VK_RIGHT) {
            isRight = false;
        }
        sendCurrentState();
        return TRUE;
    }
    return CDialog::PreTranslateMessage(msg);
}



void Cpets3Dlg::OnBnClickedCheck1()
{
    isFlip = cbFlip.GetCheck();
}

void Cpets3Dlg::OnBnClickedRadio1()
{
    // TODO: Add your control notification handler code here
}

void Cpets3Dlg::OnBnClickedRadio2()
{
    // TODO: Add your control notification handler code here
}

void Cpets3Dlg::OnBnClickedRadio3()
{
    // TODO: Add your control notification handler code here
}


void updateSoundLib() {
    loadData();
}