#ifndef _CDISCUS_H
#define _CDISCUS_H

#include "CMAIN.h"
#include "cParticle.h"

#include "MyDefine.h"
#include "cRank.h"
using namespace KG;
class cRank;
class cParticle;
class cDiscus : public KGScene
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	cRank*					m_pRank;
	cParticle*				m_pParticle[MAX_P];
	//마우스
	D3DXVECTOR3				m_mouse; // 마우스좌표
	bool					m_mousecheck;
	//
	//게임 관련 스코어,시간 등등
	int						m_score;
	int						m_bestscore;
	float					m_endtime;
	float					m_Leveltime;
	int						m_Level;
	bool					m_end;

	//
	//원반
	float					m_createtime;
	float					m_time;		
	int						m_maxdiscus;
	int						m_Csize;
	float					m_fApl;
	typedef struct s_Discus
	{
		D3DXVECTOR3				m_discus;
		int						m_state;
	}s_discus;
	s_discus				s_Discus[MAX];
	//
public:
	cDiscus(KGSprite* sprite,KGAnimate* animate);
	~cDiscus();
public:
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
public:
	void Reset();
	bool ColBetween(D3DXVECTOR3 vPos,double radius);
	void Makediscus();
	void Levelcheck();
	int	 check();

};
#endif