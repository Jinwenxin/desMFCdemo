
// DESmfcdemoDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "encrypt.h"
#include <string>

// CDESmfcdemoDlg �Ի���
class CDESmfcdemoDlg : public CDialogEx
{
// ����
public:
	CDESmfcdemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DESMFCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	// ��Կ
	CEdit m_key;
	// ���Ŀ¼
	CEdit m_endir;
	CEdit m_dedir;
	//��ť
	afx_msg void ChooseEndir();
	afx_msg void ChooseDedir();
	afx_msg void ChooseFile();
	afx_msg void ChooseDir();
	afx_msg void Encrypt();
	afx_msg void Decrypt();
	//�ļ��б�
	Fvector filelist;
	//�ļ���Ϣ
	File fileinfo;
	 //�������Ŀ¼���ļ����ļ��б���
	void AddFile(CString Curdir); 
	
};
