#pragma once

#include "define.h"


//최상위 관리자
class CEngine
{

	SINGLE(CEngine);
private:
	HWND	m_hWnd;


public:
	int Init();
	void Progress();

};

