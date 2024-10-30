#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hInst(nullptr)
	, m_hWnd(nullptr) // 초기화 리스트 멤버의 초기값을 생성자 생성전에 원하는 값으로 초기화시킴.
	, m_Resolution{}
	, m_hDC(nullptr)
{
	// 생성자가 생겨날시 실시되는 코드



}
CEngine::~CEngine()
{
	// DC 해제
	ReleaseDC(m_hWnd, m_hDC);

	// Pen 과 Brush 해제
	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_Brush[i]);
	}
}

int CEngine::Init(HINSTANCE _hInst, POINT _Resolution) //초기화 시작히 메인 윈도우 호출및 해상도 정보 받음
{
	//초기화 시 실시되는 코드

	m_hInst = _hInst;
	m_Resolution = _Resolution;
	
	// HWND : 윈도우의 ID를 받을 수 있는 것. 윈도우에서 제공하는 함수를 통해서 조작해야됨. 
   // 커널 오브젝트 : (os 차원에서 관리되는 객체)  
	m_hWnd = CreateWindowW(L"Key", L"Isaac", WS_OVERLAPPEDWINDOW,  // 등록한 설정을 찾아와서 그 정보를 기반으로 윈도우를 만든다. 
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);



	if (!m_hWnd)
		return E_FAIL;


	
	ShowWindow(m_hWnd, true);
	UpdateWindow(m_hWnd);
	
	// 윈도우 크기 설정, 위치 설정
	SetWindowPos(m_hWnd, nullptr, 10, 10, m_Resolution.x, m_Resolution.y, 0);

	//DC생성
	//- 그릴곳 필요함. 목적지-> 윈도우 입력 이렇게 생성된것을 멤버 DC의 핸들값으로 받음 이떄는 ID로 받음 커널오브젝트라서
	// 흰,검정 펜을 기본으로 가져고있음. 
	
	m_hDC = GetDC(m_hWnd);
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // 펜 스타일,두께 색상
	HPEN hPrevPen = (HPEN)(SelectObject(m_hDC, hRedPen));


	SelectObject(m_hDC, hPrevPen);
	DeleteObject(hRedPen);


	return S_OK;
}

void CEngine::Progress() //게임 코드 여기서 작성됨 매니저 호출예정
{

}

void CEngine::CreateGDIObject()
{
	// Pen
	m_Pen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_Pen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_Pen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// Brush
	m_Brush[(UINT)BRUSH_TYPE::RED] = CreateSolidBrush(RGB(255, 0, 0));
	m_Brush[(UINT)BRUSH_TYPE::GREEN] = CreateSolidBrush(RGB(0, 255, 0));
	m_Brush[(UINT)BRUSH_TYPE::BLUE] = CreateSolidBrush(RGB(0, 0, 255));
}