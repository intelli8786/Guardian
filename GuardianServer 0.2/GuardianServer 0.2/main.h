#include <Windows.h>
#include "resource.h"
#include "FString.h"
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus")
#pragma comment(lib,"Ws2_32.lib")	//윈소켓 라이브러리
#define TRAY_NOTIFY (WM_APP + 100)
#define BUF_SIZE 2048
#include "KISA_SEED_CBC.h"
#include <Dbt.h>//장치(드라이브) 체크 헤더

//함수 인터페이스
LRESULT CALLBACK WndProc_Main(HWND, UINT, WPARAM, LPARAM);//메시지루프함수선언
LRESULT CALLBACK WndProc_Register_SmartPhone(HWND, UINT, WPARAM, LPARAM);//메시지루프함수선언
LRESULT CALLBACK WndProc_Register_USB(HWND, UINT, WPARAM, LPARAM);//메시지루프함수선언
DWORD WINAPI Socket_MessageListener(LPVOID arg);
void Socket_MessageProcessor(char* str);
void Lock();
void UnLock();
void Draw_Main(HDC hdc);
void Draw_Register_SmartPhone(HDC hdc);
void Draw_Register_USB(HDC hdc);
//전역변수
HINSTANCE g_hInst;//윈도우인스턴스핸들을전역변수화하기위한변수
LPCTSTR IpszClass = TEXT("Guardian"); //프로젝트의이름
NOTIFYICONDATA nid;
HWND hWnd_Main, hWnd_Register_SmartPhone, hWnd_Register_USB;
SOCKET servSock;
SOCKADDR_IN clntAdr;
int clntAdrSz;
BYTE EmbedKey[16] = { 0x088, 0x0e3, 0x04f, 0x08f, 0x008, 0x017, 0x079, 0x0f1, 0x0e9, 0x0f3, 0x094, 0x037, 0x00a, 0x0d4, 0x005, 0x089 };
BYTE EmbedIV[16] = { 0x026, 0x08d, 0x066, 0x0a7, 0x035, 0x0a8, 0x01a, 0x081, 0x06f, 0x0ba, 0x0d9, 0x0fa, 0x036, 0x016, 0x025, 0x001 };
int AutoLockTimer = 0;
#define LOCKTIME 5 //시간만큼 경과 후 메시지가 없으면 LOCK
bool AutoMode = false;	//자동잠금모드
bool SmartUnlock = false;	//스마트폰이 잠금 풀었을 경우 USB해제시 무시
int driveNum = 0;

UINT FRegReadInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, INT nDefault)
{
	HKEY key;
	DWORD dwDisp;
	UINT Result;
	DWORD Size;

	if (RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_READ, NULL, &key, &dwDisp) != ERROR_SUCCESS)
		return 0;
	Size = sizeof(LONG);
	if (RegQueryValueEx(key, lpValue, 0, NULL, (LPBYTE)&Result, &Size) != ERROR_SUCCESS)
		Result = nDefault;
	RegCloseKey(key);
	return Result;
}

BOOL FRegWriteInt(HKEY hKey, LPCTSTR lpKey, LPCTSTR lpValue, UINT nData)
{
	HKEY key;
	DWORD dwDisp;
	if (RegCreateKeyEx(hKey, lpKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &key, &dwDisp) != ERROR_SUCCESS)
	{
		return FALSE;
	}

	if (RegSetValueEx(key, lpValue, 0, REG_DWORD, (LPBYTE)&nData, sizeof(UINT)) != ERROR_SUCCESS)
	{
		return FALSE;
	}
	RegCloseKey(key);

	return TRUE;
}

BOOL SetID(FString str)
{
	for (int i = 0; i < 14; i++)	//타임스템프 제외
	{
		FString name = "ID";
		name += (i + 1);
		if (FRegWriteInt(HKEY_CURRENT_USER, L"Fairy", name, str.Tokenizing(L",").FStringToInt()) == FALSE)
			return FALSE;
	}
	return TRUE;
}
FString GetID()
{
	FString strTemp;
	for (int i = 0; i < 14; i++)	//타임스템프 제외
	{
		FString name = "ID";
		name += (i + 1);
		strTemp += FRegReadInt(HKEY_CURRENT_USER, L"Fairy", name, 0);
		strTemp += ",";
	}
	
	return strTemp;

}

BOOL SetKey(FString str)
{
	for (int i = 0; i < 16; i++)
	{
		FString name = "KEY";
		name += (i + 1);
		if (FRegWriteInt(HKEY_CURRENT_USER, L"Fairy", name, str.Tokenizing(L",").FStringToInt()) == FALSE)
			return FALSE;
	}
	return TRUE;
}
FString GetKey()
{
	FString strTemp;
	for (int i = 0; i < 16; i++)
	{
		FString name = "KEY";
		name += (i + 1);
		strTemp += FRegReadInt(HKEY_CURRENT_USER, L"Fairy", name, 0);
		strTemp += ",";
	}

	return strTemp;
}
bool KeyCheck()
{
	wchar_t driveList[256];
	int driveNum = GetLogicalDriveStrings(256, driveList) / 4;
	for (int i = 0; i < driveNum; i++)
	{
		driveList[3 + i * 4] = ',';
	}
	FString Drives = driveList;

	for (int i = 0; i < driveNum; i++)
	{
		DWORD DSerialNumber;
		FString SerialNumber;
		if (GetVolumeInformation(Drives.Tokenizing(L","), NULL, NULL, &DSerialNumber, NULL, NULL, NULL, NULL))
		{
			SerialNumber = DSerialNumber;	//멀티바이트->유니코드;
			if (SerialNumber == FRegReadInt(HKEY_CURRENT_USER, L"Fairy", L"Code", 0))
			{
				return true;
			}
		}
	}
	return false;
}


FString GetDrives()
{
	wchar_t driveList[256];
	int driveNum = GetLogicalDriveStrings(256, driveList) / 4;
	for (int i = 0; i < driveNum; i++)
	{
		driveList[3 + i * 4] = ',';
	}
	FString Drives = driveList;
	return Drives;
}

class Register_Icon
{
public:
	RECT position;
	bool selected = false;
	FString DriveName;
}; Register_Icon USB_Icon[20]; Register_Icon Save_Icon;