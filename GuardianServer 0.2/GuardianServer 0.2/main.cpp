#include "main.h"

int APIENTRY WinMain(
	HINSTANCE hInstance,//프로그램의인스턴스핸들
	HINSTANCE hPrevInstance,//16비트와의호환성을위한파라미터(보통은NULL)
	LPSTR IpszCmdParam,//실행직후Run할파일의경로
	int nCmdShow)//프로그램의실행형태(최소화,최대화,모양등)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;


	//(Start)윈도우클래스생성(전역적인설정)
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//윈도우의색상, 무늬설정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);//윈도우의마우스커서설정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//윈도우타이틀바의아이콘설정
	WndClass.hInstance = hInstance;//인스턴스핸들러등록
	WndClass.lpfnWndProc = WndProc_Main;//메시지리스너등록
	WndClass.lpszClassName = IpszClass;//해당윈도우클래스등록
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우스타일설정(크기가변경되면다시그림)
	RegisterClass(&WndClass);//지금까지'윈도우클래스생성' 에서작성한설정을마치고등록한다.
	//(End)윈도우클래스생성(전역적인설정)


	//(S)윈도우생성(지역적인설정(다수생성가능))
	hWnd_Main = CreateWindowEx(
		WS_EX_LAYERED | WS_EX_TOOLWINDOW /*| WS_EX_TOPMOST*/,
		IpszClass,//생성하고자하는윈도우를의미하는문자열
		IpszClass,//타이틀바에보여물문자열
		WS_POPUP,//만들고자하는윈도우의형태
		CW_USEDEFAULT, CW_USEDEFAULT,//윈도우의X,Y좌표
		CW_USEDEFAULT, CW_USEDEFAULT,//윈도우의X,Y크기
		NULL,//(윈도우내부에윈도우를생성하고싶은경우부모윈도우의핸들지정)
		(HMENU)NULL,//윈도우상에서사용할메뉴의핸들지정
		hInstance,//이윈도우프로그램의핸들
		NULL);//여러개윈도우를생성할떄고유의파라미터를송출
	ShowWindow(hWnd_Main, SW_HIDE);//윈도우를화면에출력하며WinMain에서지정한실행형태를인자로갖는다.
	SetLayeredWindowAttributes(hWnd_Main, NULL, 0, LWA_ALPHA);	//처음에 0으로 초기화해주지않으면 배경이 검은색으로 나옴.
	//(E)윈도우생성(지역적인설정(다수생성가능))


	//(S)스마트폰Register 윈도우 생성
	WndClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));//윈도우 기본색상
	WndClass.lpfnWndProc = WndProc_Register_SmartPhone;
	WndClass.lpszClassName = TEXT("SmartPhoneRegister");
	RegisterClass(&WndClass);	//지금까지 '윈도우 클래스 생성' 에서 작성한 설정을 마치고 등록한다.

	hWnd_Register_SmartPhone = CreateWindow(
		L"SmartPhoneRegister",//생성하고자하는윈도우를의미하는문자열
		IpszClass,//타이틀바에보여물문자열
		WS_OVERLAPPEDWINDOW,//만들고자하는윈도우의형태
		CW_USEDEFAULT, CW_USEDEFAULT,//윈도우의X,Y좌표
		(int)((GetSystemMetrics(SM_CYSCREEN)*0.6)*1.6), (int)GetSystemMetrics(SM_CYSCREEN)*0.6,//윈도우의X,Y크기
		NULL,//(윈도우내부에윈도우를생성하고싶은경우부모윈도우의핸들지정)
		(HMENU)NULL,//윈도우상에서사용할메뉴의핸들지정
		hInstance,//이윈도우프로그램의핸들
		NULL);//여러개윈도우를생성할떄고유의파라미터를송출
	//(E)스마트폰Register 윈도우 생성

	//(S)Register 윈도우 생성
	WndClass.hbrBackground = CreateSolidBrush(RGB(240, 240, 240));//윈도우 기본색상
	WndClass.lpfnWndProc = WndProc_Register_USB;
	WndClass.lpszClassName = TEXT("USBRegister");
	RegisterClass(&WndClass);	//지금까지 '윈도우 클래스 생성' 에서 작성한 설정을 마치고 등록한다.

	hWnd_Register_USB = CreateWindow(
		L"USBRegister",//생성하고자하는윈도우를의미하는문자열
		IpszClass,//타이틀바에보여물문자열
		WS_OVERLAPPEDWINDOW,//만들고자하는윈도우의형태
		CW_USEDEFAULT, CW_USEDEFAULT,//윈도우의X,Y좌표
		(int)((GetSystemMetrics(SM_CYSCREEN)*0.6)*1.6), (int)GetSystemMetrics(SM_CYSCREEN)*0.6,//윈도우의X,Y크기
		NULL,//(윈도우내부에윈도우를생성하고싶은경우부모윈도우의핸들지정)
		(HMENU)NULL,//윈도우상에서사용할메뉴의핸들지정
		hInstance,//이윈도우프로그램의핸들
		NULL);//여러개윈도우를생성할떄고유의파라미터를송출
	//(E)Register 윈도우 생성


	//(S)트레이쉘생성
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hWnd_Main;
	nid.uID = 0;
	nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	nid.uCallbackMessage = TRAY_NOTIFY;
	nid.hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_ICON1));
	lstrcpy(nid.szTip, L"Guardian");
	Shell_NotifyIcon(NIM_ADD, &nid);//아이콘설정을쉘에저장
	//(E)트레이쉘생성

	//(S)GDI+활성화
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	if (GdiplusStartup(&gpToken, &gpsi, NULL) != Ok)
	{
		MessageBox(NULL, TEXT("GDI+ 라이브러리를 초기화할 수 없습니다."), TEXT("알림"), MB_OK);
		return 0;
	}
	//(E)GDI+활성화


	//(S)메시지루프
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	//(E)메시지루프
	GdiplusShutdown(gpToken);
	return (int)Message.wParam;
}

