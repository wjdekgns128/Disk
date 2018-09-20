#ifndef _CRANK_H
#define _CRANK_H

#include "CMAIN.h"
#include "MyDefine.h"
class cRank
{
	int			bestscore;
public:
	cRank();
	void  Save(int score);
	int  Load();
};
#endif