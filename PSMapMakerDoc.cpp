// PSMapMakerDoc.cpp : implementation of the CPSMapMakerDoc class
//

#include "stdafx.h"
#include "PSMapMaker.h"

#include "PSMapMakerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerDoc

IMPLEMENT_DYNCREATE(CPSMapMakerDoc, CDocument)

BEGIN_MESSAGE_MAP(CPSMapMakerDoc, CDocument)
	//{{AFX_MSG_MAP(CPSMapMakerDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerDoc construction/destruction

CPSMapMakerDoc::CPSMapMakerDoc()
{
}

CPSMapMakerDoc::~CPSMapMakerDoc()
{
}

BOOL CPSMapMakerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerDoc serialization

void CPSMapMakerDoc::Serialize(CArchive& ar)
{
long buffer;

	if (ar.IsStoring()){
		buffer= 0x05710571;
		ar.Write(&buffer, 4);
		ar.Write(&m_level.m_name, 128);
		for(int i= 0; i < NB_MAPS; ++i){
			ar.Write(&m_level.m_map[i].m_nBlocsUse, 4);
			ar.Write(&m_level.m_map[i].m_minX, 4);
			ar.Write(&m_level.m_map[i].m_maxX, 4);
			ar.Write(&m_level.m_map[i].m_minY, 4);
			ar.Write(&m_level.m_map[i].m_maxY, 4);
			for(int j= 0; j < m_level.m_map[i].m_nBlocsUse; ++j){
				ar.Write(&m_level.m_map[i].m_blocs[j].m_type, 4);
				ar.Write(&m_level.m_map[i].m_blocs[j].m_posX, 4);
				ar.Write(&m_level.m_map[i].m_blocs[j].m_posY, 4);
				ar.Write(&m_level.m_map[i].m_blocs[j].m_bWall, 4);
			}
		}
	}else{
		ar.Read(&buffer, 4);
		if(buffer != 0x05710571)
			AfxMessageBox("Invalid File");

		ar.Read(&m_level.m_name, 128);
		for(int i= 0; i < NB_MAPS; ++i){
			ar.Read(&m_level.m_map[i].m_nBlocsUse, 4);
			ar.Read(&m_level.m_map[i].m_minX, 4);
			ar.Read(&m_level.m_map[i].m_maxX, 4);
			ar.Read(&m_level.m_map[i].m_minY, 4);
			ar.Read(&m_level.m_map[i].m_maxY, 4);
			for(int j= 0; j < m_level.m_map[i].m_nBlocsUse; ++j){
				ar.Read(&m_level.m_map[i].m_blocs[j].m_type, 4);
				ar.Read(&m_level.m_map[i].m_blocs[j].m_posX, 4);
				ar.Read(&m_level.m_map[i].m_blocs[j].m_posY, 4);
				ar.Read(&m_level.m_map[i].m_blocs[j].m_bWall, 4);
			}
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerDoc diagnostics

#ifdef _DEBUG
void CPSMapMakerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPSMapMakerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerDoc commands
