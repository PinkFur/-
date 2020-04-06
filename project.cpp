// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WindowsProject1.h"
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

#define MAX_LOADSTRING 100
#define name L"name"
#define TIMES L"times"
#define suki L"suki"
struct DishMumber
{
	wstring dish;                //菜品名称
	double p;                     //概率
	int times;
	int perfecttimes;
	DishMumber* next;
};

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
DishMumber* First = new DishMumber;

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

wstring getRandom(DishMumber* Mumlist)
{
	int num = rand() % 100;
	DishMumber* Point = Mumlist;
	double sum = 100 * Mumlist->p;
	while (sum < num)
	{
		Point = Point->next;
		sum += 100 * Point->p;
	};
	return Point->dish;
	
}

int CalcCount(void)

{

	TCHAR      chSectionNames[2048] = { 0 };      //所有节名组成的字符数组

	LPTSTR  pSectionName; //保存找到的某个节名字符串的首地址
	LPTSTR  id = (LPTSTR)malloc(20);

	int i;      //i指向数组chSectionNames的某个位置，从0开始，顺序后移

	int j = 0;     //j用来保存下一个节名字符串的首地址相对于当前i的位置偏移量

	int count = 0;     //统计节的个数


	GetPrivateProfileSectionNames(chSectionNames, 2048, L".\\ex1.ini");

	for (i = 0; i < 2048; i++, j++)

	{

		if (chSectionNames[0] == '\0')

			break;      //如果第一个字符就是0，则说明ini中一个节也没有

		if (chSectionNames[i] == '\0')

		{

			pSectionName = &chSectionNames[i - j]; //找到一个0，则说明从这个字符往前，减掉j个偏移量，

				 //就是一个节名的首地址

			j = -1;        //找到一个节名后，j的值要还原，以统计下一个节名地址的偏移量

				 //赋成-1是因为节名字符串的最后一个字符0是终止符，不能作为节名

				 //的一部分

			

			//在获取节名的时候可以获取该节中键的值，前提是我们知道该节中有哪些键。

			//MessageBox(nullptr, id, L"成功了", MB_OK);
			DishMumber* p = new DishMumber;
			p->next = First->next;
			First->next = p;

			GetPrivateProfileString(pSectionName, name, L"Error", id, 20, L".\\ex1.ini");
			p->dish = id;
			p->times=GetPrivateProfileInt(pSectionName, TIMES, 999, L".\\exl.ini");
			p->perfecttimes=GetPrivateProfileInt(pSectionName, suki, 999, L".\\exl.ini");


			if (chSectionNames[i + 1] == 0)

			{

				break;     //当两个相邻的字符都是0时，则所有的节名都已找到，循环终止

			}

		}
	}
	return 0;
}

int wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

	srand((int)time(0));
	WritePrivateProfileString(L"红烧茄子", name, L"红烧茄子", L".\\ex1.ini");
	WritePrivateProfileString(L"清蒸鲈鱼", name, L"清蒸鲈鱼", L".\\ex1.ini");
	WritePrivateProfileString(L"雪碧泡面", name, L"雪碧泡面", L".\\ex1.ini");
	WritePrivateProfileString(L"红烧茄子", TIMES, L"0", L".\\ex1.ini");
	WritePrivateProfileString(L"清蒸鲈鱼", TIMES, L"0", L".\\ex1.ini");
	WritePrivateProfileString(L"雪碧泡面", TIMES, L"0", L".\\ex1.ini");
	WritePrivateProfileString(L"红烧茄子", suki, L"0", L".\\ex1.ini");
	WritePrivateProfileString(L"清蒸鲈鱼", suki, L"0", L".\\ex1.ini");
	WritePrivateProfileString(L"雪碧泡面", suki, L"0", L".\\ex1.ini");

	CalcCount();

	/*LPTSTR str = (LPTSTR)malloc(20);
	GetPrivateProfileString(L"Test", L"id", L"Error", str, 20, L".\\ex1.ini");
	MessageBox(nullptr, str, L"成功了！", MB_OK);*/
	/*wstring dishes = L"大白菜鸡毛菜";
	HANDLE handle = CreateFile(L"C:\\Users\\hp\\Desktop\\menu.txt", GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwWritedDateSize;
	DWORD dwDataSize=100;
	DWORD DataSize;
	DWORD dwReadedSize;
	LPVOID lpData = &dishes;
	LPVOID lp;
	WriteFile(handle, lpData, dwDataSize, &dwWritedDateSize, NULL);
	GetFileSize(handle, &DataSize);
	ReadFile(handle, lp, DataSize, &dwReadedSize, NULL);
	wstring* str = lp;*/

	
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
	if (MessageBox(nullptr, TEXT("是新用户吗？"), TEXT("登录"), MB_YESNOCANCEL) == IDYES)
		
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	MessageBox(nullptr, to_wstring(First->next->next->next->perfecttimes).c_str(), L"", MB_OK);
	
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
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



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		CreateWindowW(L"Button", L"导入菜单", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			250, 10, 120, 60, hWnd,(HMENU)IDB_ONE, (HINSTANCE)hWnd, NULL);
		CreateWindowW(L"Button", L"计算比例", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			250, 100, 120, 60, hWnd, (HMENU)IDB_TWO, (HINSTANCE)hWnd, NULL);
		CreateWindowW(L"Button", L"随机点餐", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
			250, 190, 120, 60, hWnd, (HMENU)IDB_THREE, (HINSTANCE)hWnd, NULL);
	}
	case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
			case IDB_ONE:
				MessageBox(nullptr, TEXT("这个正在做"), TEXT("导入菜单"), MB_YESNOCANCEL);
				break;
			case IDB_TWO:
				MessageBox(nullptr, TEXT("这个也正在做"), TEXT("计算比例"), MB_YESNOCANCEL);
				break;
			case IDB_THREE:
			{
				
			/*DishMumber d1 = { L"红烧茄子",0.5,NULL ,0 };
			DishMumber d2 = { L"清蒸鲈鱼",0.3,NULL ,0 };
			DishMumber d3 = { L"雪碧泡面",0.2,NULL ,0 };
			DishMumber* Mumberlist = &d1;
			d1.next = &d2;
			d2.next = &d3;
			
			MessageBox(nullptr,getRandom(Mumberlist).c_str(), TEXT("随机点菜"), MB_YESNOCANCEL);*/
			}
				break;
			case IDM_CREAT:

            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
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

// “关于”框的消息处理程序。
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
