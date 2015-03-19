
// DESmfcdemoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DESmfcdemo.h"
#include "DESmfcdemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDESmfcdemoDlg 对话框




CDESmfcdemoDlg::CDESmfcdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDESmfcdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDESmfcdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_key);
	//  DDX_Control(pDX, IDC_EDIT2, m_outdir);
	DDX_Control(pDX, IDC_EDIT2, m_endir);
	DDX_Control(pDX, IDC_EDIT3, m_dedir);
}

BEGIN_MESSAGE_MAP(CDESmfcdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON3, &CDESmfcdemoDlg::ChooseEndir)
	ON_BN_CLICKED(IDC_BUTTON4, &CDESmfcdemoDlg::ChooseDedir)
	ON_BN_CLICKED(IDC_BUTTON1, &CDESmfcdemoDlg::ChooseFile)
	ON_BN_CLICKED(IDC_BUTTON2, &CDESmfcdemoDlg::ChooseDir)
	ON_BN_CLICKED(IDC_BUTTON5, &CDESmfcdemoDlg::Encrypt)
	ON_BN_CLICKED(IDC_BUTTON6, &CDESmfcdemoDlg::Decrypt)
END_MESSAGE_MAP()


// CDESmfcdemoDlg 消息处理程序

BOOL CDESmfcdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDESmfcdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDESmfcdemoDlg::OnPaint()
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
HCURSOR CDESmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//选择加密输出目录函数
void CDESmfcdemoDlg::ChooseEndir()
{
	char dir[MAX_PATH];  //存放选择的目录路径

    BROWSEINFO bi;  //用于存放选中目录信息
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "请选择加密输出目录：";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //弹出选择目录对话框  

    if(lp && SHGetPathFromIDList(lp, dir))  //用户选中目录  
    {
		m_endir.SetWindowTextA(dir);  //设置Edit显示完整路径
    }
}

//选择解密输出目录函数
void CDESmfcdemoDlg::ChooseDedir()
{
	char dir[MAX_PATH];  //存放选择的目录路径

    BROWSEINFO bi;  //用于存放选中目录信息
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "请选择解密输出目录：";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //弹出选择目录对话框  

    if(lp && SHGetPathFromIDList(lp, dir))  //用户选中目录  
    {
		m_dedir.SetWindowTextA(dir);  //设置Edit显示完整路径
    }
}

//选择文件函数
void CDESmfcdemoDlg::ChooseFile()
{
	CFileDialog filedialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, NULL, this);  //创建打开文件对话框
	if(filedialog.DoModal() == IDOK)  //调用DoModal显示对话框
	{
		//添加新文件时清空原文件列表
		filelist.clear();
		//更新文件信息
		fileinfo.from = "";
		fileinfo.file = filedialog.GetPathName().GetBuffer(0);  //获取选择的文件完整路径，包含文件名及扩展名
		filelist.push_back(fileinfo);  //把选择的文件路径加入文件列表
	}
}

//选择文件目录函数
void CDESmfcdemoDlg::ChooseDir()
{
	char dir[MAX_PATH];  //存放选择的目录路径

    BROWSEINFO bi;  //用于存放选中目录信息
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "请选择要添加的文件目录：";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //弹出选择目录对话框  

    if(lp && SHGetPathFromIDList(lp, dir))  //用户选中目录  
    {
		//添加新文件时清空原文件列表
		filelist.clear();
		//更新文件目录信息
		fileinfo.from = dir;
		AddFile(dir);  //设置Edit显示完整路径
    }
}

//添加目录下所有文件到文件列表函数
void CDESmfcdemoDlg::AddFile(CString Curdir)
{
	CFileFind filefind;  //定义文件查找类对象
	BOOL bfind = filefind.FindFile(Curdir + "\\*.*");  //使用用户选中目录调用FindFile函数
	while(bfind)
	{
		bfind = filefind.FindNextFile();  //查找下一个文件
		CString filename = filefind.GetFileName();  //获取文件名
		if(filefind.IsDirectory() && filename[0] != _TEXT('.'))
		{
			AddFile(filefind.GetFilePath());  //当前为目录时，递归遍历子目录
		}
		else if(filename[0] != _TEXT('.'))  //当前为文件类型
		{
			//更新文件信息
			fileinfo.file = filefind.GetFilePath().GetBuffer(0);
			filelist.push_back(fileinfo);  //把文件加入文件列表
		}
	}
}

//加密操作函数
void CDESmfcdemoDlg::Encrypt()
{
	//文件列表为空提示用户并退出函数
	if(filelist.empty())
	{
		AfxMessageBox("请先选择文件或目录！");
		return;
	}
	CString key;  //密钥
	CString en_dir;  //加密输出目录
	CString de_dir;  //解密输出目录
	//从界面控件获取相应值
	m_key.GetWindowText(key);
	m_endir.GetWindowText(en_dir);
	m_dedir.GetWindowText(de_dir);

	//密钥为空提示用户并退出函数
	if(key == "")
	{
		AfxMessageBox("请先输入密钥！");
		return;
	}
	//初始化已完成任务线程数
	thread_finished = 0;
	//创建并初始化task类对象
	task t(GetSafeHwnd(), key.GetBuffer(0), filelist, en_dir.GetBuffer(0), de_dir.GetBuffer(0));
	//调用对象任务函数
	t.DoTask(0, 0);
}

//解密操作函数
void CDESmfcdemoDlg::Decrypt()
{
	//文件列表为空提示用户并退出函数
	if(filelist.empty())
	{
		AfxMessageBox("请先选择文件或目录！");
		return;
	}
	CString key;  //密钥
	CString en_dir;  //加密输出目录
	CString de_dir;  //解密输出目录
	//从界面控件获取相应值
	m_key.GetWindowText(key);
	m_endir.GetWindowText(en_dir);
	m_dedir.GetWindowText(de_dir);

	//密钥为空提示用户并退出函数
	if(key == "")
	{
		AfxMessageBox("请先输入密钥！");
		return;
	}
	//初始化已完成任务线程数
	thread_finished = 0;
	//创建并初始化task类对象
	task t(GetSafeHwnd(), key.GetBuffer(0), filelist, en_dir.GetBuffer(0), de_dir.GetBuffer(0));
	//调用对象任务函数
	t.DoTask(-1, 2);
}


//接收线程结束消息函数
BOOL CDESmfcdemoDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(message == WM_FINISHMSG)
	{
		thread_finished++;
		if(thread_finished == 2)
		{	
			CString msg;
			msg.Format("%d已完成！", ((vector<int> *)wParam) ->size());
			AfxMessageBox(msg);
		}
	}

	if (message == WM_ONEFINISHMSG)
	{
		
	}

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}
