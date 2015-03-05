
// DESmfcdemoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "encrypt.h"
#include <string>

// CDESmfcdemoDlg 对话框
class CDESmfcdemoDlg : public CDialogEx
{
// 构造
public:
	CDESmfcdemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DESMFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	// 密钥
	CEdit m_key;
	// 输出目录
	CEdit m_endir;
	CEdit m_dedir;
	//按钮
	afx_msg void ChooseEndir();
	afx_msg void ChooseDedir();
	afx_msg void ChooseFile();
	afx_msg void ChooseDir();
	afx_msg void Encrypt();
	afx_msg void Decrypt();
	//文件列表
	Fvector filelist;
	//文件信息
	File fileinfo;
	 //声明添加目录下文件到文件列表函数
	void AddFile(CString Curdir); 
	
};
