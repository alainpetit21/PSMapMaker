#ifndef _PSLEVEL_H_
#define _PSLEVEL_H_

#define B_VIDE			0x01
#define B_WALL			0x02
#define B_TRAP			0x03
#define B_STAIR_UP		0x04
#define B_STAIR_DOWN	0x05
#define B_DOOR			0x06
#define B_LOCKED_DOOR	0x07
#define B_MLOCKED_DOOR	0x08

#define B_HAVE_TREASURE	0x10
#define B_HAVE_TRAP		0x20
#define B_HAVE_SECRET	0x40

#define NB_BLOCS	1024
#define NB_MAPS		128

#define BLOC_WALL			0
#define BLOC_VIDE			1
#define BLOC_EXIT			2
#define BLOC_STAIRS_UP		3
#define BLOC_STAIRS_DOWN	4
#define BLOC_DOOR			5
#define BLOC_LOCKED_DOOR	6
#define BLOC_MAGICAL_DOOR	7
#define BLOC_MAX_TYPES		8

#define DIR_RIGHT	1
#define DIR_DOWN	2
#define DIR_LEFT	4
#define DIR_UP		8

class CPSBloc
{
public:
	CPSBloc():m_bWall(0xF), m_type(BLOC_WALL), m_posX(~0), m_posY(~0){};
	int m_type;
	int m_posX;
	int m_posY;
	int m_bWall;
	int m_bDoorOn;
	int m_bLockedDoorOn;
	int m_bMagicalDoorOn;
	int m_bTrap;
	int m_bChest;
	int m_bTrappedChest;
	int m_nbGoldChest;
	int m_nbItemChest;
};

class CPSMap
{
public:
	CPSMap();
	CPSBloc*	GetAt(int p_x, int p_y);
	void		SetAt(int p_x, int p_y, int p_type);

	CPSBloc			m_blocs[NB_BLOCS];
	int				m_nBlocsUse;
	int				m_minX;
	int				m_maxX;
	int				m_minY;
	int				m_maxY;
	int				m_curX;
	int				m_curY;
	unsigned char	m_curAngle;
};

class CPSLevel  
{
public:
	CPSLevel();
	virtual ~CPSLevel();
	CPSMap* GetMap(){return &m_map[m_nCurMap];};
	void MoveNextMap();
	void MovePreviousMap();
	void MoveWalkingForward();
	void MoveWalkingBackward();

	char	m_name[128];
	int		m_nCurMap;
	CPSMap	m_map[NB_MAPS];
};

#endif // _PSLEVEL_H_
