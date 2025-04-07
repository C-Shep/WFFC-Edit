#include "stdafx.h"
#include "EditObject.h"


// SelectDialogue dialog

IMPLEMENT_DYNAMIC(EditObject, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(EditObject, CDialogEx)
	ON_COMMAND(IDOK, &EditObject::End)					//ok button
	ON_BN_CLICKED(IDOK, &EditObject::OnBnClickedOk)
	ON_COMMAND(IDCANCEL, &EditObject::End)
END_MESSAGE_MAP()


EditObject::EditObject(CWnd* pParent, std::vector<SceneObject>* SceneGraph)		//constructor used in modal
: CDialogEx(IDD_OBPROP, pParent)
{
	m_sceneGraph = SceneGraph;
}

EditObject::EditObject(CWnd* pParent)			//constructor used in modeless
	: CDialogEx(IDD_OBPROP, pParent)
{
}

EditObject::~EditObject()
{
}

///pass through pointers to the data in the tool we want to manipulate
void EditObject::SetObjectData(std::vector<SceneObject>* SceneGraph, int* selection)
{
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

}


void EditObject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void EditObject::End()
{
	DestroyWindow();	//destory the window properly.  INcluding the links and pointers created.  THis is so the dialogue can start again. 
}

void EditObject::Select()
{

}

BOOL EditObject::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void EditObject::PostNcDestroy()
{
}

// SelectDialogue message handlers callback   - We only need this if the dailogue is being setup-with createDialogue().  We are doing
//it manually so its better to use the messagemap
/*INT_PTR CALLBACK SelectProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		//	EndDialog(hwndDlg, wParam);
			DestroyWindow(hwndDlg);
			return TRUE;


		case IDCANCEL:
			EndDialog(hwndDlg, wParam);
			return TRUE;
			break;
		}
	}

	return INT_PTR();
}*/


void EditObject::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	SceneObject obj;
	obj = m_sceneGraph->at(*m_currentSelection);

	//obj.posX =

	CDialogEx::OnOK();
}

