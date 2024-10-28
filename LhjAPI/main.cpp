
#include "framework.h"

#include "LhjAPI.h"
#include "CEngine.h"



// 전역 변수:
HINSTANCE g_hInst = nullptr;                         // 현재 인스턴스입니다. HINSTANCE(=HINSTANCE__*) : 매크로를 통한 구조체가 만들어지고 구조체 포인터를 타입 재정의 한것임.
HWND      g_hDlg = nullptr;




// 함수 전방선언
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

//SAL : 주석 언어 
int APIENTRY wWinMain( HINSTANCE hInstance,     // 프로세스 주소 ID 프로그램 시작주소
                       HINSTANCE hPrevInstance, // 안쓰이는 인자 (이전주소) 
                       LPWSTR    lpCmdLine,
                       int       nCmdShow)
{ // 윈도우 옵션설정
    WNDCLASSEXW wcex = {};                  //프로그램 시작시 나오는 창을 설정하는 것들.
    wcex.cbSize                 = sizeof(WNDCLASSEX);
    wcex.style                  = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc            = &WndProc;
    wcex.cbClsExtra             = 0;
    wcex.cbWndExtra             = 0;
    wcex.hInstance              = hInstance;
    wcex.hIcon                  = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LHJAPI));
    wcex.hCursor                = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground          = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName           = MAKEINTRESOURCEW(IDC_LHJAPI);
    wcex.lpszClassName          = L"Key";
    wcex.hIconSm                = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    
    RegisterClassExW(&wcex); // 위에 설정을 다 했으면 레지스터로 등록을 함. 

    g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.


    // HWND : 윈도우의 ID를 받을 수 있는 것. 윈도우에서 제공하는 함수를 통해서 조작해야됨. 
    // 커널 오브젝트 : (os 차원에서 관리되는 객체)  
    HWND hWnd = CreateWindowW(L"Key" , L"Isaac", WS_OVERLAPPEDWINDOW,  // 등록한 설정을 찾아와서 그 정보를 기반으로 윈도우를 만든다. 
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }
    
    SetWindowPos(hWnd, nullptr, 10, 10, 1280, 768, 0);
    ShowWindow(hWnd, nCmdShow); 
    UpdateWindow(hWnd);
   
    // 단축키 테이블
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LHJAPI));

    //메세지 변수 선언 
    MSG msg = {};


    // 기본 메시지 루프입니다: 선언된 메세지 받아옴 

    while (true)
    {
        // 메세지큐에 메세지가 있다.
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                break;

            // 메세지 처리
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        // 메세지큐에 메세지가 없다.
        else
        {
            // 게임 실행, 1 프레임
           CEngine::GetInst()->Progress();
        }
    }

    return (int)msg.wParam;
}



//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(g_hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
