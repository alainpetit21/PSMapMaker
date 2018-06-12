// PSMapMakerView.cpp : implementation of the CPSMapMakerView class
//

#include "stdafx.h"
#include "PSMapMaker.h"

#include "PSMapMakerDoc.h"
#include "PSMapMakerView.h"

#include "mathFP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPSMapMakerView* CPSMapMakerView::cela;

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView

IMPLEMENT_DYNCREATE(CPSMapMakerView, CView)

BEGIN_MESSAGE_MAP(CPSMapMakerView, CView)
	//{{AFX_MSG_MAP(CPSMapMakerView)
	ON_WM_KEYUP()
	ON_COMMAND(ID_BUTTON_DOOR, OnButtonDoor)
	ON_COMMAND(ID_BUTTON_LOCKED_DOOR, OnButtonLockedDoor)
	ON_COMMAND(ID_BUTTON_MAGICAL_DOOR, OnButtonMagicalDoor)
	ON_COMMAND(ID_BUTTON_STAIR_DOWN, OnButtonStairDown)
	ON_COMMAND(ID_BUTTON_STAIR_UP, OnButtonStairUp)
	ON_COMMAND(ID_BUTTON_NEXTMAP, OnButtonNextmap)
	ON_COMMAND(ID_BUTTON_PREVMAP, OnButtonPrevmap)
	ON_COMMAND(ID_BUTTON_EXPLICIT, OnButtonExplicit)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView construction/destruction

CPSMapMakerView::CPSMapMakerView()
{
	cela= this;
}

CPSMapMakerView::~CPSMapMakerView()
{
}

BOOL CPSMapMakerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView drawing

void CPSMapMakerView::OnDraw(CDC* pDC)
{
	CPSMapMakerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView printing

BOOL CPSMapMakerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPSMapMakerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPSMapMakerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView diagnostics

#ifdef _DEBUG
void CPSMapMakerView::AssertValid() const
{
	CView::AssertValid();
}

void CPSMapMakerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPSMapMakerDoc* CPSMapMakerView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPSMapMakerDoc)));
	return (CPSMapMakerDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPSMapMakerView message handlers

void CPSMapMakerView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	m_renderer.m_frameHWnd= GetSafeHwnd();
	m_renderer.Init(640, 480);

}

long palette[]={0x00000000, 0x00FFFFFF, 0x00FF0000, 0x0000FFFF, 0x000000FF, 0x00FFFF00, 0x0000FF00, 0x00FF00FF};

void CPSMapMakerView::OnIdle()
{
int i, mapI;
int j, mapJ;

	m_renderer.FillBitmap(m_renderer.m_pBB, 0);

	for(i= 0, mapI= GetDocument()->m_level.GetMap()->m_curX - (320/8); 
	(i < (640/8)); 
	++i, ++mapI){
		for(j= 0, mapJ= GetDocument()->m_level.GetMap()->m_curY - (240/8); 
		(j < (480/8)); 
		++j, ++mapJ){
			CPSBloc* pBloc;

			if((pBloc= GetDocument()->m_level.GetMap()->GetAt(mapI, mapJ))){
				m_renderer.FillRect_i(m_renderer.m_pBB, (i*8)+((pBloc->m_bWall&DIR_LEFT)?1:0), (j*8)+((pBloc->m_bWall&DIR_UP)?1:0), ((i+1)*8)-((pBloc->m_bWall&DIR_RIGHT)?1:0), ((j+1)*8)-((pBloc->m_bWall&DIR_DOWN)?1:0), palette[pBloc->m_type]);
				if((mapI == GetDocument()->m_level.GetMap()->m_curX) &&
				(mapJ == GetDocument()->m_level.GetMap()->m_curY)){
					m_renderer.FillRect_i(m_renderer.m_pBB, (i*8)+2, (j*8)+2, ((i+1)*8)-2, ((j+1)*8)-2, 0x00FF0000);
				}
			}
		}
	}
	unsigned long* ptPixel= (unsigned long*)m_renderer.LockBB();
	m_renderer.DrawLine_locked(ptPixel, 
							   324+(-8*(Sin(GetDocument()->m_level.GetMap()->m_curAngle)>>8)),
							   244+(8*(Cos(GetDocument()->m_level.GetMap()->m_curAngle)>>8)), 
							   324+(32*(Cos(GetDocument()->m_level.GetMap()->m_curAngle)>>8)),
							   244+(32*(Sin(GetDocument()->m_level.GetMap()->m_curAngle)>>8)), 1, 0x00FF0000);
	m_renderer.DrawLine_locked(ptPixel, 
							   324+(8*(Sin(GetDocument()->m_level.GetMap()->m_curAngle)>>8)),
							   244+(-8*(Cos(GetDocument()->m_level.GetMap()->m_curAngle)>>8)), 
							   324+(32*(Cos(GetDocument()->m_level.GetMap()->m_curAngle)>>8)),
							   244+(32*(Sin(GetDocument()->m_level.GetMap()->m_curAngle)>>8)), 1, 0x00FF0000);
	m_renderer.UnLockBB((unsigned short*)ptPixel);
	m_renderer.EndScene(0);


}

