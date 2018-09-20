#include "cRank.h"
cRank::cRank()
{
		bestscore = 0;
}
void cRank::Save(int score)
{
	if(score > bestscore)
		bestscore  = score;
	FILE* fp = _wfopen(L"res/rank.score",L"wt");
	fwprintf(fp,L"%d",bestscore);
	fclose(fp);
}
int cRank::Load()
{
	FILE* fp = _wfopen(L"res/rank.score",L"rt");

	if(fp != NULL)
	{
		fwscanf(fp,L"%d",&bestscore);
		fclose(fp);
		return bestscore;
	}
	else
		return 0;
}