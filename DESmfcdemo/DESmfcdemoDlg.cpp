
// DESmfcdemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DESmfcdemo.h"
#include "DESmfcdemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDESmfcdemoDlg �Ի���




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


// CDESmfcdemoDlg ��Ϣ�������

BOOL CDESmfcdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDESmfcdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDESmfcdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ѡ��������Ŀ¼����
void CDESmfcdemoDlg::ChooseEndir()
{
	char dir[MAX_PATH];  //���ѡ���Ŀ¼·��

    BROWSEINFO bi;  //���ڴ��ѡ��Ŀ¼��Ϣ
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "��ѡ��������Ŀ¼��";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //����ѡ��Ŀ¼�Ի���  

    if(lp && SHGetPathFromIDList(lp, dir))  //�û�ѡ��Ŀ¼  
    {
		m_endir.SetWindowTextA(dir);  //����Edit��ʾ����·��
    }
}

//ѡ��������Ŀ¼����
void CDESmfcdemoDlg::ChooseDedir()
{
	char dir[MAX_PATH];  //���ѡ���Ŀ¼·��

    BROWSEINFO bi;  //���ڴ��ѡ��Ŀ¼��Ϣ
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "��ѡ��������Ŀ¼��";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //����ѡ��Ŀ¼�Ի���  

    if(lp && SHGetPathFromIDList(lp, dir))  //�û�ѡ��Ŀ¼  
    {
		m_dedir.SetWindowTextA(dir);  //����Edit��ʾ����·��
    }
}

//ѡ���ļ�����
void CDESmfcdemoDlg::ChooseFile()
{
	CFileDialog filedialog(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, NULL, this);  //�������ļ��Ի���
	if(filedialog.DoModal() == IDOK)  //����DoModal��ʾ�Ի���
	{
		//������ļ�ʱ���ԭ�ļ��б�
		filelist.clear();
		//�����ļ���Ϣ
		fileinfo.from = "";
		fileinfo.file = filedialog.GetPathName().GetBuffer(0);  //��ȡѡ����ļ�����·���������ļ�������չ��
		filelist.push_back(fileinfo);  //��ѡ����ļ�·�������ļ��б�
	}
}

//ѡ���ļ�Ŀ¼����
void CDESmfcdemoDlg::ChooseDir()
{
	char dir[MAX_PATH];  //���ѡ���Ŀ¼·��

    BROWSEINFO bi;  //���ڴ��ѡ��Ŀ¼��Ϣ
    bi.hwndOwner = m_hWnd;  
    bi.pidlRoot = NULL;  
    bi.pszDisplayName = dir;  
    bi.lpszTitle = "��ѡ��Ҫ��ӵ��ļ�Ŀ¼��";  
    bi.ulFlags = 0;  
    bi.lpfn = NULL;  
    bi.lParam = 0;  
    bi.iImage = 0;  
   
    LPITEMIDLIST lp = SHBrowseForFolder(&bi);   //����ѡ��Ŀ¼�Ի���  

    if(lp && SHGetPathFromIDList(lp, dir))  //�û�ѡ��Ŀ¼  
    {
		//������ļ�ʱ���ԭ�ļ��б�
		filelist.clear();
		//�����ļ�Ŀ¼��Ϣ
		fileinfo.from = dir;
		AddFile(dir);  //����Edit��ʾ����·��
    }
}

//���Ŀ¼�������ļ����ļ��б���
void CDESmfcdemoDlg::AddFile(CString Curdir)
{
	CFileFind filefind;  //�����ļ����������
	BOOL bfind = filefind.FindFile(Curdir + "\\*.*");  //ʹ���û�ѡ��Ŀ¼����FindFile����
	while(bfind)
	{
		bfind = filefind.FindNextFile();  //������һ���ļ�
		CString filename = filefind.GetFileName();  //��ȡ�ļ���
		if(filefind.IsDirectory() && filename[0] != _TEXT('.'))
		{
			AddFile(filefind.GetFilePath());  //��ǰΪĿ¼ʱ���ݹ������Ŀ¼
		}
		else if(filename[0] != _TEXT('.'))  //��ǰΪ�ļ�����
		{
			//�����ļ���Ϣ
			fileinfo.file = filefind.GetFilePath().GetBuffer(0);
			filelist.push_back(fileinfo);  //���ļ������ļ��б�
		}
	}
}

//���ܲ�������
void CDESmfcdemoDlg::Encrypt()
{
	//�ļ��б�Ϊ����ʾ�û����˳�����
	if(filelist.empty())
	{
		AfxMessageBox("����ѡ���ļ���Ŀ¼��");
		return;
	}
	CString key;  //��Կ
	CString en_dir;  //�������Ŀ¼
	CString de_dir;  //�������Ŀ¼
	//�ӽ���ؼ���ȡ��Ӧֵ
	m_key.GetWindowText(key);
	m_endir.GetWindowText(en_dir);
	m_dedir.GetWindowText(de_dir);

	//��ԿΪ����ʾ�û����˳�����
	if(key == "")
	{
		AfxMessageBox("����������Կ��");
		return;
	}
	//��ʼ������������߳���
	thread_finished = 0;
	//��������ʼ��task�����
	task t(GetSafeHwnd(), key.GetBuffer(0), filelist, en_dir.GetBuffer(0), de_dir.GetBuffer(0));
	//���ö���������
	t.DoTask(0, 0);
}

//���ܲ�������
void CDESmfcdemoDlg::Decrypt()
{
	//�ļ��б�Ϊ����ʾ�û����˳�����
	if(filelist.empty())
	{
		AfxMessageBox("����ѡ���ļ���Ŀ¼��");
		return;
	}
	CString key;  //��Կ
	CString en_dir;  //�������Ŀ¼
	CString de_dir;  //�������Ŀ¼
	//�ӽ���ؼ���ȡ��Ӧֵ
	m_key.GetWindowText(key);
	m_endir.GetWindowText(en_dir);
	m_dedir.GetWindowText(de_dir);

	//��ԿΪ����ʾ�û����˳�����
	if(key == "")
	{
		AfxMessageBox("����������Կ��");
		return;
	}
	//��ʼ������������߳���
	thread_finished = 0;
	//��������ʼ��task�����
	task t(GetSafeHwnd(), key.GetBuffer(0), filelist, en_dir.GetBuffer(0), de_dir.GetBuffer(0));
	//���ö���������
	t.DoTask(-1, 2);
}


//�����߳̽�����Ϣ����
BOOL CDESmfcdemoDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	if(message == WM_FINISHMSG)
	{
		thread_finished++;
		if(thread_finished == 2)
		{	
			CString msg;
			msg.Format("%d����ɣ�", ((vector<int> *)wParam) ->size());
			AfxMessageBox(msg);
		}
	}

	if (message == WM_ONEFINISHMSG)
	{
		
	}

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}
