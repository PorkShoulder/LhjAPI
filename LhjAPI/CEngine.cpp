#include "pch.h"
#include "CEngine.h"

CEngine::CEngine()
	: m_hInst(nullptr)
	, m_hWnd(nullptr) // �ʱ�ȭ ����Ʈ ����� �ʱⰪ�� ������ �������� ���ϴ� ������ �ʱ�ȭ��Ŵ.
	, m_Resolution{}
	, m_hDC(nullptr)
{
	// �����ڰ� ���ܳ��� �ǽõǴ� �ڵ�



}
CEngine::~CEngine()
{
	// DC ����
	ReleaseDC(m_hWnd, m_hDC);

	// Pen �� Brush ����
	for (UINT i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_Pen[i]);
	}

	for (UINT i = 0; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_Brush[i]);
	}
}

int CEngine::Init(HINSTANCE _hInst, POINT _Resolution) //�ʱ�ȭ ������ ���� ������ ȣ��� �ػ� ���� ����
{
	//�ʱ�ȭ �� �ǽõǴ� �ڵ�

	m_hInst = _hInst;
	m_Resolution = _Resolution;
	
	// HWND : �������� ID�� ���� �� �ִ� ��. �����쿡�� �����ϴ� �Լ��� ���ؼ� �����ؾߵ�. 
   // Ŀ�� ������Ʈ : (os �������� �����Ǵ� ��ü)  
	m_hWnd = CreateWindowW(L"Key", L"Isaac", WS_OVERLAPPEDWINDOW,  // ����� ������ ã�ƿͼ� �� ������ ������� �����츦 �����. 
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, m_hInst, nullptr);



	if (!m_hWnd)
		return E_FAIL;


	
	ShowWindow(m_hWnd, true);
	UpdateWindow(m_hWnd);
	
	// ������ ũ�� ����, ��ġ ����
	SetWindowPos(m_hWnd, nullptr, 10, 10, m_Resolution.x, m_Resolution.y, 0);

	//DC����
	//- �׸��� �ʿ���. ������-> ������ �Է� �̷��� �����Ȱ��� ��� DC�� �ڵ鰪���� ���� �̋��� ID�� ���� Ŀ�ο�����Ʈ��
	// ��,���� ���� �⺻���� ����������. 
	
	m_hDC = GetDC(m_hWnd);
	HPEN hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0)); // �� ��Ÿ��,�β� ����
	HPEN hPrevPen = (HPEN)(SelectObject(m_hDC, hRedPen));


	SelectObject(m_hDC, hPrevPen);
	DeleteObject(hRedPen);


	return S_OK;
}

void CEngine::Progress() //���� �ڵ� ���⼭ �ۼ��� �Ŵ��� ȣ�⿹��
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