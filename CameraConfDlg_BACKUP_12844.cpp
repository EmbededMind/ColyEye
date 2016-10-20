// CameraConfDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColyEye.h"
#include "CameraConfDlg.h"
#include "afxdialogex.h"
<<<<<<< HEAD
#include "RecordFileManager.h"
=======

#include "CameraOffConfirmDlg.h"
#include "CameraStoreOffConfirmDlg.h"

>>>>>>> 766a6c5d8294362b7725d220ffda10ac14f933cc

// CCameraConfDlg �Ի���

IMPLEMENT_DYNAMIC(CCameraConfDlg, CDialogEx)

CCameraConfDlg::CCameraConfDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAMERA_CONF, pParent)
	, mCurrName(_T(""))
{

}

CCameraConfDlg::~CCameraConfDlg()
{
}

void CCameraConfDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mCurrName);
	DDX_Control(pDX, IDC_SLIDER1, mSlider);
	DDX_Control(pDX, IDC_BUTTON1, mSwitcher);
	DDX_Control(pDX, IDC_BUTTON2, mPicDirection);
	DDX_Control(pDX, IDC_BUTTON3, mStoreSwitcher);
	DDX_Control(pDX, IDC_BUTTON4, mAutoWatchSwitcher);
}


BEGIN_MESSAGE_MAP(CCameraConfDlg, CDialogEx)
	ON_MESSAGE(USER_MSG_GIVE_FOCUS, &CCameraConfDlg::OnUserMsgGiveFocus)
	ON_MESSAGE(USER_MSG_DEVICE_CONFIG, &CCameraConfDlg::OnUserMsgDeviceConfig)
	ON_WM_HSCROLL()
<<<<<<< HEAD
=======

