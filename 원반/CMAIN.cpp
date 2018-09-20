#include "CMAIN.h"

IMPLEMENT_MAIN(CMAIN);

CMAIN::CMAIN() : KGEmotion(L"원반", 300, 400)
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
	//!< Entry(씬이름, 씬 class 이름)
	Entry(L"game",new cGame);
	
}


void CMAIN::Init()
{
	Trans(L"game");
				//!< Trans(위에서 선언한 씬이름)
}