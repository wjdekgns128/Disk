#ifndef _CMANAGER_H
#define _CMANAGER_H
#include "CMAIN.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
using namespace KG;

class cManager
{
public:
	vector<void*>			m_List;
	vector<int>				m_removeList;

public: 
	cManager();
	~cManager();
public:
	static cManager* GetInstance()  
	{  
		static cManager* Instance = NULL;  
		if( Instance == NULL )  
			Instance = new cManager();
		return Instance;
	}  
	void Update(float fElapsedTime);
	void Draw();
	void end();
};

#endif