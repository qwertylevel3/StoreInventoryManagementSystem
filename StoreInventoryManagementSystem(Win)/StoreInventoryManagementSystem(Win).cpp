// StoreInventoryManagementSystem(Win).cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "StoreInventoryManagementSystem(Win).h"
#include"Inventory.h"
#include"InventoryManagement.h"
#include"TVector.h"
#include"DoubleList.h"


#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
InventoryManagement manage;						// InventoryManage
TCHAR tempName[MAX_LOADSTRING];					// ѡ����Ʒ��
int g_iIndex;									// ѡ����Ʒindex
char newTypeName[MAX_LOADSTRING];				// �½���Ʒ��
bool g_bChange;									// �Ƿ����

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_STOREINVENTORYMANAGEMENTSYSTEMWIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STOREINVENTORYMANAGEMENTSYSTEMWIN));

	

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STOREINVENTORYMANAGEMENTSYSTEMWIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_STOREINVENTORYMANAGEMENTSYSTEMWIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
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

   hWnd = CreateWindow(szWindowClass, szTitle, WS_MINIMIZEBOX|WS_OVERLAPPED|WS_SYSMENU|WS_CAPTION,
      100,100, xClient, yClient, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
void FillListBox(HWND hwndList)
{
	SendMessage(hwndList,LB_RESETCONTENT,0,0);
	for(int i=0;i<manage.GetSize();i++)
	{
		char p[100];
		strcpy(p, manage.getInventoryName(i).c_str());
		TCHAR szOut[MAX_PATH] = {0};
		MultiByteToWideChar(CP_ACP, 0,p, -1,szOut, strlen(p));
		SendMessage(hwndList,LB_ADDSTRING,0,(LPARAM)szOut);
	}
}
//
void FillChildBox(HWND hwndChildList)
{
	SendMessage(hwndChildList,LB_RESETCONTENT,0,0);
	if(tempName!=NULL)
	{
		if(g_iIndex!=-1)
		{
			TCHAR szBuffer[100];
			wsprintf(szBuffer,TEXT("һ�� %i ��"),
				manage.management[g_iIndex].InventoryList->GetSize());
			SendMessage(hwndChildList,LB_ADDSTRING,0,(LPARAM)szBuffer);

			for(int i=0;i<manage.management[g_iIndex].InventoryList->GetSize();i++)
			{
				char p[100];
				ostringstream ostr;
				ostr<<manage.management[g_iIndex].InventoryList->read(i);
				strcpy(p, (ostr).str().c_str());
				TCHAR szOut[MAX_PATH] = {0};
				MultiByteToWideChar(CP_ACP, 0,p, -1,szOut, strlen(p));
				SendMessage(hwndChildList,LB_ADDSTRING,0,(LPARAM)szOut);
			}

		}
	}

}


BOOL CALLBACK AddTypeDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HWND	hCtrlBlock;
	HWND hEdit; 
	TCHAR temp[100];
	int iTextLen;


	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON2,IDC_BUTTON1);
		hCtrlBlock = GetDlgItem(hDlg,IDD_DIALOGBAR);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR));
		return false;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			EndDialog(hDlg, LOWORD(wParam));
			return false;
		case IDC_BUTTON2:
			hEdit = GetDlgItem(hDlg,IDC_EDIT1);//hDlgΪ�����ھ�� 
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,newTypeName,iTextLen,NULL,NULL);
			manage.addInventoryType(newTypeName);
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		}
	}
	return false;
}

BOOL CALLBACK RemoveTypeDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HWND	hCtrlBlock;
	HWND hEdit; 
	TCHAR temp[100];
	char t[100];
	int iTextLen;
	int number;


	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON2,IDC_BUTTON1);
		hCtrlBlock = GetDlgItem(hDlg,IDD_DIALOGBAR3);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR3));
		return false;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			if(manage.removeInventoryType(g_iIndex)!=-1)
			{
				MessageBox(hDlg,TEXT("����Ʒ�Ѿ�ȫ���Ƴ�"),TEXT("�Ƴ���Ʒ"),NULL);
			}
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		case IDC_BUTTON2:
			EndDialog(hDlg, LOWORD(wParam));
			return false;

		}
	}
	return false;
}

BOOL CALLBACK QuitDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HWND	hCtrlBlock;
	HWND hEdit; 



	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON2,IDC_BUTTON1);
		hCtrlBlock = GetDlgItem(hDlg,IDD_DIALOGBAR3);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR3));
		return false;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			manage.save();
			MessageBox(NULL,TEXT("������ɣ�"),TEXT("����"),0);
			g_bChange=false;
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		case IDC_BUTTON2:
			EndDialog(hDlg, LOWORD(wParam));
			return false;
		}
	}
	return false;
}


