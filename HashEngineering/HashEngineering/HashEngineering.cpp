// HashEngineering.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#pragma warning(disable:4305 4309)
#pragma comment(lib,"ole32")
#pragma comment(lib,"comsupp")
#include <objbase.h>
#include <comip.h>
#include <mlang.h>
#include "HashEngineering.h"

typedef _com_ptr_t<_com_IIID<IMultiLanguage3, &IID_IMultiLanguage3> > IMultiLanguage3Ptr;
#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
#ifndef Win32
#include <sstream>
void print(WCHAR *p1){
	static HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(out, p1, wcslen(p1), NULL, NULL);
}
template<typename T>
void printf(T t){
	std::wstringstream wss;
	wss << t;
	std::wstring ws;
	wss >> ws;
	ws = ws + L"\n";
	print((WCHAR*)ws.c_str());
}
#else
#endif
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	AllocConsole();
 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_HASHENGINEERING, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}
	printf<wchar_t*>(L"xcvxcvxc");
	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HASHENGINEERING));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	FreeConsole();
	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HASHENGINEERING));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_HASHENGINEERING);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   if (!hWnd)
   {
      return FALSE;
   }

   CreateWindow(L"Edit", L"sdfsdfsd", WS_CHILD | ES_MULTILINE | WS_VISIBLE | ES_LEFT, 80, 80, 500, 150, hWnd, (HMENU)6521, hInst, NULL);
   CreateWindow(L"Edit", L"", WS_CHILD | ES_MULTILINE | WS_VISIBLE | ES_LEFT, 80, 240, 500, 150, hWnd, (HMENU)6012, hInst, NULL);
   CreateWindow(L"Button", L"�鿴", WS_CHILD | BS_TEXT | WS_VISIBLE , 550, 80, 200, 80, hWnd, (HMENU)3721, hInst, NULL);
   DWORD dw = GetLastError();
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void sdfsdf(wchar_t *lp){
	CoInitialize(NULL);
	{
		IMultiLanguage3Ptr pML(CLSID_CMultiLanguage, NULL, CLSCTX_INPROC);
		char *data = (char *)lp;//{ 0xD6, 0xD0, 0xCE, 0xC4, 0xB1, 0xE0, 0xC2, 0xEB };
		int isize = sizeof(data);
		DetectEncodingInfo result[32];
		int result_count = sizeof(result) / sizeof(result[0]);
		HRESULT hr = pML->DetectInputCodepage(MLDETECTCP_NONE, 0, data, &isize, result, &result_count);
		if (!SUCCEEDED(hr))
		{
			fprintf(stderr, "Failed with 0x%x\n", hr);
			CoUninitialize();
			return ;
		}
		WCHAR p[9068] = L"";
		for (int i = 0; i < result_count; i++)
		{
			WCHAR desc[100] = { 0 };
			pML->GetCodePageDescription(result[i].nCodePage, result[i].nLangID, desc, 100);
			//printf("CP:%d (%S)\n", result[i].nCodePage, desc);
			wsprintf(p, L"%S CP:%d (%S)\n",p, result[i].nCodePage, desc);
		}
		print(p);
	}
	CoUninitialize();
}
//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 3721:{
					  int len = ::SendMessage(GetDlgItem(hWnd, 6521), WM_GETTEXTLENGTH, 0, 0);
					  wchar_t* buffer = new wchar_t[len + 1];
					  int n = ::SendMessage(GetDlgItem(hWnd, 6521), WM_GETTEXT, len + 1, (LPARAM)buffer);
					  //::PostMessage(GetDlgItem(hWnd, 6012), WM_SETTEXT, (WPARAM)buffer, (LPARAM)n);
					  printf(buffer);
					  sdfsdf(buffer);
					  delete buffer;
					  buffer = NULL;
		}break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
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
