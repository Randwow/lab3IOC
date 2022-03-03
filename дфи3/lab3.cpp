

#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <chrono>
#include <ctime>
#include <cmath>
#include <math.h>
#include <tchar.h>
#include <windows.h>
#include <winuser.h>
#include <iostream>
#define ID_TIMER 1
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
#define M_PI 3.14159
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
std::chrono::time_point<std::chrono::system_clock> m_StartTime;
std::chrono::time_point<std::chrono::system_clock> m_EndTime;
bool                                               m_bRunning = false;
void start()
{
    m_StartTime = std::chrono::system_clock::now();
    m_bRunning = true;
}

void stop()
{
    m_EndTime = std::chrono::system_clock::now();
    m_bRunning = false;
}

double elapsedMilliseconds()
{
    std::chrono::time_point<std::chrono::system_clock> endTime;

    if (m_bRunning)
    {
        endTime = std::chrono::system_clock::now();
    }
    else
    {
        endTime = m_EndTime;
    }

    return (double)std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count();
}

double elapsedSeconds()
{
    return elapsedMilliseconds() / 1000.0;
}

bool DrawLine(HDC hdc, int x0, int y0, int x, int y)
{
    POINT pt;
    MoveToEx(hdc, x0, y0, &pt);
    return LineTo(hdc, x, y);
}
char conv(int tic)
{
    switch (tic)
    {
    case 0: return '0';
    case 1: return '1';
    case 2: return '2';
    case 3: return '3';
    case 4: return '4';
    case 5: return '5';
    case 6: return '6';
    case 7: return '7';
    case 8: return '8';
    case 9: return '9';
    default:
        return '0';

    }
}
_TCHAR wall[50];
_TCHAR circle[50];
_TCHAR wall1[50];
_TCHAR circle1[50];
_TCHAR timespent[5];
bool need = true;
bool ch = true;
bool walls = 0;
bool clocks = 0;
bool ready = 0;
bool print = 0;
bool print1 = 0;
int step = 0;
int x = 0;
int y = 0;
int phase = 1;
int Steps = 0;
int i = 0;
int i1 = 0;
int j = 0;
int j2 = 0;
int t = 0;
int angle = 0;
/*  Make the class name into a global variable  */
TCHAR szClassName[] = _T("GDI_Lab");

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx(&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("GDI_Lab"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        CW_USEDEFAULT,                 /* The programs width */
        CW_USEDEFAULT,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );
    while (!SetTimer(hwnd, ID_TIMER, 1, NULL))
        if (IDCANCEL == MessageBox(hwnd, L"Too many clocks or timers", szClassName, MB_ICONEXCLAMATION | MB_RETRYCANCEL))
            return FALSE;

    /* Make the window visible on the screen */
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage(&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */


LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
        
        HDC hdc;
        PAINTSTRUCT ps;
        RECT rect;
        HBRUSH hBrush;
        // hBrush=CreateSolidBrush(RGB(0,0,255));
    case WM_CREATE:

        break;
    case WM_TIMER:
        if (!need) {
            need = true;
            ch = true;
        }
        if (need)
            if (ch) {
                start();
                ch = false;
            }
            else {
                stop();
                need = false;
                t = elapsedMilliseconds();
            }

        if (ready)
            if (walls)
                step++;
            else
                if (clocks)
                {
                    x = cos(angle * M_PI / 30) * 150;
                    y = sin(angle * M_PI / 30) * 150;
                    angle++;
                    if (angle == 60)
                        angle = 0;
                }
        InvalidateRect(hwnd, NULL, TRUE);
        return 0;
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_SPACE:
            if (walls)
            {
                Steps = step - 136;
                if (abs(Steps) < 10)
                    if (Steps >= 0)
                    {
                        wall[i] = conv(abs(Steps));
                        i++;
                    }
                    else
                    {
                        wall1[i1] = conv(abs(Steps));
                        i1++;
                    }
            }
            else
                if (clocks)
                {
                    Steps = angle - 45 - 1;//âîò ýòî õîäóëè
                    if (abs(Steps) < 10)
                        if (Steps >= 0)
                        {
                            circle[j] = conv(abs(Steps));
                            j++;
                        }
                        else
                        {
                            circle1[j2] = conv(abs(Steps));
                            j2++;
                        }
                }
            step = 0;
            ready = false;
            break;
        case 0x31:

            print = true;
            print1 = false;
            walls = true;
            clocks = false;
            break;
        case 0x32:
            angle = 45;
            print1 = true;
            print = false;
            clocks = true;
            walls = false;
            phase = 1;
            break;
        case 0x43:
            ready = true;
            break;
        case 0x33:
            ready = false;
            break;

        default:

            break;
        }
        break;


    case WM_LBUTTONDOWN:

        break;



    case WM_LBUTTONUP:

        break;

    case WM_KEYUP:
        switch (wParam)
        {

        case VK_F1:

            break;
        default:

            break;

        }
        break;
    case WM_PAINT:


        hdc = BeginPaint(hwnd, &ps);
        GetClientRect(hwnd, &rect);
        SetTextColor(hdc, RGB(0, 0, 255));
        SetBkMode(hdc, TRANSPARENT);
        hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        if (walls)
        {
            hBrush = CreateSolidBrush(RGB(0, 0, 0));
            SelectObject(hdc, hBrush);
            Rectangle(hdc, 780, 300, 800, 360);
            Rectangle(hdc, 780, 420, 800, 480);
            Rectangle(hdc, 100 + 5 * step, 360, 120 + 5 * step, 420);
        }
        else
            if (clocks)
            {
                hBrush = CreateSolidBrush(RGB(100, 100, 100));
                SelectObject(hdc, hBrush);
                Ellipse(hdc, 400, 200, 700, 500);
                hBrush = CreateSolidBrush(RGB(250, 0, 0));
                SelectObject(hdc, hBrush);
                DrawLine(hdc, 350, 350, 750, 350);
                DrawLine(hdc, 550, 150, 550, 550);
                TextOut(hdc, 545, 190, L"12", 2);
                hBrush = CreateSolidBrush(RGB(255, 0, 0));
                SelectObject(hdc, hBrush);
                DrawLine(hdc, 550, 350, x + 550, y + 350);

            }
            else
                if (!print && !print1)
                    TextOut(hdc, 100, 100, L"Viberite rejim 1 ili 2", 23);
        if (print)
        {
            timespent[0] = conv((t / 10000) % 10);
            timespent[1] = conv((t / 1000) % 10);
            timespent[2] = conv((t / 100) % 10);
            timespent[3] = conv((t / 10) % 10);
            timespent[4] = conv(t % 10);
            TextOut(hdc, 10, 10, timespent, 5);
            TextOut(hdc, 100, 100, wall, 50);
            TextOut(hdc, 100, 150, wall1, 50);

        }
        if (print1)
        {
            timespent[0] = conv((t / 10000) % 10);
            timespent[1] = conv((t / 1000) % 10);
            timespent[2] = conv((t / 100) % 10);
            timespent[3] = conv((t / 10) % 10);
            timespent[4] = conv(t % 10);
            TextOut(hdc, 10, 10, timespent, 5);

            TextOut(hdc, 100, 100, circle, 50);
            TextOut(hdc, 100, 150, circle1, 50);
        }

        EndPaint(hwnd, &ps);
        DeleteObject(hBrush);
        ReleaseDC(hwnd, hdc);

        break;

    case WM_DESTROY:

        PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}