>>>>>>> 766a6c5d8294362b7725d220ffda10ac14f933cc
	ON_BN_CLICKED(IDC_BUTTON1, &CCameraConfDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCameraConfDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCameraConfDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CCameraConfDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CCameraConfDlg ��Ϣ��������


void CCameraConfDlg::FocusJumpTo(int dst_id)
{
	GetDlgItem(dst_id)->SetFocus();
}

BOOL CCameraConfDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ�����ר�ô����/����û���
	if (pMsg->message == WM_KEYDOWN) {
			int id = GetFocus()->GetDlgCtrlID();

		switch (pMsg->wParam)
		{
		case VK_SPACE:
			if (id == IDC_EDIT1) {
				TRACE("camera name edit space\n");
				if (mNameConfPanel.IsVisible()) {
					mNameConfPanel.ShowPanel(SW_HIDE);
					mOtherConfPanel.MovePanel(0, -100);
				}
				else {
					mNameConfPanel.ShowPanel(SW_SHOW);
					mOtherConfPanel.MovePanel(0, 100);
					GetDlgItem(1)->SetFocus();
				}				
			 }
			return true;
        
		case VK_UP:
			// ����ѡ��
			if (id >= 1 && id <= 18) {
				if (id > 4) {
					FocusJumpTo(id - 4);
				}
			}
			else {
				//
			}
			return true;

		case VK_DOWN:
			if (id >= 1 && id <= 18) {
				if (id < 15) {
					FocusJumpTo(id + 4);
				}
			}
			else
			{
				//
			}
			return true;

		case VK_LEFT:
			if (id >= 1 && id <= 18) {
				if (id > 1) {
					FocusJumpTo(id - 1);
				}
				return true;
			}
			break;

		case VK_RIGHT:
			if (id >= 1 && id <= 18) {
				if (id < 18) {
					FocusJumpTo(id + 1);
				}
				return true;
			}
			break;

		case VK_RETURN:
			if (id >= 1 && id <= 18) {

				GetDlgItem(IDC_EDIT1)->SetFocus();
				CString name;
				((CTagButton*)GetDlgItem(id))->GetWindowTextW(name);
				((CEdit*)GetDlgItem(IDC_EDIT1))->SetWindowTextW(name);
				mNameConfPanel.ShowPanel(SW_HIDE);
				mOtherConfPanel.MovePanel(0, -100);
				return true;
			}
			break;
			
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


BOOL CCameraConfDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ����Ӷ���ĳ�ʼ��
	mVolume = 5;
	InitNameItem();
	InitPanel();
	mSlider.SetRange(0,10,TRUE);
	mSlider.SetTicFreq(1);
	mSlider.SetPos(mVolume);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CCameraConfDlg::ShowConfigurationOf(CCamera* whichCamera)
{
	if (whichCamera->userConf.name_inx == 0) {
		mCurrName.Format(_T("�����%d"), whichCamera->mId);
	}
	else if (whichCamera->userConf.name_inx <= 18) {
		((CTagButton*)GetDlgItem(whichCamera->userConf.name_inx))->GetWindowTextW(mCurrName);
	}

	mVolume = whichCamera->userConf.vol;
	
	if (whichCamera->userConf.toggleConf & CAMERA_USER_CONF_ON) {
		mSwitcher.SetWindowTextW(_T("��"));
	}
	else {
		mSwitcher.SetWindowTextW(_T("��"));
	}

	if (whichCamera->userConf.toggleConf & CAMERA_USER_CONF_UP) {
		mPicDirection.SetWindowTextW(_T("���ŷ�"));
	}
	else {
		mPicDirection.SetWindowTextW(_T("���ŷ�"));
	}

	if (whichCamera->userConf.toggleConf & CAMERA_USER_CONF_STORE) {
		mStoreSwitcher.SetWindowTextW(_T("��"));
	}
	else {
		mStoreSwitcher.SetWindowTextW(_T("��"));
	}

	if (whichCamera->userConf.toggleConf & CAMERA_USER_CONF_AWATCH) {
		mAutoWatchSwitcher.SetWindowTextW(_T("��"));
	}
	else {
		mAutoWatchSwitcher.SetWindowTextW(_T("��"));
	}

	UpdateData(FALSE);
}



void CCameraConfDlg::InitPanel()
{
	for (int i = 0; i < 18; i++) {
		mNameConfPanel.AddWindow(GetDlgItem(i+1));
	}

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC1));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC2));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC3));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC4));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC5));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC6));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_STATIC7));

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON1));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON2));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON3));
	mOtherConfPanel.AddWindow(GetDlgItem(IDC_BUTTON4));

	mOtherConfPanel.AddWindow(GetDlgItem(IDC_SLIDER1));
}



void CCameraConfDlg::InitNameItem()
{
	CString name;
	RECT rClient;
	RECT r = {5, 45, 60, 30};
	GetClientRect(&rClient);


	//name.LoadStringW(IDS_STR_CAMERA_NAME_1);
	//mNameItems[0].Create(name, WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON, r, this, 1);


	for (int i = 0; i < 18; i++) {
		name.LoadStringW(IDS_STR_CAMERA_NAME_1+i);

		r.left = rClient.left + (i % 4) * 85 + 40;
		r.top = rClient.top + (i / 4) * 25 + 45;
		r.right = r.left + 80;
		r.bottom = r.top + 20;


		mNameItems[i].Create(name, WS_CHILD  | BS_PUSHBUTTON, r, this, i+1);
		mNameItems[i].SetFont(GetFont() , true);
	}
}


afx_msg LRESULT CCameraConfDlg::OnUserMsgGiveFocus(WPARAM wParam, LPARAM lParam)
{
	GetDlgItem(IDC_EDIT1)->SetFocus();

	return 0;
}


afx_msg LRESULT CCameraConfDlg::OnUserMsgDeviceConfig(WPARAM wParam, LPARAM lParam)
{	
	pCamera = CCameraManager::getInstance()->mLoginDevice[wParam-1];
	if (pCamera != NULL) {
		//   ˢ��������
		ShowConfigurationOf(pCamera);
	}
	return 0;
}


void CCameraConfDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	int curpos = mSlider.GetPos();
	switch (nSBCode)
	{
	case SB_ENDSCROLL:
		if (mVolume != curpos)
		{
			mVolume = curpos;
			TRACE(_T("mVolume = %d\n"), mVolume);
		}
		break;
	}	
	CDialogEx::OnHScroll(nSBCode, mVolume, pScrollBar);

}


