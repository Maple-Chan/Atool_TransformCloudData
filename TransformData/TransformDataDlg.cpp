
// TransformDataDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "TransformData.h"
#include "TransformDataDlg.h"
#include "afxdialogex.h"
#include "readFile.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

std::string fileSrc = "data.asc";
std::string fileDst = "mk2.mk2";

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTransformDataDlg 对话框



CTransformDataDlg::CTransformDataDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANSFORMDATA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTransformDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTransformDataDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTransformDataDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTransformDataDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTransformDataDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CTransformDataDlg 消息处理程序

BOOL CTransformDataDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CString initone;
	CString inittwo;

	//::WritePrivateProfileStringW(_T("TransformData"), _T("Form"), (indexList), _T("..\\config.ini"));
	//::WritePrivateProfileStringW(_T("TransformData"), _T("Seprator"), (separator), _T("..\\config.ini"));

	GetPrivateProfileString(_T("TransformData"), _T("Form"), CString(""), initone.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\config.ini"));
	GetPrivateProfileString(_T("TransformData"), _T("Seprator"), CString(""), inittwo.GetBuffer(MAX_PATH), MAX_PATH, _T("..\\config.ini"));

	SetDlgItemText(IDC_EDIT1, (initone));
	SetDlgItemText(IDC_EDIT2, inittwo);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTransformDataDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTransformDataDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTransformDataDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTransformDataDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}





CString separator;//从窗口中读取给这里赋值
CString indexList;//存储坐标、向量各个值所在的位置


void CTransformDataDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT1);
	//赋值1
	//pBoxOne-> SetWindowText( _T("FOO ") );
	//取值
	CString str;
	pBoxOne->GetWindowText(str);
	indexList = str;



	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT2);
	//赋值2
	//pBoxOne-> SetWindowText( _T("FOO ") );
	//取值
	pBoxOne->GetWindowText(str);
	separator = str;


	maple::readFile transformOBJ(fileSrc, fileDst);
	bool flag = false;
	flag = transformOBJ.dealData();

	if (flag)
	{//弹出成功
		str = "转换成功";

		//向D盘写入程序数据库连接ini文件信息，默认设置如下
		CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
		BOOL ifFind = finder.FindFile(_T("..\\config.ini"));

		::WritePrivateProfileStringW(_T("TransformData"), _T("Form"), (indexList), _T("..\\config.ini"));
		::WritePrivateProfileStringW(_T("TransformData"), _T("Seprator"),(separator), _T("..\\config.ini"));
		

		MessageBox(str, _T("格式转换"), MB_OK);
	}
	else
	{//弹出失败
		str = "转换失败，请检查：\n    ①输入的是否是英文符号、\n    ②分隔符是否正确";
		MessageBox(str, _T("格式转换"), MB_OK);
	}


}


void CTransformDataDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FilePathName;
	CFileDialog dlg(TRUE, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)_TEXT("All Files (*.*)|*.*|Text Files (*.txt)|*.txt|ASC Files (*.asc)|*.asc||"),
		NULL);
	if (dlg.DoModal() == IDOK)
	{
		FilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
		fileSrc = CStringA(FilePathName);
	}
	else
	{
		return;
	}

}
