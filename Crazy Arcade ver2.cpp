// Crazy Arcade.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Crazy Arcade ver2.h"
#include "Define.h"
#include "GameCore.h"
#define MAX_LOADSTRING 100

// 전역 변수:
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
DWORD dwTime = GetTickCount();					// 
HINSTANCE hInst;                                // 현재 인스턴스입니다.
HWND g_hWnd;
RECT crt;                                       // Client 너비, 높이를 구하기 위한
POINT ptMouse = { 0,0 };
Vector2 myXY = { 100.0, 100.0 }; // 캐릭터의 키보드에 따른 좌표
DWORD currentTime = GetTickCount64();
DWORD prevTime = GetTickCount64();
RECT rcInter; // 충돌처리용 RECT
float dDT = 0.0f;
float fFrameDelay = 0.0f;
float fFrameDelay2 = 0.0f;
float fPlayerX, fPlayerY = 0; // 캐릭터 좌표 저장
int nPlayerWay = 0; // 캐릭터 방향
int nPlayerWayBan = 0; // 캐릭터 방향락
int nBanCount = 0; // 락 카운트
int nBomb = 0; // 물풍선 설치 여부
bool bMove = false; // 이동 제한




// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// wWinMain은 __stdcall 방식으로 실행된다.
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, // 객체를 실제로 만들어 내는것을 Instance, HINSTANCE
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CRAZYARCADEVER2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CRAZYARCADEVER2));
    MSG msg; // 메시지 구조체 변수 선언
    GameCore GameCore;
    GameCore.Initialize();

    // 기본 메시지 루프입니다:

    /*
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    */

    //수정된 메시지 루프입니다:
    // 수정한 이유는 무한 루프를 타고
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // 메시지 루프 PeekMessage : 스레드 메시지 큐에 저장된 메시지들을 가져온다.
        {
            if (msg.message == WM_QUIT) // 종료
            {
                break;
            }


            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg); // 키보드 이벤트를 적절하게 바꿔주는 역할
                DispatchMessage(&msg); // 메시지를 처리할 프로시저(WndProc)에 메시지를 넘겨주는 역할
            }
        }
        else
        {
            if (dwTime + 10 < GetTickCount64())
            {
                dwTime = GetTickCount64();
                GameCore.Progress();
                GameCore.Render();

                dDT = currentTime / 1000.0f;
                currentTime = GetTickCount64() - prevTime;
                prevTime = GetTickCount64();
            }
        }
    }


    return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance) // 윈도우 클래스를 등록
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW; // 가로, 세로
    wcex.lpfnWndProc = WndProc; // 콜백 함수 포인터 지정, WndProc() 함수는 메시지 처리 콜백 함수, 큐(Queue) => 선입선출, 메시지에 따른 사용자 정의 기능을 만들 수 있어야 한다.
    //WndProc를 함수 포인터로 준 이유 ? : 포인터를 이용해 주소에 접근하여서 값을 변경할 수 있기 때문이다.
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CRAZYARCADEVER2)); // 예를 들어 바탕화면에 있을 때 그 프로그램을 표현하는 그림
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); // 실행 했을 때 프로그램 안에서 마우스 모양 현재는 ARROW
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 배경화면
    wcex.lpszMenuName = NULL; // 메뉴 ( 파일, 도움말 ) MAKEINTRESOURCEW(IDC_CRAZYARCADE), 이거 같은 경우에는 안쓸 거니까 = NULL;
    wcex.lpszClassName = szWindowClass; // 레지스터에 등록할 클래스 이름
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL)); // 왼쪽 상단 작은 그림

    return RegisterClassExW(&wcex); // 레지스터에 등록
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    g_hWnd = hWnd;

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
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
    case WM_MOUSEMOVE:
    {
        ptMouse.x = LOWORD(lParam);
        ptMouse.y = HIWORD(lParam);
        break;
    }
    case WM_KEYUP:
    {
        nBanCount = 0;
        bMove = false;
        break;
    }
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            nPlayerWay = VK_LEFT; // 캐릭터 왼쪽으로
            bMove = true;
            nBanCount = 0;
            break;
        case VK_UP:
            nPlayerWay = VK_UP; // 캐릭터 왼쪽으로
            bMove = true;
            nBanCount = 0;
            break;
        case VK_RIGHT:
            nPlayerWay = VK_RIGHT; // 캐릭터 왼쪽으로
            bMove = true;
            nBanCount = 0;
            break;
        case VK_DOWN:
            nPlayerWay = VK_DOWN; // 캐릭터 왼쪽으로
            bMove = true;
            nBanCount = 0;
            break;
        case VK_SPACE:
            nBomb = VK_SPACE; // 물풍선 설치를 위함
            break;
        default:
            nPlayerWay = 0;
        }
        break;
    }
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