#ifndef _CPRTICLE_H
#define _CPRTICLE_H

#include "CMAIN.h"
#include "MyDefine.h"

using namespace KG;
class cParticle
{
public:
	D3DXVECTOR3				m_point;
	D3DXVECTOR3				m_move;
	
	int						m_state;
	int						m_type;
	float					m_time;
	float					m_fApl;
	int						m_size;
public:
	cParticle(D3DXVECTOR3	point);
	~cParticle();
public:

	void Update(float fElapsedTime);
	void Draw(KGSprite* sprite);
	void paritcleReset();
public:
};
#endif