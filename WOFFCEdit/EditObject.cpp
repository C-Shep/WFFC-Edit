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
		tool->dontSelect = false;
		return;
	}

	int index = *m_currentSelection;

	if (index < 0 || index >= m_sceneGraph->size()) {
		AfxMessageBox(L"Please select an object!");
		tool->dontSelect = false;
		return;
	}

	SceneObject& obj = m_sceneGraph->at(index);

	obj = m_sceneGraph->at(*m_currentSelection);

	//

	//Position
	wchar_t XobjPos[20] = L"";
	swprintf_s(XobjPos,L"%f",obj.posX);
	SetDlgItemText(IDC_X_Pos, XobjPos);

	wchar_t YobjPos[20] = L"";
	swprintf_s(YobjPos, L"%f", obj.posY);
	SetDlgItemText(IDC_Y_Pos, YobjPos);

	wchar_t ZobjPos[20] = L"";
	swprintf_s(ZobjPos, L"%f", obj.posZ);
	SetDlgItemText(IDC_Z_Pos, ZobjPos);

	//Rotation
	wchar_t XobjRot[20] = L"";
	swprintf_s(XobjRot, L"%f", obj.rotX);
	SetDlgItemText(IDC_X_Rot, XobjRot);

	wchar_t YobjRot[20] = L"";
	swprintf_s(YobjRot, L"%f", obj.rotY);
	SetDlgItemText(IDC_Y_Rot, YobjRot);

	wchar_t ZobjRot[20] = L"";
	swprintf_s(ZobjRot, L"%f", obj.rotZ);
	SetDlgItemText(IDC_Z_Rot, ZobjRot);

	//Scale
	wchar_t XobjScale[20] = L"";
	swprintf_s(XobjScale, L"%f", obj.scaX);
	SetDlgItemText(IDC_X_Scale, XobjScale);

	wchar_t YobjScale[20] = L"";
	swprintf_s(YobjScale, L"%f", obj.scaY);
	SetDlgItemText(IDC_Y_Scale, YobjScale);

	wchar_t ZobjScale[20] = L"";
	swprintf_s(ZobjScale, L"%f", obj.scaZ);
	SetDlgItemText(IDC_Z_Scale, ZobjScale);
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
		tool->dontSelect = false;
		return;
	}

	int index = *m_currentSelection;

	if (index < 0 || index >= m_sceneGraph->size()) {
		AfxMessageBox(L"Please select an object!");
		tool->dontSelect = false;
		return;
	}

	tool->addUndo();

	SceneObject& obj = m_sceneGraph->at(index); // modify directly

	obj = m_sceneGraph->at(*m_currentSelection);

	//------------------Position------------------
	//X Pos
	int XtextNumber = 0;
	wchar_t Xnumberraw[20] = {0};
	GetDlgItemText(IDC_X_Pos, Xnumberraw, _countof(Xnumberraw));
	swscanf_s(Xnumberraw, L"%d", &XtextNumber);
	obj.posX = XtextNumber;

	//Y Pos
	int YtextNumber = 0;
	wchar_t Ynumberraw[20] = { 0 };
	GetDlgItemText(IDC_Y_Pos, Ynumberraw, _countof(Ynumberraw));
	swscanf_s(Ynumberraw, L"%d", &YtextNumber);
	obj.posY = YtextNumber;

	//Z Pos
	int ZtextNumber = 0;
	wchar_t Znumberraw[20] = { 0 };
	GetDlgItemText(IDC_Z_Pos, Znumberraw, _countof(Znumberraw));
	swscanf_s(Znumberraw, L"%d", &ZtextNumber);
	obj.posZ = ZtextNumber;

	//------------------Rotation------------------
	//X Rot
	int XtextNumberRot = 0;
	wchar_t XnumberrawRot[20] = { 0 };
	GetDlgItemText(IDC_X_Rot, XnumberrawRot, _countof(XnumberrawRot));
	swscanf_s(XnumberrawRot, L"%d", &XtextNumberRot);
	obj.rotX = XtextNumberRot;

	//Y Rot
	int YtextNumberRot = 0;
	wchar_t YnumberrawRot[20] = { 0 };
	GetDlgItemText(IDC_Y_Rot, YnumberrawRot, _countof(YnumberrawRot));
	swscanf_s(YnumberrawRot, L"%d", &YtextNumberRot);
	obj.rotY = YtextNumberRot;

	//Z Rot
	int ZtextNumberRot = 0;
	wchar_t ZnumberrawRot[20] = { 0 };
	GetDlgItemText(IDC_Z_Rot, ZnumberrawRot, _countof(ZnumberrawRot));
	swscanf_s(ZnumberrawRot, L"%d", &ZtextNumberRot);
	obj.rotZ = ZtextNumberRot;

	//------------------Scale------------------
	//X Scale
	int XtextNumberScale = 0;
	wchar_t XnumberrawScale[20] = { 0 };
	GetDlgItemText(IDC_X_Scale, XnumberrawScale, _countof(XnumberrawScale));
	swscanf_s(XnumberrawScale, L"%d", &XtextNumberScale);
	obj.scaX = XtextNumberScale;

	//Y Scale
	int YtextNumberScale = 0;
	wchar_t YnumberrawScale[20] = { 0 };
	GetDlgItemText(IDC_Y_Scale, YnumberrawScale, _countof(YnumberrawScale));
	swscanf_s(YnumberrawScale, L"%d", &YtextNumberScale);
	obj.scaY = YtextNumberScale;

	//Z Scale
	int ZtextNumberScale = 0;
	wchar_t ZnumberrawScale[20] = { 0 };
	GetDlgItemText(IDC_Z_Scale, ZnumberrawScale, _countof(ZnumberrawScale));
	swscanf_s(ZnumberrawScale, L"%d", &ZtextNumberScale);
	obj.scaZ = ZtextNumberScale;

	//Render all the stuff cuz u just updated an object
	tool->renderDisplayList();
	
	CDialogEx::OnOK();
}

