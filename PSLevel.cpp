#include "stdafx.h"
#include "PSMapMaker.h"
#include "PSLevel.h"
#include "mathFP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CPSLevel::CPSLevel():
m_nCurMap(0)
{
	m_map->SetAt(0, 0, BLOC_EXIT);
}

CPSLevel::~CPSLevel()
{

}

void
CPSLevel::MoveNextMap()
{
int curAngle= m_map[m_nCurMap].m_curAngle;
int curX= m_map[m_nCurMap].m_curX, curY= m_map[m_nCurMap].m_curY;

	if(m_nCurMap == (NB_MAPS-1)){
		return;
	}

	++m_nCurMap;

	m_map[m_nCurMap].m_curAngle= curAngle;
	m_map[m_nCurMap].SetAt(curX, curY, BLOC_VIDE);
}

void
CPSLevel::MovePreviousMap()
{
int curAngle= m_map[m_nCurMap].m_curAngle;
int curX= m_map[m_nCurMap].m_curX, curY= m_map[m_nCurMap].m_curY;

	if(m_nCurMap == 0){
		return;
	}

	--m_nCurMap;

	m_map[m_nCurMap].m_curAngle= curAngle;
	m_map[m_nCurMap].SetAt(curX, curY, BLOC_VIDE);
}

void 
CPSLevel::MoveWalkingForward()
{
CPSBloc* pBloc= m_map[m_nCurMap].GetAt( m_map[m_nCurMap].m_curX, m_map[m_nCurMap].m_curY);

	switch(m_map[m_nCurMap].m_curAngle){
	case 0:		pBloc->m_bWall&= ~DIR_RIGHT;break;
	case 64:	pBloc->m_bWall&= ~DIR_DOWN;	break;
	case 128:	pBloc->m_bWall&= ~DIR_LEFT;	break;
	case 192:	pBloc->m_bWall&= ~DIR_UP;	break;
	}
	m_map[m_nCurMap].SetAt( m_map[m_nCurMap].m_curX + (Cos(m_map[m_nCurMap].m_curAngle)>>8),
							m_map[m_nCurMap].m_curY + (Sin(m_map[m_nCurMap].m_curAngle)>>8), 
							BLOC_VIDE);


	pBloc= m_map[m_nCurMap].GetAt( m_map[m_nCurMap].m_curX, m_map[m_nCurMap].m_curY);
	switch(m_map[m_nCurMap].m_curAngle){
	case 0:		pBloc->m_bWall&= ~DIR_LEFT;	break;
	case 64:	pBloc->m_bWall&= ~DIR_UP;	break;
	case 128:	pBloc->m_bWall&= ~DIR_RIGHT;break;
	case 192:	pBloc->m_bWall&= ~DIR_DOWN;	break;
	}
}

void 
CPSLevel::MoveWalkingBackward()
{
CPSBloc* pBloc= m_map[m_nCurMap].GetAt( m_map[m_nCurMap].m_curX, m_map[m_nCurMap].m_curY);

	switch(m_map[m_nCurMap].m_curAngle){
	case 0:		pBloc->m_bWall&= ~DIR_LEFT;	break;
	case 64:	pBloc->m_bWall&= ~DIR_UP;	break;
	case 128:	pBloc->m_bWall&= ~DIR_RIGHT;break;
	case 192:	pBloc->m_bWall&= ~DIR_DOWN;	break;
	}
	m_map[m_nCurMap].SetAt( m_map[m_nCurMap].m_curX - (Cos(m_map[m_nCurMap].m_curAngle)>>8),
							m_map[m_nCurMap].m_curY - (Sin(m_map[m_nCurMap].m_curAngle)>>8), 
							BLOC_VIDE);
	pBloc= m_map[m_nCurMap].GetAt( m_map[m_nCurMap].m_curX, m_map[m_nCurMap].m_curY);
	switch(m_map[m_nCurMap].m_curAngle){
	case 0:		pBloc->m_bWall&= ~DIR_RIGHT;break;
	case 64:	pBloc->m_bWall&= ~DIR_DOWN;	break;
	case 128:	pBloc->m_bWall&= ~DIR_LEFT;	break;
	case 192:	pBloc->m_bWall&= ~DIR_UP;	break;
	}
}

CPSMap::CPSMap():
m_nBlocsUse(0),
m_minX(1000),
m_maxX(-1000),
m_minY(1000),
m_maxY(-1000),
m_curAngle(192)
{
	memset(m_blocs, 0x0, sizeof(CPSBloc)*NB_BLOCS);
};

void
CPSMap::SetAt(int p_x, int p_y, int p_type)
{
int i;
	m_curX= p_x;
	m_curY= p_y;
	for(i= 0; i < m_nBlocsUse; ++i){	
		if((m_blocs[i].m_posX == p_x) &&
		(m_blocs[i].m_posY == p_y)){
			if(p_type > m_blocs[i].m_type)
				m_blocs[i].m_type= p_type;
			return;
		}		
	}
	m_blocs[m_nBlocsUse].m_posX= p_x;
	m_blocs[m_nBlocsUse].m_posY= p_y;
	if(p_type > m_blocs[m_nBlocsUse].m_type)	m_blocs[m_nBlocsUse].m_type= p_type;
	if(p_x < m_minX)							m_minX= p_x;
	if(p_x >=m_maxX)							m_maxX= p_x+1;
	if(p_y < m_minY)							m_minY= p_y;
	if(p_y >=m_maxY)							m_maxY= p_y+1;
	++m_nBlocsUse;
}


CPSBloc*
CPSMap::GetAt(int p_x, int p_y)
{
int i;
	for(i= 0; i < m_nBlocsUse; ++i){	
		if((m_blocs[i].m_posX == p_x) &&
		(m_blocs[i].m_posY == p_y))
			return m_blocs+i;
	}

	return 0;
}
