// ShareFileSelect.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "emule.h"
#include "ShareFileSelect.h"
#include ".\sharefileselect.h"


// CShareFileSelect �Ի���

IMPLEMENT_DYNAMIC(CShareFileSelect, CDialog)
CShareFileSelect::CShareFileSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CShareFileSelect::IDD, pParent)
{
}

CShareFileSelect::~CShareFileSelect()
{
}

void CShareFileSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SHAREFILE, m_ShareFileList);
}


BEGIN_MESSAGE_MAP(CShareFileSelect, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// CShareFileSelect ��Ϣ��������
BOOL CShareFileSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	CenterWindow();
	m_ShareFileList.SetExtendedStyle(LVS_EX_CHECKBOXES | LVS_EX_FULLROWSELECT);

	m_ShareFileList.InsertColumn(0, GetResString(IDS_ADDTASKDLG_FILENAME), LVCFMT_LEFT, 400);
	m_ShareFileList.InsertColumn(1, _T(""), LVCFMT_LEFT, 40);//spacehold
    GetDlgItem(IDOK)->SetWindowText(GetResString(IDS_OK));
	GetDlgItem(IDCANCEL)->SetWindowText(GetResString(IDS_CANCEL));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CShareFileSelect::ShowFile(CString strDir)
{
	if (strDir.Right(1) != _T('\\'))
		strDir += _T('\\');

	m_strDir = strDir;

	CFileFind finder;
	BOOL bWorking = finder.FindFile(strDir+_T("*.*"));
	
	int index = 0;

	while (bWorking)
	{
		bWorking = finder.FindNextFile();

		if (finder.IsDirectory())
		{
			continue;
		}

		int iItemIndex = m_ShareFileList.InsertItem(index, _T(""));

		CString strFilename = finder.GetFileName();
		
		m_ShareFileList.SetItemText(iItemIndex, 0, strFilename);

		index++;
	}

	finder.Close();
}
void CShareFileSelect::OnBnClickedOk()
{
	int	iItemCount = m_ShareFileList.GetItemCount();

	for (int i = 0; i < iItemCount; i++)
	{
		BOOL bCheck = m_ShareFileList.GetCheck(i);
		
		if (bCheck)
		{
			CString strFileName = m_ShareFileList.GetItemText(i, 0);
			CGlobalVariable::filemgr.AddLocalSharedFile(m_strDir + strFileName, true);
		}
	}

	OnOK();
}

void CShareFileSelect::OnBnClickedCancel()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	OnCancel();
}

void CShareFileSelect::OnNcDestroy()
{
	CDialog::OnNcDestroy();

	// TODO: �ڴ˴�������Ϣ�����������
	delete this;
}