void CCameraConfDlg::OnBnClickedButton1()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
<<<<<<< HEAD
	if (pCamera->mLoginId)
	{
		pCamera->stopRecord();
		RecordFileManager* pMgr = RecordFileManager::GetInstance();
		pMgr->RecallRecordFile(pCamera->mId, RECORD_TYPE_NORMAL);
		pCamera->logout();
	}
	else
	{
		pCamera->login();
		RecordFileManager* pMgr = RecordFileManager::GetInstance();
		pCamera->startRecord(pMgr->DistributeRecordFile(pCamera->mId, RECORD_TYPE_NORMAL));
=======
	ASSERT(pCamera != NULL);

	// �����ǿ�������������
	if (pCamera->userConf.toggleConf & CAMERA_USER_CONF_ON) {
		CCameraOffConfirmDlg dlg;
		if (dlg.DoModal() == IDOK) {
			TRACE("ȷ���ر������\n");
			mSwitcher.SetWindowTextW(_T("��"));
			pCamera->userConf.toggleConf &= (~CAMERA_USER_CONF_ON);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		}
		else {
			TRACE("ȡ���ر������\n");
		}
	}
	// �����ǹرգ����ڿ���
	else {
		mSwitcher.SetWindowTextW(_T("��"));
		pCamera->userConf.toggleConf |= CAMERA_USER_CONF_ON;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
>>>>>>> 766a6c5d8294362b7725d220ffda10ac14f933cc
	}
}


<<<<<<< HEAD
void CCameraConfDlg::OnBnClickedButton2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}


void CCameraConfDlg::OnBnClickedButton3()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
}


void CCameraConfDlg::OnBnClickedButton4()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
=======
/**@brief ������Ƶ����ť
 *
 */
void CCameraConfDlg::OnBnClickedButton2()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	ASSERT(pCamera != NULL);


}


/**@brief ��Ƶ�洢���ܿ���
 *
 */
void CCameraConfDlg::OnBnClickedButton3()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	ASSERT(pCamera != NULL);

	//���������˴洢����������ˣ����˹ر�
	if (pCamera->userConf.toggleConf & CAMERA_USER_CONF_STORE) {
		CCameraStoreOffConfirmDlg dlg;
		if (dlg.DoModal() == IDOK) {
			mStoreSwitcher.SetWindowTextW(_T("�ر�"));
			pCamera->userConf.toggleConf &= (~CAMERA_USER_CONF_STORE);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		}
	}
	// �����ǹرգ����ڿ���
	else {
		mStoreSwitcher.SetWindowTextW(_T("����"));
		pCamera->userConf.toggleConf |= CAMERA_USER_CONF_STORE;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
	}
}


/**@brief �Զ��������ܿ���
 *
 */
void CCameraConfDlg::OnBnClickedButton4()
{
	// TODO: �ڴ����ӿؼ�֪ͨ�����������
	//�����������Զ���������������ˣ����˹ر�
	if (pCamera->userConf.toggleConf & CAMERA_USER_CONF_AWATCH) {
		//CCameraStoreOffConfirmDlg dlg;
		//if (dlg.DoModal() == IDOK) {
			mStoreSwitcher.SetWindowTextW(_T("�ر�"));
			pCamera->userConf.toggleConf &= (~CAMERA_USER_CONF_AWATCH);
			::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, false, (LPARAM)pCamera);
		//}
	}
	// �����ǹرգ����ڿ���
	else {
		mStoreSwitcher.SetWindowTextW(_T("����"));
		pCamera->userConf.toggleConf |= CAMERA_USER_CONF_AWATCH;
		::SendMessage(((CColyEyeApp*)AfxGetApp())->m_pWallWnd->m_hWnd, USER_MSG_DEVICE_CONFIG, true, (LPARAM)pCamera);
	}
>>>>>>> 766a6c5d8294362b7725d220ffda10ac14f933cc
}