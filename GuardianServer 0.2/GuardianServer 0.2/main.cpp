#include "main.h"

int APIENTRY WinMain(
	HINSTANCE hInstance,//���α׷����ν��Ͻ��ڵ�
	HINSTANCE hPrevInstance,//16��Ʈ����ȣȯ���������Ķ����(������NULL)
	LPSTR IpszCmdParam,//��������Run�������ǰ��
	int nCmdShow)//���α׷��ǽ�������(�ּ�ȭ,�ִ�ȭ,����)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;


	//(Start)������Ŭ��������(�������μ���)
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//�������ǻ���, ���̼���
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//�������Ǹ��콺Ŀ������
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//������Ÿ��Ʋ���Ǿ����ܼ���
	WndClass.hInstance = hInstance;//�ν��Ͻ��ڵ鷯���
	WndClass.lpfnWndProc = WndProc_Main;//�޽��������ʵ��
	WndClass.lpszClassName = IpszClass;//�ش�������Ŭ�������
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�����콺Ÿ�ϼ���(ũ�Ⱑ����Ǹ�ٽñ׸�)
	RegisterClass(&WndClass);//���ݱ���'������Ŭ��������' �����ۼ��Ѽ�������ġ�����Ѵ�.
	//(End)������Ŭ��������(�������μ���)


	//(S)���������(�������μ���(�ټ���������))
	hWnd_Main = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOOLWINDOW /*| WS_EX_TOPMOST*/,
		IpszClass,//�����ϰ����ϴ������츦�ǹ��ϴ¹��ڿ�
		IpszClass,//Ÿ��Ʋ�ٿ����������ڿ�
		WS_POPUP,//��������ϴ�������������
		CW_USEDEFAULT, CW_USEDEFAULT,//��������X,Y��ǥ
		CW_USEDEFAULT, CW_USEDEFAULT,//��������X,Yũ��
		NULL,//(�����쳻�ο������츦�����ϰ�������θ����������ڵ�����)
		(HMENU)NULL,//������󿡼�����Ҹ޴����ڵ�����
		hInstance,//�����������α׷����ڵ�
		NULL);//�����������츦�����ҋ��������Ķ���͸�����
	ShowWindow(hWnd_Main, SW_HIDE);//�����츦ȭ�鿡����ϸ�WinMain���������ѽ������¸����ڷΰ��´�.
	SetLayeredWindowAttributes(hWnd_Main, NULL, 0, LWA_ALPHA);	//ó���� 0���� �ʱ�ȭ������������ ����� ���������� ����.
	//(E)���������(�������μ���(�ټ���������))


	//(S)����Ʈ��Register ������ ����
	WndClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));//������ �⺻����
	WndClass.lpfnWndProc = WndProc_Register_SmartPhone;
	WndClass.lpszClassName = TEXT("SmartPhoneRegister");
	RegisterClass(&WndClass);	//���ݱ��� '������ Ŭ���� ����' ���� �ۼ��� ������ ��ġ�� ����Ѵ�.

	hWnd_Register_SmartPhone = CreateWindow(
		L"SmartPhoneRegister",//�����ϰ����ϴ������츦�ǹ��ϴ¹��ڿ�
		IpszClass,//Ÿ��Ʋ�ٿ����������ڿ�
		WS_OVERLAPPEDWINDOW,//��������ϴ�������������
		CW_USEDEFAULT, CW_USEDEFAULT,//��������X,Y��ǥ
		(int)((GetSystemMetrics(SM_CYSCREEN)*0.6)*1.6), (int)GetSystemMetrics(SM_CYSCREEN)*0.6,//��������X,Yũ��
		NULL,//(�����쳻�ο������츦�����ϰ�������θ����������ڵ�����)
		(HMENU)NULL,//������󿡼�����Ҹ޴����ڵ�����
		hInstance,//�����������α׷����ڵ�
		NULL);//�����������츦�����ҋ��������Ķ���͸�����
	//(E)����Ʈ��Register ������ ����

	//(S)Register ������ ����
	WndClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));//������ �⺻����
	WndClass.lpfnWndProc = WndProc_Register_USB;
	WndClass.lpszClassName = TEXT("USBRegister");
	RegisterClass(&WndClass);	//���ݱ��� '������ Ŭ���� ����' ���� �ۼ��� ������ ��ġ�� ����Ѵ�.

	hWnd_Register_USB = CreateWindow(
		L"USBRegister",//�����ϰ����ϴ������츦�ǹ��ϴ¹��ڿ�
		IpszClass,//Ÿ��Ʋ�ٿ����������ڿ�
		WS_OVERLAPPEDWINDOW,//��������ϴ�������������
		CW_USEDEFAULT, CW_USEDEFAULT,//��������X,Y��ǥ
		(int)((GetSystemMetrics(SM_CYSCREEN)*0.6)*1.6), (int)GetSystemMetrics(SM_CYSCREEN)*0.6,//��������X,Yũ��
		NULL,//(�����쳻�ο������츦�����ϰ�������θ����������ڵ�����)
		(HMENU)NULL,//������󿡼�����Ҹ޴����ڵ�����
		hInstance,//�����������α׷����ڵ�
		NULL);//�����������츦�����ҋ��������Ķ���͸�����
	//(E)Register ������ ����


	//(S)Ʈ���̽�����
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd_Main;
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.uCallbackMessage = TRAY_NOTIFY;
	nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1));
	lstrcpy(nid.szTip, L"Guardian");
	Shell_NotifyIcon(NIM_ADD, &nid);//�����ܼ�������������
	//(E)Ʈ���̽�����

	//(S)GDI+Ȱ��ȭ
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok)
	{
		MessageBox(NULL, TEXT("GDI+ ���̺귯���� �ʱ�ȭ�� �� �����ϴ�."), TEXT("�˸�"), MB_OK);
		return 0;
	}
	//(E)GDI+Ȱ��ȭ


	//(S)�޽�������
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	//(E)�޽�������
	GdiplusShutdown(gpToken);
	return (int)Message.wParam;
}

