#include "framework.h"
#include "pr24.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
double scaling_coeff = 0.1;  // Coordinates were so big, I had to decrease them, otherwise they were off the monitor's resolution

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PR24, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PR24));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

///////////// MY CLASS AND CODE

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

void printMemoryLeaks()
{
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}

class Shape {
private:
    virtual int minX() = 0;
    virtual int minY() = 0;
    virtual int maxX() = 0;
    virtual int maxY() = 0;
public:
    virtual ~Shape() {}
    virtual void print() = 0;
    virtual void drawLine(HDC& hdc) = 0;
    virtual Shape* copy() = 0;
};

class Line : public Shape {
private:
    POINT start;
    POINT end;

    int minX() {
        if (start.x > end.x) {
            return end.x;
        }
        return start.x;
    }
    int maxX() {
        if (start.x < end.x) {
            return end.x;
        }
        return start.x;
    }
    int minY() {
        if (start.y > end.y) {
            return end.y;
        }
        return start.y;
    }
    int maxY() {
        if (start.y < end.y) {
            return end.y;
        }
        return start.y;
    }
public:
    Line(const POINT& start, const POINT& end) {
        this->start = start;
        this->end = end;
    }
    
    void drawLine(HDC& hdc) {
        MoveToEx(hdc, int(start.x), int(start.y), NULL);
        LineTo(hdc, int(end.x), int(end.y));
    }

    Line(const Line& other) {
        this->start = other.start;
        this->end = other.end;
    }

    Shape* copy() {
        return new Line(*this);
    }

    void print() {
        cout << "Line. Coordinates:" << endl << "Start: x = " << start.x << ", y = " << start.y << endl;
        cout << "End: x = " << end.x << ", y = " << end.y << endl;
        cout << "Center coordinates:" << " x = " << (start.x + end.x) / 2.0 << ", y = " << (start.y + end.y) / 2.0 << endl;
        cout << "Min coordinates:" << " x = " << minX() << ", y = " << minY() << endl;
        cout << "Max coordinates:" << " x = " << maxX() << ", y = " << maxY() << endl;
    }
};

class PolyLine : public Shape {
private:
    POINT* points;
    int size;

    double centroidX() {
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            sum += points[i].x;
        }
        return sum / size;
    }

    double centroidY() {
        double sum = 0.0;
        for (int i = 0; i < size; i++) {
            sum += points[i].y;
        }
        return sum / size;
    }

    int minX() {
        int ans;
        ans = points[0].x;
        for (int i = 1; i < size; i++) {
            if (ans > points[i].x) ans = points[i].x;
        }

        return ans;
    }

    int maxX() {
        int ans;
        ans = points[0].x;
        for (int i = 1; i < size; i++) {
            if (ans < points[i].x) ans = points[i].x;
        }

        return ans;
    }

    int minY() {
        int ans;
        ans = points[0].y;
        for (int i = 1; i < size; i++) {
            if (ans > points[i].y) ans = points[i].y;
        }

        return ans;
    }

    int maxY() {
        int ans;
        ans = points[0].y;
        for (int i = 1; i < size; i++) {
            if (ans < points[i].y) ans = points[i].y;
        }

        return ans;
    }

public:
    PolyLine(const vector<POINT>& points_) {
        points = new POINT[points_.size() + 1];
        size = points_.size();
        for (int i = 0; i < points_.size(); i++) {
            points[i] = POINT(points_[i]);
        }
    }

    void print() {
        cout << "PolyLine. All points:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Point #" << i + 1 << ": x = " << points[i].x << ", y = " << points[i].y << endl;
        }
        cout << "Center coordinates:" << " x = " << centroidX() << ", y = " << centroidY() << endl;
        cout << "Min coordinates:" << " x = " << minX() << ", y = " << minY() << endl;
        cout << "Max coordinates:" << " x = " << maxX() << ", y = " << maxY() << endl;
    }

    PolyLine(const PolyLine& other) {
        points = new POINT[other.size];
        size = other.size;
        for (int i = 0; i < other.size; i++) {
            points[i] = POINT(other.points[i]);
        }
    }

    Shape* copy() {
        return new PolyLine(*this);
    }

    void drawLine(HDC& hdc) {
        Polyline(hdc, points, size);
    }

    ~PolyLine() {
        delete[] points;
    }
};

void readFile(string filename, vector<Shape*>& shapes) {
    ifstream file(filename);

    bool penDown = false;
    vector <POINT> points;
    string line;

    while (file.is_open() && file.good()) {
        string tmp;
        file >> tmp;
        line += tmp;
    }

    for (int i = 0; i < line.size() - 1; i++) {
        // already drawing
        if (line[i] == 'P' && line[i + 1] == 'A' && penDown) {
            int x, y;
            string tmp;
            for (int j = i + 2; line[j] != ';'; j++) {
                if (line[j] != ',')
                    tmp += line[j];
                else {
                    x = stoi(tmp);
                    tmp = "";
                }
            }
            y = stoi(tmp);
            points.push_back(POINT{ int(x * scaling_coeff), int(y * scaling_coeff) });
        }
        // moved position before starting to draw
        else if (line[i] == 'P' && line[i + 1] == 'A' && !penDown) {
            points.clear();
            int x, y;
            string tmp;
            for (int j = i + 2; line[j] != ';'; j++) {
                if (line[j] != ',')
                    tmp += line[j];
                else {
                    x = stoi(tmp);
                    tmp = "";
                }
            }
            y = stoi(tmp);
            points.push_back(POINT{ int(x * scaling_coeff), int(y * scaling_coeff) });
        }

        // start drawing shape
        else if (line[i] == 'P' && line[i + 1] == 'D') {
            penDown = true;
        }

        // finish drawing shape
        else if (line[i] == 'P' && line[i + 1] == 'U') {
            penDown = false;
            if (points.size() > 2) {
                shapes.push_back(new PolyLine(points));
            }
            else if (points.size() == 2) {
                shapes.push_back(new Line(points[0], points[1]));
            }
            points.clear();
        }
        
    }
}

class DB {
private:
    vector<Shape*> shapes;
public:
    DB(string filename) {
        readFile(filename, shapes);
    }

    void draw(HDC& hdc) {
        for (int i = 0; i < shapes.size(); i++) {
            shapes[i]->drawLine(hdc);
        }
    }
    
    DB(const DB& other) = delete;

    DB& operator=(const DB& other) = delete;

    ~DB() {
        for (int i = 0; i < shapes.size(); i++) {
            delete shapes[i];
        }
        shapes.clear();
    }
};

/////////////




//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PR24));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PR24);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    wcex.hbrBackground = CreateSolidBrush(RGB(28, 28, 28));  // set dark theme. Comment if you want a light theme

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
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
            // TODO: Add any drawing code that uses hdc here...
            // window's width: 1424
            // window's height: 700

            // If you wanna use dark theme
            HPEN hPen = CreatePen(PS_SOLID, 2, RGB(235, 235, 235)); // create a white pen
            HPEN holdPen = (HPEN)SelectObject(hdc, hPen); // select the pen into the DC

            static DB db("file.hpgl");
            DB db_Another = db;
            //db_Another.draw(hdc);
            db.draw(hdc);

            // If you used dark theme
            SelectObject(hdc, holdPen); // restore the original pen
            DeleteObject(hPen); // delete the white pen

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

// Message handler for about box.
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