BOOL CALLBACK RemoveDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HWND	hCtrlBlock;
	HWND hEdit; 
	TCHAR temp[100];
	char t[100];
	int iTextLen;
	int number;


	switch(message)
	{
	case WM_INITDIALOG:
		CheckRadioButton(hDlg,IDC_BUTTON1,IDC_BUTTON2,IDC_BUTTON1);
		hCtrlBlock = GetDlgItem(hDlg,IDD_DIALOGBAR);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR));
		return false;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:


			hEdit = GetDlgItem(hDlg,IDC_EDIT1);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			number=atoi(t);
			iTextLen = WideCharToMultiByte(CP_ACP,0,tempName,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,tempName,-1,t,iTextLen,NULL,NULL);

			manage.getInventory(t,number);
			EndDialog(hDlg, LOWORD(wParam));
			return true;
		case IDC_BUTTON2:
			EndDialog(hDlg, LOWORD(wParam));
			return false;

		}
	}
	return false;
}

BOOL CALLBACK AddDlgProc(HWND hDlg,UINT message,WPARAM wParam,LPARAM lParam)
{
	static HWND	hCtrlBlock;
	HWND hEdit; 
	TCHAR temp[100];
	char t[100];
	int iTextLen,number;
	Inventory tempInventory;
	Inventory_date tempDate1;
	Inventory_date tempDate2;


	switch(message)
	{
	case WM_INITDIALOG:
		hCtrlBlock = GetDlgItem(hDlg,IDD_DIALOGBAR1);
		SetFocus(GetDlgItem(hDlg,IDD_DIALOGBAR1));
		return false;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BUTTON1:
			iTextLen = WideCharToMultiByte(CP_ACP,0,tempName,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,tempName,-1,t,iTextLen,NULL,NULL);
			tempInventory.set_name(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT1);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempInventory.set_ProducingArea(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT2);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate1.year=atoi(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT3);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate1.month=atoi(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT4);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate1.day=atoi(t);

			tempInventory.set_BestBefore(tempDate1);

			hEdit = GetDlgItem(hDlg,IDC_EDIT5);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate2.year=atoi(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT6);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate2.month=atoi(t);

			hEdit = GetDlgItem(hDlg,IDC_EDIT7);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			tempDate2.day=atoi(t);

			tempInventory.set_ManufDate(tempDate2);

			hEdit = GetDlgItem(hDlg,IDC_EDIT8);
			GetWindowText(hEdit,temp,MAX_LOADSTRING);
			iTextLen = WideCharToMultiByte(CP_ACP,0,temp,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,temp,-1,t,iTextLen,NULL,NULL);
			number=atoi(t);

			manage.addInevntory(tempInventory,number);

			EndDialog(hDlg, LOWORD(wParam));
			return true;
		case IDC_BUTTON2:
			EndDialog(hDlg, LOWORD(wParam));
			return false;

		}
	}
	return false;
}