//메인 메시지루프
LRESULT CALLBACK WndProc_Main(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static HANDLE LockTimer;
	switch (iMessage)
	{
	case WM_CREATE:
		LockTimer = (HANDLE)SetTimer(hWnd, 1, 1000, NULL);	//잠금타이머 생성

		RegisterHotKey(hWnd, 0x0000, NULL, VK_F2);	//잠금
		RegisterHotKey(hWnd, 0x0001, NULL, VK_F3);	//잠금해제
		RegisterHotKey(hWnd, 0x0002, NULL, VK_F4);	//종료

		WSADATA wsaData;	//소켓 스타트업/클린업 자동화 구조체
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)	//윈도우 소켓 열기
			MessageBox(NULL, TEXT("WSAStartup() error!"), L" ", MB_OK);

		CreateThread(NULL, 0, Socket_MessageListener, NULL, 0, NULL);

		if(FRegReadInt(HKEY_CURRENT_USER, L"Fairy", L"Code", 0) == 0)
		{
			if (MessageBox(hWnd_Main, L"Guardian을 처음실행하셨습니다.\nUSB 등록을 실행합니다.", IpszClass, MB_YESNO))
			{
				PostMessage(hWnd, WM_COMMAND, IDC_TRAYMENU_REGISTER_USB, NULL);
			}
		}
		else //처음실행이 아님
		{
			//if (!KeyCheck() && !SmartUnlock) //테스트를 위해 시작시 잠그지 않음
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
				if (!KeyCheck() && !SmartUnlock)	//스마트폰이 잠금해제하였을 경우 키가 아닌 USB가 해제되어도 잠기지 않음(키인 USB는 잠김)
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
			SendMessage(hWnd_Register_SmartPhone, WM_PAINT, NULL, NULL);	//바로 그려주기
			break;
		case IDC_TRAYMENU_REGISTER_USB:
			ShowWindow(hWnd_Register_USB, SW_SHOW);
			SendMessage(hWnd_Register_USB, WM_PAINT, NULL, NULL);	//바로 그려주기
			break;

		case IDC_TRAYMENU_SETUP:

			break;

		case IDC_TRAYMENU_EXIT:
			if (MessageBox(hWnd_Main, L"정말로 종료할까요?\n종료하면 이 PC는 보호받지 못하게됩니다!", IpszClass, MB_YESNO) == IDYES)
				PostQuitMessage(0);
			break;
		}
		break;


	case WM_DESTROY:
		KillTimer(hWnd, 1);
		//(S)트레이쉘제거
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hWnd;
		nid.uID = 0;
		Shell_NotifyIcon(NIM_DELETE, &nid);
		//(E)트레이쉘제거
		UnregisterHotKey(hWnd, 0x0000);	//할당한 핫키 제거
		UnregisterHotKey(hWnd, 0x0001);	//할당한 핫키 제거
		UnregisterHotKey(hWnd, 0x0002);	//할당한 핫키 제거
		WSACleanup();
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//스마트폰 레지스터 메시지루프
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
		return 0;	//종료메시지 가로채기
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//USB 레지스터 메시지루프
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
					SendMessage(hWnd_Register_USB, WM_PAINT, NULL, NULL);	//바로 그려주기
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
							FString SerialNumber = DSerialNumber;	//멀티바이트->유니코드;
							FRegWriteInt(HKEY_CURRENT_USER, L"Fairy", L"Code", SerialNumber.FStringToInt());

							MessageBox(hWnd_Main, L"KEY가 재설정되었습니다!", IpszClass, NULL);
							ShowWindow(hWnd_Register_USB, SW_HIDE);
						}

					}
				}
			}
		}
		break;
	case WM_CLOSE:
		ShowWindow(hWnd, SW_HIDE);
		return 0;	//종료메시지 가로채기
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//UDP소켓 메시지루프
DWORD WINAPI Socket_MessageListener(LPVOID arg)
{
	//(Start)UDP소켓 활성화
	int strLen;
	SOCKADDR_IN servAdr;

	servSock = socket(PF_INET, SOCK_DGRAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(8787);

	bind(servSock, (SOCKADDR*)&servAdr, sizeof(servAdr));

	//(End)UDP소켓 활성화

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
FString형 데이터 123,456,789을
BYTE[0] = 123, BYTE[1] = 456, BYTE[2] = 789로 변환
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
	int Plain_size = SEED_CBC_Decrypt(Key, EmbedIV, Cyper_byteStr, Cyper_size, Plain_byteStr);//복호화

	return ByteToStrNum(Plain_byteStr, Plain_size);	//Byte->FString
}


void Socket_MessageProcessor(char* str)
{
	FString Block = str;
	FString Type = Block.Parsing(L"TYPE=", L":");
	if (Type == L"LOCK" && !KeyCheck())	//USB키가 연결되어있지 않아야함.
	{
		FString ID = Block.Parsing(L"ID=", L":");
		BYTE plain[128];
		StrNumToByte(GetKey(), plain);
		wchar_t wplain[128];
		GetID().FStringToWideChar(wplain);
		if (Decrypt(ID, plain).IsContain(wplain))
		{
			AutoMode = false;	//버튼으로 열기 자동잠금 끄기
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
			MessageBox(hWnd_Main, L"스마트폰이 등록되지 않았거나 옳지 않은 ID입니다!", L"Guardian", NULL);
		}
	}
	else if (Type == L"AUTOLOCK" && !KeyCheck())	//USB키가 연결되어있지 않아야함.
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
				AutoMode = true;	//자동잠금모드 신호 발생
				AutoLockTimer = 0;
				UnLock();
				sendto(servSock, "UNLOCK", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
			}
		}
		else if (Command == L"CLOCK")
		{
			AutoLockTimer++;

			if (AutoLockTimer > LOCKTIME && AutoMode==true)	//잠금시간이 지나고 자동잠금모드일 경우
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

			//키 복호화
			FString PlainKey = Decrypt(CyperKey, EmbedKey);

			//키 레지스트리에 저장
			if (!SetKey(PlainKey))
			{
				MessageBox(hWnd_Main, L"등록 실패!", L"Guardian", NULL);
				return;
			}

			//ID 복호화
			BYTE byteKey[256];
			StrNumToByte(PlainKey, byteKey);
			FString PlainID = Decrypt(CyperID, byteKey);

			//ID 레지스트리에 저장
			if (!SetID(PlainID))
			{
				MessageBox(hWnd_Main, L"등록 실패!", L"Guardian", NULL);
				return;
			}

			sendto(servSock, "REGIST", 6, 0, (SOCKADDR*)&clntAdr, clntAdrSz);
			MessageBox(hWnd_Main, L"스마트폰을 등록하였습니다.", L"Guardian", NULL);
		}
	}
}