void CPSMapMakerView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	switch(nChar){
	case 39:	//Right
		GetDocument()->m_level.GetMap()->m_curAngle+= 64;
		break;
	case 37:	//Left
		GetDocument()->m_level.GetMap()->m_curAngle-= 64;	
		break;
	case 40:	//Down
		GetDocument()->m_level.MoveWalkingBackward();
		break;
	case 38:	//Up
		GetDocument()->m_level.MoveWalkingForward();
		break;
	default:break;
	}
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CPSMapMakerView::OnButtonDoor() 
{
	GetDocument()->m_level.GetMap()->SetAt( GetDocument()->m_level.GetMap()->m_curX,
											GetDocument()->m_level.GetMap()->m_curY, 
											BLOC_DOOR);
}

void CPSMapMakerView::OnButtonLockedDoor() 
{
	GetDocument()->m_level.GetMap()->SetAt( GetDocument()->m_level.GetMap()->m_curX,
											GetDocument()->m_level.GetMap()->m_curY, 
											BLOC_LOCKED_DOOR);
}

void CPSMapMakerView::OnButtonMagicalDoor() 
{
	GetDocument()->m_level.GetMap()->SetAt( GetDocument()->m_level.GetMap()->m_curX,
											GetDocument()->m_level.GetMap()->m_curY, 
											BLOC_MAGICAL_DOOR);
}

void CPSMapMakerView::OnButtonStairDown() 
{
	GetDocument()->m_level.GetMap()->SetAt( GetDocument()->m_level.GetMap()->m_curX,
											GetDocument()->m_level.GetMap()->m_curY, 
											BLOC_STAIRS_DOWN);
}

void CPSMapMakerView::OnButtonStairUp() 
{
	GetDocument()->m_level.GetMap()->SetAt( GetDocument()->m_level.GetMap()->m_curX,
											GetDocument()->m_level.GetMap()->m_curY, 
											BLOC_STAIRS_UP);
}

void CPSMapMakerView::OnButtonExplicit() 
{
	CPSBloc* pBloc;

	if((pBloc= GetDocument()->m_level.GetMap()->GetAt(GetDocument()->m_level.GetMap()->m_curX, GetDocument()->m_level.GetMap()->m_curY))){
		if((++pBloc->m_type) >= BLOC_MAX_TYPES)
			pBloc->m_type= 0;
	}
}

void CPSMapMakerView::OnButtonNextmap() 
{
	GetDocument()->m_level.MoveNextMap();
}

void CPSMapMakerView::OnButtonPrevmap() 
{
	GetDocument()->m_level.MovePreviousMap();
}


void CPSMapMakerView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonUp(nFlags, point);
}
