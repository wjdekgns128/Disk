#include "CMAIN.h"

IMPLEMENT_MAIN(CMAIN);

CMAIN::CMAIN() : KGEmotion(L"����", 300, 400)
{
	m_pMain					= this;
#if defined(NDEBUG)
	SetFullScreenBackBufferWidthAtModeChange(300);
	SetFullScreenBackBufferHeightAtModeChange(400);
	SetOverrideWidth(300);
	SetOverrideHeight(400);
	SetOverrideFullScreen(false);
	SetHandleAltEnter(false);
	SetHandleDefaultHotkeys(false);
	SetShowMsgBoxOnError(true);
	SetShowCursorWhenFullScreen(false);
#endif
}

CMAIN::~CMAIN()
{
}


void CMAIN::Create()
{
	//!< Entry(���̸�, �� class �̸�)
	Entry(L"game",new cGame);
	
}


void CMAIN::Init()
{
	Trans(L"game");
				//!< Trans(������ ������ ���̸�)
}