#include "cParticle.h"
#include "cManager.h"
cParticle::cParticle(D3DXVECTOR3	point)
{
	paritcleReset();

	m_type					= rand()%2;
	m_state					=	1;
	m_time					=   0;
	m_point					=   point;
	m_fApl					= 1;
	m_size					= 10 + rand()%10;
	if(m_type == 0)
		m_move.x				= 1 * ((1+rand()%10) * 0.15);
	else
		m_move.x				= (1 * ((1+rand()%10) * 0.15) * -1);
	m_move.y				= 1 * ((1+rand()%10) * 0.4);
}
void cParticle::paritcleReset()
{
	cManager* pManager = cManager::GetInstance();
	pManager->m_List.push_back(this);
}

cParticle::~cParticle()
{

}

void cParticle::Update(float fElapsedTime)
{
	m_time +=fElapsedTime;
	if(m_state == 1)
	{
		m_point.y += m_move.y;
		m_point.x += m_move.x;
		m_fApl	  -= 0.015;
		if(m_fApl < 0.0 )
		{
			m_state = 0;
		}
	}
}
void cParticle::Draw(KGSprite* sprite)
{
	KGRect m_rect			= KGRect(m_point.x - m_size,m_point.y - m_size,m_point.x + m_size,m_point.y + m_size);
	if(m_state == 1)
	{
		if(m_type == 0)
			sprite->Render(L"2-1",m_rect,D3DXCOLOR(1,1,1,m_fApl));
		else if(m_type == 1)
			sprite->Render(L"2",m_rect,D3DXCOLOR(1,1,1,m_fApl));

	}	
}