void Lock()
{
	ShowWindow(FindWindow(L"Shell_TrayWnd", NULL), SW_HIDE);	//테스크바 HIDE
	SetLayeredWindowAttributes(hWnd_Main, NULL, 0, LWA_ALPHA);
	ShowWindow(hWnd_Main, SW_MAXIMIZE);
	SendMessage(hWnd_Main, WM_PAINT, NULL, NULL);	//PostMessage는 기다리지않고 진행하기 때문에 배경이 그려지기 전에 불투명화를 진행해버림

	for (int trans = 0; trans < 256; trans += 15)
	{
		SetLayeredWindowAttributes(hWnd_Main, NULL, trans, LWA_ALPHA);
		Sleep(15);
	}
	SetForegroundWindow(hWnd_Main);	//Z순서 변경
}

void UnLock()
{
	for (int trans = 255; trans > -1; trans -= 15)
	{
		SetLayeredWindowAttributes(hWnd_Main, NULL, trans, LWA_ALPHA);
		Sleep(15);
	}
	ShowWindow(hWnd_Main, SW_HIDE);

	ShowWindow(FindWindow(L"Shell_TrayWnd", NULL), SW_SHOW);	//테스크바 HIDE
}

void Draw_Main(HDC hdc)
{
	//PNG로드
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
	//PNG로드
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
	//PNG로드
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

	Font F(L"한컴 윤고딕 230", height/15, FontStyleBold, UnitPixel);	//폰트설정
	PointF P(10.0f, 10.0f);
	SolidBrush B(Color(0, 0, 0));
	Graphics G(hdc);

	G.SetTextRenderingHint((TextRenderingHint)4);	//안티엘리어싱 최대

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
	G.DrawString(L"저장하기", -1, &F, P, &B);
}