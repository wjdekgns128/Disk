#include "cDiscus.h"
#include "cManager.h"
#include "time.h"
cDiscus::cDiscus(KGSprite* sprite,KGAnimate* animate)
{
	m_pSprite				= sprite;
	m_pAnimate				= animate;
	m_pRank					= new cRank();
	m_bestscore				= m_pRank->Load();
	Reset();
}
cDiscus::~cDiscus()
{
	SAFE_DELETE(m_pRank);
	cManager* m_pManager = cManager::GetInstance();
	delete m_pManager;
}
void cDiscus::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{		
	if(m_end || m_endtime <= 0)
	{
		m_end				= true;
		return;
	}
	cManager* m_pManager = cManager::GetInstance();
	m_pManager->Update(fElapsedTime);
	m_createtime += fElapsedTime;
	m_Leveltime	 += fElapsedTime;
	m_endtime	 -= fElapsedTime;
	Makediscus();
	Levelcheck();

}
void cDiscus::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	for(int i=0;i<m_maxdiscus;i++)
	{
		if(s_Discus[i].m_state == 1)
		{
			m_pSprite->Render(L"1",KGRect(s_Discus[i].m_discus.x-m_Csize,s_Discus[i].m_discus.y-m_Csize,
				s_Discus[i].m_discus.x+m_Csize,s_Discus[i].m_discus.y+m_Csize),D3DXCOLOR(1,1,1,1));
		}
	}
	if(m_end)
	{
		if(m_fApl > 0.5)
			m_fApl -= 0.005;
		else if(m_fApl <= 0.5)
			m_fApl = 1;
		m_pSprite->Render(L"Gameover",D3DXVECTOR3(0,100,0),D3DXCOLOR(1,1,1,1));
		m_pSprite->Render(L"Mouse",D3DXVECTOR3(50,200,0),D3DXCOLOR(1,1,1,m_fApl));

	}
	cManager* m_pManager = cManager::GetInstance();
	m_pManager->Draw();


}
void cDiscus::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{

	m_mouse					= D3DXVECTOR3(xPos,yPos,0);
	int	m					= 0;
	if(bButtonDown)	
	{
		m = check();
		if(!m_end)
		{
			if(ColBetween(s_Discus[m].m_discus,m_Csize))
			{
				for(int j=0;j<MAX_P;j++)
				{
					m_pParticle[j]					= new cParticle(m_mouse);
				}
				s_Discus[m].m_state				= 0;
				m_endtime						= END_TIME;
				m_score++;
				m_pRank->Save(m_score);
				m_bestscore						= m_pRank->Load();
			}
			else
			{
				m_end = true;
				cManager* m_pManager = cManager::GetInstance();
				m_pManager->end();

			}
		}
		else
		{
			Reset();
		}

	}
}
void cDiscus::Reset()
{
	cGame* pGame		= (cGame*)cMain()->GetCurrent();
	pGame->m_time			= 0 ;
	m_mousecheck			= true;
	m_end					= false;
	m_mouse					= D3DXVECTOR3(0,0,0);
	m_maxdiscus				= 25;
	m_createtime			= 0.0;


	m_Leveltime				= 0.0;
	m_Level					= 7;

	m_time					= 0.35;
	m_Csize					= 60;
	m_fApl					= 1;
	m_score					= 0;
	m_endtime				= END_TIME;
	for(int i=0;i<MAX;i++)
	{
		s_Discus[i].m_state					= 0;
		s_Discus[i].m_discus				= D3DXVECTOR3(0,0,0);
	}
}
bool cDiscus::ColBetween(D3DXVECTOR3 vPos,double radius)
{

	return (pow(vPos.x - m_mouse.x,2)+
		pow(vPos.y - m_mouse.y,2)
		< pow(radius + 0,2));

}

void cDiscus::Makediscus()
{

	for(int i=0;i<m_maxdiscus;i++)
	{
		if(s_Discus[i].m_state == 0)
		{
			if(m_createtime > m_time)
			{
				s_Discus[i].m_state				= 1;
				s_Discus[i].m_discus			= D3DXVECTOR3(30+rand()%200,30+rand()%290,0);
				m_createtime					= 0;

			}
		}
	}
}
void cDiscus::Levelcheck()
{
	if(m_Csize  > 40 )
	{
		if(m_Leveltime >= m_Level)
		{
			if(m_maxdiscus > 1 )
			{
				m_maxdiscus				-= 1;
				m_Level					+= 1;
				m_Leveltime				= 0.0;
				m_time					+= 0.1;
			}
			else if(m_maxdiscus <= 1)
			{
				m_Csize -= 2;
			}
		}
	}
}
int	cDiscus::check()
{
	for(int i=m_maxdiscus-1;i >= 0 ;i--)
	{
		if(s_Discus[i].m_state == 0)
			continue;
		if(ColBetween(s_Discus[i].m_discus,m_Csize))
		{
			return i;
		}
	}
}