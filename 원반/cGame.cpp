#include "cGame.h"
#include "time.h"

cGame::cGame()
{
	m_pdiscus				= NULL;
	m_pSprite				= NULL;
	m_pAnimate				= NULL;
	m_pDialog				= NULL;
	m_stop					= true;
	m_time					= 0.0;
	m_check					= 0;
	m_checkapl				= 1;
}


cGame::~cGame()
{
	SAFE_DELETE(m_pdiscus);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pDialog);
}
void cGame::OnDestroyDevice(void* pUserContext)
{
	SAFE_DELETE(m_pdiscus);
	SAFE_DELETE(m_pSprite);
	SAFE_DELETE(m_pAnimate);
	SAFE_DELETE(m_pDialog);

}
HRESULT cGame::OnCreateDevice(IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext)
{
	if(m_pSprite == NULL)
	{
		m_pSprite			= new KGSprite(pd3dDevice);
		m_pSprite->Entry(L"res/Te/example.Te");
		m_pSprite->Entry(L"res/Te/Dialog_number1.Te");

	}
	if(m_pAnimate == NULL)
	{
		m_pAnimate			= new KGAnimate(m_pSprite);
	}
	if(m_pdiscus == NULL)
	{
		m_pdiscus			= new cDiscus(m_pSprite,m_pAnimate);

	}
	if(m_pDialog == NULL)
	{
		m_pDialog			= new KGDialog(m_pSprite,NULL,this);
		m_pDialog->AddNumber(ONE,L"Dnum1_",D3DXVECTOR3(120,100,0));
		m_pDialog->AddNumber(TWO,L"num_",D3DXVECTOR3(0,375,0),-3);
		m_pDialog->AddNumber(THREE,L"num_",D3DXVECTOR3(260,375,0),-3,1);
	}
	return S_OK;
}
void cGame::OnFrameMove(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	m_pDialog->GetNumber(2)->SetNumber(m_pdiscus->m_bestscore);
	if(m_stop)
		return;
	m_time	+=fElapsedTime;
	m_pDialog->GetNumber(0)->SetNumber(m_time);
	m_pDialog->GetNumber(1)->SetNumber(m_pdiscus->m_score);
	if(m_time > 3)
	{
		SAFE_ONFRAMEMOVE(m_pdiscus);
	}
	if(m_check == 1)
	{
		m_checkapl -= 0.1;
		if(m_checkapl < 0)
		{
			m_checkapl = 1;
			m_check    = 0;
		}
	}
}
void cGame::OnFrameRender(IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext)
{
	HRESULT					hr;

	V(pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB(0, 0, 0, 0), 1.0f, 0));

	if(SUCCEEDED(pd3dDevice->BeginScene()))
	{
		m_pSprite->Render(L"BGBG",D3DXVECTOR3(0,0,0),D3DXCOLOR(1,1,1,1));
	
		if(m_stop)
		{
			m_pDialog->GetNumber(ONE)->SetVisible(false);
			m_pSprite->Render(L"Mouse",D3DXVECTOR3(50,200,0),D3DXCOLOR(1,1,1,1));
		}
		SAFE_ONFRAMERENDER(m_pDialog);
		if(m_time <= 3)
		{
			m_pDialog->GetNumber(ONE)->SetVisible(true);
		}
		else
		{
			SetCursor(NULL);
			SAFE_ONFRAMERENDER(m_pdiscus);
			m_pDialog->GetNumber(ONE)->SetVisible(false);
			if(m_check == 1)
				m_pSprite->Render(L"check",m_point,D3DXCOLOR(1,1,1,m_checkapl));
		}
		m_pSprite->Render(L"bar",KGRect(80.f,370.f,75 + (m_pdiscus->m_endtime * 30),405.f),D3DXCOLOR(1,1,1,1));
	
		V(pd3dDevice->EndScene());
	}
}
void cGame::OnMouse(bool bButtonDown, bool bLeftButtonDown, bool bRightButtonDown, bool bMiddleButtonDown, bool bSideButton1Down, bool bSideButton2Down, int nMouseWheelDelta, int xPos, int yPos, void* pUserContext)
{
	m_point.x				= xPos;
	m_point.y				= yPos;
	if(m_time > 3)
		SAFE_ONMOUSE(m_pdiscus);


	if(bButtonDown)
	{
		m_check	= 1;
		if(m_stop)
			m_stop				=  false;
	}
}
void cGame::OnKeyboard(UINT nChar,bool bKeyDown,bool bAltDown,void *pUserContext)
{
	if(!bKeyDown) return;
	switch(nChar)
	{
	case VK_ESCAPE:
		cMain()->CloseWindow();
		break;
	}
}