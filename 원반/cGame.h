#ifndef _CGAME_H
#define _CGAME_H

#include "CMAIN.h"
#include "cDiscus.h"
#include "MyEnum.h"
using namespace KG;
class cDiscus;
class cGame : public KGScene, public KGResponseDialog
{
public:
	KGSprite*				m_pSprite;
	KGAnimate*				m_pAnimate;
	KGDialog*				m_pDialog;
	cDiscus*				m_pdiscus;

	float					m_time;
	bool					m_stop;


	D3DXVECTOR3				m_point;
	int						m_check;
	float					m_checkapl;
public:
	cGame();
	~cGame();
public:
	HRESULT CALLBACK		OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext);
	void CALLBACK			OnDestroyDevice(void* pUserContext);
	void CALLBACK			OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext);
	void CALLBACK			OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext);
	void CALLBACK			OnKeyboard(UINT nChar,bool bKeyDown,bool bAltDown,void *pUserContext);
public:
};
#endif