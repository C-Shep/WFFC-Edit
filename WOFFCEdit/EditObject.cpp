#include "stdafx.h"
#include "EditObject.h"


// SelectDialogue dialog

IMPLEMENT_DYNAMIC(EditObject, CDialogEx)

//Message map.  Just like MFCMAIN.cpp.  This is where we catch button presses etc and point them to a handy dandy method.
BEGIN_MESSAGE_MAP(EditObject, CDialogEx)
//	ON_COMMAND(IDOK, &EditObject::End)					//ok button
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
void EditObject::SetObjectData(ToolMain* toolMain, std::vector<SceneObject>* SceneGraph, int* selection)
{
	tool = toolMain;
	m_sceneGraph = SceneGraph;
	m_currentSelection = selection;

	tool->dontSelect = true;

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
	CDialogEx::PostNcDestroy();
	tool->dontSelect = false;
	delete this;
}

void EditObject::OnBnClickedOk()
{
	tool->dontSelect = false;

	if (!m_sceneGraph || !m_currentSelection) {
		AfxMessageBox(L"Scene graph or selection is null!");
		tool->dontSelect = false;
		return;
	}

	int index = *m_currentSelection;

	if (index < 0 || index >= m_sceneGraph->size()) {
		AfxMessageBox(L"Selection index out of bounds!");
		tool->dontSelect = false;
		return;
	}

	SceneObject& obj = m_sceneGraph->at(index); // modify directly

	obj = m_sceneGraph->at(*m_currentSelection);

	int textNumber = 0;
	wchar_t numberraw[20] = {0};

	GetDlgItemText(IDC_X, numberraw, _countof(numberraw));

	swscanf_s(numberraw, L"%d", &textNumber);

	obj.posX = textNumber;

	tool->renderDisplayList();

	CDialogEx::OnOK();
}

