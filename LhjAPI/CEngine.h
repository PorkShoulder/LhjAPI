#pragma once

#include "define.h"


//�ֻ��� ������
class CEngine
{

	SINGLE(CEngine);
private:
	HWND	m_hWnd;


public:
	int Init();
	void Progress();

};

