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

	wchar_t XobjPos[20] = L"";
	swprintf_s(XobjPos,L"%f",obj.posX);
	SetDlgItemText(IDC_X, XobjPos);

	wchar_t YobjPos[20] = L"";
	swprintf_s(YobjPos, L"%f", obj.posY);
	SetDlgItemText(IDC_Y, YobjPos);

	wchar_t ZobjPos[20] = L"";
	swprintf_s(ZobjPos, L"%f", obj.posZ);
	SetDlgItemText(IDC_Z, ZobjPos);


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

	//------------------Position------------------
	//X Pos
	int XtextNumber = 0;
	wchar_t Xnumberraw[20] = {0};
	GetDlgItemText(IDC_X, Xnumberraw, _countof(Xnumberraw));
	swscanf_s(Xnumberraw, L"%d", &XtextNumber);
	obj.posX = XtextNumber;

	//Y Pos
	int YtextNumber = 0;
	wchar_t Ynumberraw[20] = { 0 };
	GetDlgItemText(IDC_Y, Ynumberraw, _countof(Ynumberraw));
	swscanf_s(Ynumberraw, L"%d", &YtextNumber);
	obj.posY = YtextNumber;

	//Z Pos
	int ZtextNumber = 0;
	wchar_t Znumberraw[20] = { 0 };
	GetDlgItemText(IDC_Z, Znumberraw, _countof(Znumberraw));
	swscanf_s(Znumberraw, L"%d", &ZtextNumber);
	obj.posZ = ZtextNumber;

	tool->renderDisplayList();

	CDialogEx::OnOK();
}

