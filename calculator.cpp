#include <Windows.h>
#include <stdio.h>
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
char szClassname[] = "TextEntry";

// Declare wincl outside of WinMain so it can be accessed from WindowProcedure
WNDCLASSEX wincl;

using namespace std;
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow){

    HWND hwnd;
    MSG messages;
    HBRUSH hBrush;
    // Initialize the wincl structure
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "Test";
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS; 
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL; 
    wincl.cbClsExtra = 0;      
    wincl.cbWndExtra = 0;      
    wincl.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(250,120,30));
   
    if (!RegisterClassEx(&wincl))
        return 0;

    // The class is registered, let's create the program's window
    hwnd = CreateWindowEx(
        0,                           // Extended possibilites for variation
        "Test",                      // Class name
        "MyCalculator",              // Window title
        WS_SYSMENU, // Window style
        CW_USEDEFAULT,               // Windows decides the position
        CW_USEDEFAULT,               // where the window ends up on the screen
        250,                         // The programs width
        200,                         // and height in pixels
        HWND_DESKTOP,                // The window is a child-window to desktop
        NULL,                        // No menu
        hThisInstance,               // Program Instance handler
        NULL                         // No Window Creation data
    );

    // Make the window visible on the screen
    ShowWindow(hwnd, nCmdShow);

    // Run the message loop. It will run until GetMessage() returns 0
    while (GetMessage(&messages, NULL, 0, 0))
    {
        // Translate virtual-key messages into wchar_tacter messages
        TranslateMessage(&messages);
        // Send message to WindowProcedure
        DispatchMessage(&messages);
    }

    // The program return-value is 0 - The value that PostQuitMessage() gave
    return messages.wParam;
}

// This function is called by the Windows function DispatchMessage()
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND textfield, TextBox1, TextBox2;  // หัวข้อหลัก ช่องเติม  ช่องเติม
    static HWND bPlus, bMinus, bMultiply, bDiv; // ปุ่ม 4 ปุ่ม
    char outMessage[100];
    char num1[256], num2[256];
    double val1, val2, result;
    switch (message) // handle the messages
    {

    case WM_CREATE:
        textfield = CreateWindow("STATIC", "Please input two numbers",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 20, 20, 200, 20, hwnd, NULL, NULL, NULL);
        TextBox1 = CreateWindow("EDIT", "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                40, 50, 150, 25, hwnd, NULL, NULL, NULL);
        TextBox2 = CreateWindow("EDIT", "",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                40, 80, 150, 25, hwnd, NULL, NULL, NULL);
        bPlus = CreateWindow("BUTTON", "+",
                             WS_VISIBLE | WS_CHILD | WS_BORDER,
                             60, 120, 25, 25, hwnd, (HMENU)1, NULL, NULL);
        bMinus = CreateWindow("BUTTON", "-",
                              WS_VISIBLE | WS_CHILD | WS_BORDER,
                              90, 120, 25, 25, hwnd, (HMENU)2, NULL, NULL);
        bMultiply = CreateWindow("BUTTON", "*",
                                 WS_VISIBLE | WS_CHILD | WS_BORDER,
                                 120, 120, 25, 25, hwnd, (HMENU)3, NULL, NULL);
        bDiv = CreateWindow("BUTTON", "/",
                            WS_VISIBLE | WS_CHILD | WS_BORDER,
                            150, 120, 25, 25, hwnd, (HMENU)4, NULL, NULL);

        break;
    case WM_COMMAND:

        GetWindowText(TextBox1, num1, 20); // get text from the first text box
        GetWindowText(TextBox2, num2, 20); // get text from the second text box
        val1 = atof(num1);
        val2 = atof(num2);
        switch (LOWORD(wParam)){

        case 1:
            result = val1 + val2;
            sprintf(outMessage, "%f", result);
			::MessageBox(hwnd, outMessage, "Result", MB_OK);
        
        break;
        case 2:
            result = val1 - val2;
            sprintf(outMessage, "%f", result);
			::MessageBox(hwnd, outMessage, "Result", MB_OK);
        break;
        case 3:
            result = val1 * val2;
            sprintf(outMessage, "%f", result);
			::MessageBox(hwnd, outMessage, "Result", MB_OK);
        break;
        case 4:
            result = val1 / val2;
            sprintf(outMessage, "%f", result);
			::MessageBox(hwnd, outMessage, "Result", MB_OK);
        break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0); // Send a WM_QUIT message to the message queue
        break;
    default: // for messages that we don't deal with
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    // If something was not handled here, let it go
    return 0;
}