//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmapBK;
	static HBITMAP hBitmapAD;
	
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc,hdcMem;

	static HINSTANCE hInstance;
	static int cxChar,cyChar;
	HWND hwndButton[7];
	int iLength,iIndex,iTextLen;
	TCHAR *pVarName,*pVarValue;
	static HWND hwndList,hwndText,hwndChildList,hwndChildText;
	char t[100];

	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());

		hwndList = CreateWindow(TEXT("listbox"),NULL,WS_CHILD|WS_VISIBLE|LBS_STANDARD,
			30,180,
			cxChar*16+GetSystemMetrics(SM_CXVSCROLL),
			cyChar*10,
			hWnd,(HMENU)ID_LIST,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
		hwndText = CreateWindow(TEXT("static"),TEXT("��Ʒ��"),
			WS_CHILD|WS_VISIBLE|SS_CENTER,
			30,150,
			cxChar*18,cyChar,
			hWnd,(HMENU)ID_TEXT,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
		hwndChildList = CreateWindow(TEXT("listbox"),NULL,WS_CHILD|WS_VISIBLE|LBS_NOTIFY|WS_VSCROLL|WS_BORDER,
			200,180,
			cxChar*78+GetSystemMetrics(SM_CXVSCROLL),
			cyChar*17,
			hWnd,(HMENU)ID_CHILDLIST,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);
		hwndChildText = CreateWindow(TEXT("static"),TEXT("��ϸ��Ϣ"),
			WS_CHILD|WS_VISIBLE|SS_CENTER,
			200,150,
			cxChar*78+GetSystemMetrics(SM_CXVSCROLL),cyChar,
			hWnd,(HMENU)ID_TEXT,(HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),NULL);

		hwndButton[1] = CreateWindow(TEXT("button"),TEXT("����"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-400,yClient-100,20*cxChar,7*cyChar/4,hWnd,(HMENU)IDM_SAVE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[2] = CreateWindow(TEXT("button"),TEXT("������Ʒ����"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,150,20*cxChar,7*cyChar/3,hWnd,(HMENU)IDM_ADDTYPE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[3] = CreateWindow(TEXT("button"),TEXT("�õ���Ʒ��Ϣ"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,270,20*cxChar,7*cyChar/3,hWnd,(HMENU)IDM_GETMESSAGE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[4] = CreateWindow(TEXT("button"),TEXT("������Ʒ"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,330,20*cxChar,7*cyChar/3,hWnd,(HMENU)IDM_ADD,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[5] = CreateWindow(TEXT("button"),TEXT("�Ƴ���Ʒ"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,390,20*cxChar,7*cyChar/3,hWnd,(HMENU)IDM_REMOVE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[6] = CreateWindow(TEXT("button"),TEXT("�Ƴ���Ʒ����"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,210,20*cxChar,7*cyChar/3,hWnd,(HMENU)IDM_REMOVETYPE,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		hwndButton[0] = CreateWindow(TEXT("button"),TEXT("�˳�"),WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			xClient-200,yClient-100,20*cxChar,7*cyChar/4,hWnd,(HMENU)IDM_QUIT,((LPCREATESTRUCT)lParam)->hInstance,NULL);
		
		manage.read();
		FillListBox(hwndList);

		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		hBitmapBK=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP1));
		hBitmapAD=LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_BITMAP2));

		g_iIndex=-1;
		g_bChange=false;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		if(wmId == ID_LIST && wmEvent == LBN_SELCHANGE)
		{
			SendMessage(hwndChildList,LB_RESETCONTENT,0,0);//���

			iIndex=SendMessage(hwndList,LB_GETCURSEL,0,0);//��ȡѡ�����id

			iLength = SendMessage(hwndList,LB_GETTEXTLEN,iIndex,0)+1;
			SendMessage(hwndList,LB_GETTEXT,iIndex,(LPARAM)tempName);

			iTextLen = WideCharToMultiByte(CP_ACP,0,tempName,-1,NULL,0,NULL,NULL);
			WideCharToMultiByte(CP_ACP,0,tempName,-1,t,iTextLen,NULL,NULL);
			g_iIndex = manage.findInventoryType(t);
		}
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if(g_bChange)
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR4),hWnd,QuitDlgProc);
			DestroyWindow(hWnd);
			break;
		case IDM_QUIT:
			if(g_bChange)
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR4),hWnd,QuitDlgProc);
			DestroyWindow(hWnd);
			break;
		case IDM_ADD:
			if(g_iIndex!=-1)
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR1),hWnd,AddDlgProc);
			else
				MessageBox(hWnd,TEXT("��ѡ��һ����Ʒ����"),TEXT("������Ʒ"),NULL);
			FillChildBox(hwndChildList);
			g_bChange=true;
			break;
		case IDM_ADDTYPE:
			DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR),hWnd,AddTypeDlgProc);
			FillListBox(hwndList);
			g_iIndex=-1;
			g_bChange=true;
			break;
		case IDM_REMOVE:
			if(g_iIndex!=-1)
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR2),hWnd,RemoveDlgProc);
			else
				MessageBox(hWnd,TEXT("��ѡ��һ����Ʒ����"),TEXT("�Ƴ���Ʒ"),NULL);
			FillChildBox(hwndChildList);
			g_bChange=true;
			break;
		case IDM_SAVE:
			manage.save();
			MessageBox(NULL,TEXT("������ɣ�"),TEXT("����"),0);
			g_bChange=false;
			break;
		case IDM_GETMESSAGE:
			if(g_iIndex!=-1)
				FillChildBox(hwndChildList);
			else
				MessageBox(hWnd,TEXT("��ѡ��һ����Ʒ����"),TEXT("�õ���Ʒ��Ϣ"),NULL);
			g_bChange=true;
			break;
		case IDM_REMOVETYPE:
			if(g_iIndex!=-1)
				DialogBox(hInstance,MAKEINTRESOURCE(IDD_DIALOGBAR3),hWnd,RemoveTypeDlgProc);
			else
				MessageBox(hWnd,TEXT("��ѡ��һ����Ʒ����"),TEXT("�Ƴ���Ʒ����"),NULL);
			g_iIndex=-1;
			FillListBox(hwndList);
			FillChildBox(hwndChildList);
			g_bChange=true;
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		hdcMem=CreateCompatibleDC(hdc);
		SelectObject(hdcMem,hBitmapBK);
		
		BitBlt(hdc,20,15,1000,130,hdcMem,0,0,SRCCOPY);
		SelectObject(hdcMem,hBitmapAD);
		BitBlt(hdc,30,340,150,150,hdcMem,0,0,SRCCOPY);
		DeleteDC(hdcMem);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DeleteObject(hBitmapBK);
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
