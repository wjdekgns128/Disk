#include "cManager.h"
#include "cParticle.h"


cManager::cManager()
{

}


cManager::~cManager()
{
	if(m_List.empty() == false)
		for(int i = 0; i < m_List.size(); i++)
			delete ((cParticle*)m_List[i]);
	m_List.clear();
	m_removeList.clear();
}
void cManager::end()
{
	if(m_List.empty() == false)
		for(int i = 0; i < m_List.size(); i++)
			delete ((cParticle*)m_List[i]);
	m_List.clear();
	m_removeList.clear();
}


void cManager::Update(float fElapsedTime)
{
	if(m_List.empty() == false) {
		for(int i = 0; i < m_List.size(); i++) {
			((cParticle*)m_List[i])->Update(fElapsedTime);
			if(((cParticle*)m_List[i])->m_state == 0) {
				m_removeList.push_back(i);
			}
		}
		if(m_removeList.empty() == false) {
			for(int i = m_removeList.size()-1; i >= 0; i--) {
				delete ((cParticle*)m_List[m_removeList[i]]);
				m_List.erase(m_List.begin() + m_removeList[i]);
			}
			m_removeList.clear();
		}
	}
}


void cManager::Draw()
{
	cGame* pGame			= (cGame*)cMain()->GetCurrent();
	if(m_List.empty() == false) {
		for(int i = 0; i < m_List.size(); i++) {
			((cParticle*)m_List[i])->Draw(pGame->m_pSprite);
		}
	}
}