//���� �޽�������
LRESULT CALLBACK WndProc_Main(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HANDLE LockTimer;
	switch (iMessage)
	{
	case WM_CREATE:
		LockTimer = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);	//���Ÿ�̸� ����

		RegisterHotKey(hWnd, 0x0000, NULL, VK_F2);	//���
		RegisterHotKey(hWnd, 0x0001, NULL, VK_F3);	//�������
		RegisterHotKey(hWnd, 0x0002, NULL, VK_F4);	//����

		WSADATA wsaData;	//���� ��ŸƮ��/Ŭ���� �ڵ�ȭ ����ü
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	//������ ���� ����
			MessageBox(NULL, TEXT("WSAStartup() error!"), L" ", MB_OK);

		CreateThread(NULL, 0, Socket_MessageListener, NULL, 0, NULL);

		if(FRegReadInt(HKEY_CURRENT_USER, L"Fairy", L"Code", 0) == 0)
		{
			if (MessageBox(hWnd_Main, L"Guardian�� ó�������ϼ̽��ϴ�.\nUSB ����� �����մϴ�.", IpszClass, MB_YESNO))
			{
				PostMessage(hWnd, WM_COMMAND, IDC_TRAYMENU_REGISTER_USB, NULL);
			}
		}
		else //ó�������� �ƴ�
		{
			//if (!KeyCheck() && !SmartUnlock) //�׽�Ʈ�� ���� ���۽� ����� ����
				//Lock();
		}

		return 0;
		
	case WM_TIMER:
		Socket_MessageProcessor("TYPE=AUTOLOCK:COMMAND=CLOCK:");
		return 0;

	case WM_DEVICECHANGE:
		if (FRegReadInt(HKEY_CURRENT_USER, L"Fairy", L"Code", 0) != 0)
		{
			switch ((UINT)wParam)
			{
			case DBT_DEVICEARRIVAL:
				if (KeyCheck())
				{
					UnLock();
					SmartUnlock = false;
				}


				if (IsWindowVisible(hWnd_Register_USB))
					InvalidateRect(hWnd_Register_USB, NULL, true);
				break;

			case DBT_DEVICEREMOVECOMPLETE:
				if (!KeyCheck() && !SmartUnlock)	//����Ʈ���� ��������Ͽ��� ��� Ű�� �ƴ� USB�� �����Ǿ ����� ����(Ű�� USB�� ���)
					Lock();

				if (IsWindowVisible(hWnd_Register_USB))
					InvalidateRect(hWnd_Register_USB, NULL, true);
				break;
			}
		}
		break;

	case WM_HOTKEY:
		switch (wParam)
		{
		case 0:
			Lock();
			break;
		case 1:
			UnLock();
			break;
		case 2:
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd_Main, &ps);
		Draw_Main(hdc);
		EndPaint(hWnd_Main, &ps);
		break;

	case TRAY_NOTIFY:
		switch (lParam)
		{
		case WM_RBUTTONDOWN:
			HMENU hMenu, hPopupMenu;
			POINT pt;
			hMenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_TRAYMENU));
			hPopupMenu = GetSubMenu(hMenu, 0);
			GetCursorPos(&pt);
			SetForegroundWindow(hWnd);
			TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, pt.x, pt.y, 0, hWnd, NULL);
			SetForegroundWindow(hWnd);
			DestroyMenu(hPopupMenu);
			DestroyMenu(hMenu);
			break;
		}
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_TRAYMENU_LOCK:
			Lock();
			break;

		case IDC_TRAYMENU_REGISTER_SMARTPHONE:
			ShowWindow(hWnd_Register_SmartPhone, SW_SHOW);
			SendMessage(hWnd_Register_SmartPhone, WM_PAINT, NULL, NULL);	//�ٷ� �׷��ֱ�
			break;
		case IDC_TRAYMENU_REGISTER_USB:
			ShowWindow(hWnd_Register_USB, SW_SHOW);
			SendMessage(hWnd_Register_USB, WM_PAINT, NULL, NULL);	//�ٷ� �׷��ֱ�
			break;

		case IDC_TRAYMENU_SETUP:

			break;

		case IDC_TRAYMENU_EXIT:
			if (MessageBox(hWnd_Main, L"������ �����ұ��?\n�����ϸ� �� PC�� ��ȣ���� ���ϰԵ˴ϴ�!", IpszClass, MB_YESNO) == IDYES)
				PostQuitMessage(0);
			break;
		}
		break;


	case WM_DESTROY:
		KillTimer(hWnd, 1);
		//(S)Ʈ���̽�����
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 0;
		Shell_NotifyIcon(NIM_DELETE, &nid);
		//(E)Ʈ���̽�����
		UnregisterHotKey(hWnd, 0x0000);	//�Ҵ��� ��Ű ����
		UnregisterHotKey(hWnd, 0x0001);	//�Ҵ��� ��Ű ����
		UnregisterHotKey(hWnd, 0x0002);	//�Ҵ��� ��Ű ����
		WSACleanup();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//����Ʈ�� �������� �޽�������
LRESULT CALLBACK WndProc_Register_SmartPhone(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	switch (iMessage)
	{
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd_Register_SmartPhone, &ps);
		Draw_Register_SmartPhone(hdc);
		EndPaint(hWnd_Register_SmartPhone, &ps);
		break;

		case WM_LBUTTONDOWN:
			x = LOWORD(lParam);
			y = HIWORD(lParam);

			
			break;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;	//����޽��� ����ä��
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//USB �������� �޽�������
LRESULT CALLBACK WndProc_Register_USB(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int x, y;
	switch (iMessage)
	{
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hWnd_Register_USB, &ps);
		Draw_Register_USB(hdc);
		EndPaint(hWnd_Register_USB, &ps);
		break;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		for (int i = 0; i < driveNum; i++)
		{
			if (USB_Icon[i].position.left < x && x < USB_Icon[i].position.right)
			{
				if (USB_Icon[i].position.top < y && y < USB_Icon[i].position.bottom)
				{
					for (int j = 0; j < driveNum;j++)
					{
						USB_Icon[j].selected = false;
					}
					USB_Icon[i].selected = true;
					SendMessage(hWnd_Register_USB, WM_PAINT, NULL, NULL);	//�ٷ� �׷��ֱ�
					InvalidateRect(hWnd_Register_USB,NULL, true);
				}
			}
		}

		if (Save_Icon.position.left < x && x < Save_Icon.position.right)
		{
			if (Save_Icon.position.top < y && y < Save_Icon.position.bottom)
			{
				for (int i = 0; i < driveNum; i++)
				{
					if (USB_Icon[i].selected)
					{ 
						DWORD DSerialNumber;
						FString DriveName = USB_Icon[i].DriveName;
						//DriveName += "\\";

						if (GetVolumeInformation(DriveName, NULL, NULL, &DSerialNumber, NULL, NULL, NULL, NULL))
						{
							FString SerialNumber = DSerialNumber;	//��Ƽ����Ʈ->�����ڵ�;
							FRegWriteInt(HKEY_CURRENT_USER, L"Fairy", L"Code", SerialNumber.FStringToInt());

							MessageBox(hWnd_Main, L"KEY�� �缳���Ǿ����ϴ�!", IpszClass, NULL);
							ShowWindow(hWnd_Register_USB, SW_HIDE);
						}

					}
				}
			}
		}
		break;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;	//����޽��� ����ä��
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//UDP���� �޽�������
DWORD WINAPI Socket_MessageListener(LPVOID arg)
{
	//(Start)UDP���� Ȱ��ȭ
	int strLen;
	SOCKADDR_IN servAdr;

	servSock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(8787);

	bind(servSock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	//(End)UDP���� Ȱ��ȭ

	char strMessage[BUF_SIZE];
	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		strLen = recvfrom(servSock, strMessage, BUF_SIZE, 0, (SOCKADDR*)&clntAdr, &clntAdrSz);
		strMessage[strLen] = NULL;
		Socket_MessageProcessor(strMessage);
	}
}

/*
FString�� ������ 123,456,789��
BYTE[0] = 123, BYTE[1] = 456, BYTE[2] = 789�� ��ȯ
*/
int StrNumToByte(FString Str,BYTE byte[])
{
	int size = 0;
	FString Temp = Str.Tokenizing(L",");
	while (!Temp.IsEmpty())
	{
		byte[size] = Temp.FStringToInt();
		size++;
		Temp = Str.Tokenizing(L",");
	}
	return size;
}

FString ByteToStrNum(BYTE byte[],int size)
{
	FString str;
	for (int i = 0; i < size; i++)
	{
		str += byte[i];
		str += ",";
	}
	return str;
}

FString Decrypt(FString Cyper,BYTE *Key)
{
	BYTE Cyper_byteStr[2048] = { 0x00, };
	BYTE Plain_byteStr[2048] = { 0x00, };

	int Cyper_size = StrNumToByte(Cyper, Cyper_byteStr);	//FString->Byte
	int Plain_size = SEED_CBC_Decrypt(Key, EmbedIV, Cyper_byteStr, Cyper_size, Plain_byteStr);//��ȣȭ

	return ByteToStrNum(Plain_byteStr, Plain_size);	//Byte->FString
}


void Socket_MessageProcessor(char* str)
{
	FString Block = str;
	FString Type = Block.Parsing(L"TYPE=", L":");
	if (Type == L"LOCK" && !KeyCheck())	//USBŰ�� ����Ǿ����� �ʾƾ���.
	{
		FString ID = Block.Parsing(L"ID=", L":");
		BYTE plain[128];
		StrNumToByte(GetKey(), plain);
		wchar_t wplain[128];
		GetID().FStringToWideChar(wplain);
		if (Decrypt(ID, plain).IsContain(wplain))
		{
			AutoMode = false;	//��ư���� ���� �ڵ���� ����
			if (!IsWindowVisible(hWnd_Main))
			{
				Lock();
				sendto(servSock, "LOCK", 4, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
			}
			else
			{
				UnLock();
				sendto(servSock, "UNLOCK", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
				SmartUnlock = true;
			}
		}
		else
		{
			MessageBox(hWnd_Main, L"����Ʈ���� ��ϵ��� �ʾҰų� ���� ���� ID�Դϴ�!", L"Guardian", NULL);
		}
	}
	else if (Type == L"AUTOLOCK" && !KeyCheck())	//USBŰ�� ����Ǿ����� �ʾƾ���.
	{
		FString Command = Block.Parsing(L"COMMAND=", L":");
		if (Command == L"INIT")
		{
			FString ID = Block.Parsing(L"ID=", L":");
			BYTE plain[128];
			StrNumToByte(GetKey(), plain);
			wchar_t wplain[128];
			GetID().FStringToWideChar(wplain);
			if (Decrypt(ID, plain).IsContain(wplain))
			{
				AutoMode = true;	//�ڵ���ݸ�� ��ȣ �߻�
				AutoLockTimer = 0;
				UnLock();
				sendto(servSock, "UNLOCK", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
			}
		}
		else if (Command == L"CLOCK")
		{
			AutoLockTimer++;

			if (AutoLockTimer > LOCKTIME && AutoMode==true)	//��ݽð��� ������ �ڵ���ݸ���� ���
			{
				if (!IsWindowVisible(hWnd_Main))
				{
					Lock();
					sendto(servSock, "LOCK", 4, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
				}
			}
		}
	}
	else if (Type == L"LINK")
	{
		if (IsWindowVisible(hWnd_Main))
			sendto(servSock, "LOCK", 4, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
		else
			sendto(servSock, "UNLOCK", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
	}
	else if (Type == L"REGI")
	{
		if (IsWindowVisible(hWnd_Register_SmartPhone))
		{
			FString PhoneNumber = Block.Parsing(L"PNUM=", L":");
			FString CyperKey = Block.Parsing(L"KEY=", L":");
			FString CyperID = Block.Parsing(L"ID=", L":");

			//Ű ��ȣȭ
			FString PlainKey = Decrypt(CyperKey, EmbedKey);

			//Ű ������Ʈ���� ����
			if (!SetKey(PlainKey))
			{
				MessageBox(hWnd_Main, L"��� ����!", L"Guardian", NULL);
				return;
			}

			//ID ��ȣȭ
			BYTE byteKey[256];
			StrNumToByte(PlainKey, byteKey);
			FString PlainID = Decrypt(CyperID, byteKey);

			//ID ������Ʈ���� ����
			if (!SetID(PlainID))
			{
				MessageBox(hWnd_Main, L"��� ����!", L"Guardian", NULL);
				return;
			}

			sendto(servSock, "REGIST", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
			MessageBox(hWnd_Main, L"����Ʈ���� ����Ͽ����ϴ�.", L"Guardian", NULL);
		}
	}
}

void Lock()
{
	ShowWindow(FindWindow(L"Shell_TrayWnd", NULL), SW_HIDE);	//�׽�ũ�� HIDE
	SetLayeredWindowAttributes(hWnd_Main, NULL, 0, LWA_ALPHA);
	ShowWindow(hWnd_Main, SW_MAXIMIZE);
	SendMessage(hWnd_Main, WM_PAINT, NULL, NULL);	//PostMessage�� ��ٸ����ʰ� �����ϱ� ������ ����� �׷����� ���� ������ȭ�� �����ع���

	for (int trans = 0; trans < 256; trans += 15)
	{
		SetLayeredWindowAttributes(hWnd_Main, NULL, trans, LWA_ALPHA);
		Sleep(15);
	}
	SetForegroundWindow(hWnd_Main);	//Z���� ����
}

void UnLock()
{
	for (int trans = 255; trans > -1; trans -= 15)
	{
		SetLayeredWindowAttributes(hWnd_Main, NULL, trans, LWA_ALPHA);
		Sleep(15);
	}
	ShowWindow(hWnd_Main, SW_HIDE);

	ShowWindow(FindWindow(L"Shell_TrayWnd", NULL), SW_SHOW);	//�׽�ũ�� HIDE
}

void Draw_Main(HDC hdc)
{
	//PNG�ε�
	HRSRC hResource = FindResource(g_hInst, MAKEINTRESOURCE(IDB_PNG1), TEXT("PNG"));
	if (!hResource)    return;
	DWORD imageSize = SizeofResource(g_hInst, hResource);
	HGLOBAL hGlobal = LoadResource(g_hInst, hResource);
	LPVOID pData = LockResource(hGlobal);
	HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, imageSize);
	LPVOID pBuffer = GlobalLock(hBuffer);
	CopyMemory(pBuffer, pData, imageSize);
	GlobalUnlock(hBuffer);
	IStream *pStream;
	CreateStreamOnHGlobal(hBuffer, TRUE, &pStream);
	Image I(pStream);
	pStream->Release();
	if (I.GetLastStatus() != Ok)
		return;

	Graphics G(hdc);
	G.DrawImage(&I, 
		(GetSystemMetrics(SM_CXSCREEN) / 2) - ((GetSystemMetrics(SM_CXSCREEN) / 3) / 2),
		(GetSystemMetrics(SM_CYSCREEN) / 2) - ((GetSystemMetrics(SM_CXSCREEN) / 3) / 2),
		GetSystemMetrics(SM_CXSCREEN) / 3,
		GetSystemMetrics(SM_CXSCREEN) / 3);
}

void Draw_Register_SmartPhone(HDC hdc)
{
	//PNG�ε�
	HRSRC hResource_Regist = FindResource(g_hInst, MAKEINTRESOURCE(IDB_PNG5), TEXT("PNG"));
	if (!hResource_Regist)    return;
	DWORD imageSize_Regist = SizeofResource(g_hInst, hResource_Regist);
	HGLOBAL hGlobal_Regist = LoadResource(g_hInst, hResource_Regist);
	LPVOID pData_Regist = LockResource(hGlobal_Regist);
	HGLOBAL hBuffer_Regist = GlobalAlloc(GMEM_MOVEABLE, imageSize_Regist);
	LPVOID pBuffer_Regist = GlobalLock(hBuffer_Regist);
	CopyMemory(pBuffer_Regist, pData_Regist, imageSize_Regist);
	GlobalUnlock(hBuffer_Regist);
	IStream *pStream_Regist;
	CreateStreamOnHGlobal(hBuffer_Regist, TRUE, &pStream_Regist);
	Image IMG_Regist(pStream_Regist);
	pStream_Regist->Release();
	if (IMG_Regist.GetLastStatus() != Ok)
		return;

	RECT Register_WindowSize;
	GetWindowRect(hWnd_Register_USB, &Register_WindowSize);
	int width = Register_WindowSize.right - Register_WindowSize.left;
	int height = Register_WindowSize.bottom - Register_WindowSize.top;

	Graphics G(hdc);
	G.DrawImage(&IMG_Regist,
		0,0,width,(int)(height*0.9));
}

void Draw_Register_USB(HDC hdc)
{
	//PNG�ε�
	HRSRC hResource_USB_Off = FindResource(g_hInst, MAKEINTRESOURCE(IDB_PNG2), TEXT("PNG"));
	if (!hResource_USB_Off)    return;
	DWORD imageSize_USB_Off = SizeofResource(g_hInst, hResource_USB_Off);
	HGLOBAL hGlobal_USB_Off = LoadResource(g_hInst, hResource_USB_Off);
	LPVOID pData_USB_Off = LockResource(hGlobal_USB_Off);
	HGLOBAL hBuffer_USB_Off = GlobalAlloc(GMEM_MOVEABLE, imageSize_USB_Off);
	LPVOID pBuffer_USB_Off = GlobalLock(hBuffer_USB_Off);
	CopyMemory(pBuffer_USB_Off, pData_USB_Off, imageSize_USB_Off);
	GlobalUnlock(hBuffer_USB_Off);
	IStream *pStream_USB_Off;
	CreateStreamOnHGlobal(hBuffer_USB_Off, TRUE, &pStream_USB_Off);
	Image IMG_USB_Off(pStream_USB_Off);
	pStream_USB_Off->Release();
	if (IMG_USB_Off.GetLastStatus() != Ok)
		return;

	HRSRC hResource_USB_On = FindResource(g_hInst, MAKEINTRESOURCE(IDB_PNG3), TEXT("PNG"));
	if (!hResource_USB_On)    return;
	DWORD imageSize_USB_On = SizeofResource(g_hInst, hResource_USB_On);
	HGLOBAL hGlobal_USB_On = LoadResource(g_hInst, hResource_USB_On);
	LPVOID pData_USB_On = LockResource(hGlobal_USB_On);
	HGLOBAL hBuffer_USB_On = GlobalAlloc(GMEM_MOVEABLE, imageSize_USB_On);
	LPVOID pBuffer_USB_On = GlobalLock(hBuffer_USB_On);
	CopyMemory(pBuffer_USB_On, pData_USB_On, imageSize_USB_On);
	GlobalUnlock(hBuffer_USB_On);
	IStream *pStream_USB_On;
	CreateStreamOnHGlobal(hBuffer_USB_On, TRUE, &pStream_USB_On);
	Image IMG_USB_On(pStream_USB_On);
	pStream_USB_On->Release();
	if (IMG_USB_On.GetLastStatus() != Ok)
		return;

	HRSRC hResource_USB_Save = FindResource(g_hInst, MAKEINTRESOURCE(IDB_PNG4), TEXT("PNG"));
	if (!hResource_USB_Save)    return;
	DWORD imageSize_USB_Save = SizeofResource(g_hInst, hResource_USB_Save);
	HGLOBAL hGlobal_USB_Save = LoadResource(g_hInst, hResource_USB_Save);
	LPVOID pData_USB_Save = LockResource(hGlobal_USB_Save);
	HGLOBAL hBuffer_USB_Save = GlobalAlloc(GMEM_MOVEABLE, imageSize_USB_Save);
	LPVOID pBuffer_USB_Save = GlobalLock(hBuffer_USB_Save);
	CopyMemory(pBuffer_USB_Save, pData_USB_Save, imageSize_USB_Save);
	GlobalUnlock(hBuffer_USB_Save);
	IStream *pStream_USB_Save;
	CreateStreamOnHGlobal(hBuffer_USB_Save, TRUE, &pStream_USB_Save);
	Image IMG_USB_Save(pStream_USB_Save);
	pStream_USB_Save->Release();
	if (IMG_USB_Save.GetLastStatus() != Ok)
		return;



	RECT Register_WindowSize;
	GetWindowRect(hWnd_Register_USB, &Register_WindowSize);
	int width = Register_WindowSize.right - Register_WindowSize.left;
	int height = Register_WindowSize.bottom - Register_WindowSize.top;
	int icon_sideSize = (int)(height / 5);

	Font F(L"���� ����� 230", height/15, FontStyleBold, UnitPixel);	//��Ʈ����
	PointF P(10.0f, 10.0f);
	SolidBrush B(Color(0, 0, 0));
	Graphics G(hdc);

	G.SetTextRenderingHint((TextRenderingHint)4);	//��Ƽ������� �ִ�

	wchar_t driveList[256];
	driveNum = GetLogicalDriveStrings(256, driveList) / 4;
	for (int i = 0; i < driveNum; i++)
	{
		driveList[3 + i * 4] = ',';
	}
	FString Drive = driveList;
	int startPosition = ((width - (icon_sideSize*driveNum)) / 2);

	for (int i = 0; i < driveNum; i++)
	{
		USB_Icon[i].position.left = startPosition + i*icon_sideSize;
		USB_Icon[i].position.right = USB_Icon[i].position.left + icon_sideSize;
		USB_Icon[i].position.top = height / 5;
		USB_Icon[i].position.bottom = USB_Icon[i].position.top + icon_sideSize;
		USB_Icon[i].DriveName = Drive.Tokenizing(L",");
		if (USB_Icon[i].selected)
			G.DrawImage(&IMG_USB_On, startPosition + i*icon_sideSize, height / 5, icon_sideSize, icon_sideSize);
		else
			G.DrawImage(&IMG_USB_Off, startPosition + i*icon_sideSize, height/5, icon_sideSize, icon_sideSize);
		P.X = USB_Icon[i].position.left;
		P.Y = USB_Icon[i].position.bottom;
		G.DrawString(USB_Icon[i].DriveName, -1, &F, P, &B);
	}

	int save_side = (height / 4);
	Save_Icon.position.left = (width - save_side) / 2;
	Save_Icon.position.right = Save_Icon.position.left + save_side;
	Save_Icon.position.top = height - (height / 2);
	Save_Icon.position.bottom = Save_Icon.position.top + save_side;
	G.DrawImage(&IMG_USB_Save, (width - save_side) / 2, height - (height / 2), save_side, save_side);

	P.X = Save_Icon.position.left;
	P.Y = Save_Icon.position.bottom;
	G.DrawString(L"�����ϱ�", -1, &F, P, &B);
}