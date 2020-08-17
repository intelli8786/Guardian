
/*
1.동적할당을 위해 사용할 포인터 변수는 반드시 NULL로 초기화 해준다.
*/

#ifndef FSTRING_H	//중복정의 방지
#define FSTRING_H

#define F_ANSICODE 0
#define F_UTF8 1
#define F_UNICODE 2


//(S)전역함수
template <typename T>
static int FS_Length(T *str)
{
	int length = 0;
	if (str == NULL)	//NULL or nullptr
	{
		//널포인터인 경우 아무 작업도 하지 않고 0을 반환
	}
	else
	{
		while (*str++ != NULL)
		{
			length++;
		}
	}

	return length;
}
static int FS_Length(int num, int radix)	//음수일 경우 '-'기호를 포함한 길이를 반환한다.
{
	int length = 0;
	bool negative = false;	//음수체크

	if (num < 0)//음수일 경우
	{
		num *= -1;	//양수화
		negative = true;
	}
	while (true)
	{
		length++;
		num /= radix;
		if (num == 0)
		{
			break;
		}
	}

	return length + negative;
}
template <typename T1, typename T2>
void FS_Copy(T1 *str1, T2 *str2)
{
	if (str1 == NULL)	//str1이 할당되지 않은 경우
	{
		//MessageBox(NULL, L"복사할 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
	}
	else
	{
		if (str2 == NULL)	//NULL or nullptr
		{
			//복사할 문자열이 널포인터인 경우 str1을 비움
			*str1 = NULL;
		}
		else
		{
			while (*str2 != NULL)
			{
				*str1++ = *str2++;
			}
			*str1 = NULL;
		}
	}
}
template <typename T1, typename T2>
void FS_Copy(T1 *str1, T2 *str2, int start, int num)
{
	if (str1 == NULL)	//str1이 할당되지 않은 경우
	{
		//MessageBox(NULL, L"복사할 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
	}
	else
	{
		if (str2 == NULL)	//NULL or nullptr
		{
			//복사할 문자열이 널포인터인 경우 str1을 비움
			*str1 = NULL;
		}
		else
		{
			if (start < 0)	//시작값이 0보다 작을 경우
			{
				start = 0;	//0부터 시작
			}
			if (num > FS_Length(str2))	//복사할 값이 str2의 길이보다 클 경우
			{
				num = FS_Length(str2);//str2길이만큼만 복사
			}

			for (int i = 0; i < num; i++)
			{
				*str1++ = *((str2++) + start);
			}
			*str1 = NULL;
		}
	}
}
template <typename T1, typename T2>
void FS_Catenate(T1 *str1, T2 *str2)
{
	if (str1 == NULL)
	{
		//MessageBox(NULL, L"이어질 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
	}
	else if (str2 == NULL)
	{
		//이을 변수가 비어있으므로 str1을 변화시키지 않음
	}
	else
	{
		while (*str1 != NULL)
			str1++;

		while (*str2 != NULL)
		{
			*str1++ = *str2++;
		}
		*str1 = NULL;
	}
}
template <typename T1, typename T2>
bool FS_Compare(T1 *str1, T2 *str2)
{
	if (str1 == NULL || str2 == NULL)
	{
		if (str1 == str2)	//둘 다 NULL인 경우
		{
			return true;
		}
		else if (str1 != NULL)	//비할당변수 = 첫값이NULL인변수
		{
			if (*str1 == NULL)
				return true;
		}
		else if (str2 != NULL)	//비할당변수 = 첫값이NULL인변수
		{
			if (*str2 == NULL)
				return true;
		}
		else  //둘중 하나만 NULL인 경우
		{
			return false;
		}
	}
	else
	{
		while (*str1++ == *str2++)
		{
			if (*str1 == NULL && *str2 == NULL)	//마지막 널까지 같다면
			{
				return true;
			}
		}
	}
	return false;
}
template <typename T>
void FS_Trim(T *str, int trim, bool direction)	//direction 0 왼쪽부터 1 오른쪽부터
{
	if (trim > 0 && str != NULL)
	{
		int length = FS_Length(str);
		if (length > trim)	//문자열 길이가 지우려는 수보다 작으며 양수임
		{
			if (!direction)	//왼쪽Trim일 경우
			{
				for (int i = 0; i < length - trim; i++)
				{
					str[i] = str[i + trim];
				}
			}
			str[length - trim] = NULL;
		}
		else	//문자열 길이가 지우려는 수보다 큼
		{
			*str = NULL;	//첫번째 문자에 NULL 대입
		}
	}
}
template <typename T1, typename T2>
int FS_Contain(T1 *str1, T2 *str2, int start)
{
	if (str1 == NULL)	//str1이 할당되지않음
	{
		return -1;
	}
	else if (str2 == NULL)	//str2가 할당되지않음
	{
		return -1;
	}
	else
	{
		int length1 = FS_Length(str1);
		int length2 = FS_Length(str2);
		int check;

		if (start < 0)
			start = 0;

		for (int i = start; i < length1 - length2 + 1; i++)
		{
			check = 0;
			for (int j = 0; j < length2; j++)
			{
				if (str1[i + check] == str2[j])//문자가 같지 않을 경우
				{
					check++;
					if (j == length2 - 1)	//j가 마지막까지 브레이크없이 도달
					{
						return i;
					}
				}
				else
				{
					break;
				}
			}
		}
	}
	return -1;
}
//(E)전역함수

class FString
{
public:
	wchar_t *m_FString = NULL;

	/*
	<F_Length>
	유니코드형 문자열의 길이 반환함수
	NULL을 제외한 길이
	*/
	template <typename T>
	int F_Length(T *str)
	{
		int length = 0;
		if (str == NULL)	//NULL or nullptr
		{
			//널포인터인 경우 아무 작업도 하지 않고 0을 반환
		}
		else
		{
			while (*str++ != NULL)
			{
				length++;
			}
		}

		return length;
	}
	int F_Length(int num, int radix)	//음수일 경우 '-'기호를 포함한 길이를 반환한다.
	{
		int length = 0;
		bool negative = false;	//음수체크

		if (num < 0)//음수일 경우
		{
			num *= -1;	//양수화
			negative = true;
		}
		while (true)
		{
			length++;
			num /= radix;
			if (num == 0)
			{
				break;
			}
		}

		return length + negative;
	}

	/*
	<F_Copy>
	유니코드형 문자열을 복사
	str2를 str1로 복사한다.
	또는 str2를 str1로 start번지부터 num수 만큼 복사
	*/
	template <typename T1, typename T2>
	void F_Copy(T1 *str1, T2 *str2)
	{
		if (str1 == NULL)	//str1이 할당되지 않은 경우
		{
			//MessageBox(NULL, L"복사할 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
		}
		else
		{
			if (str2 == NULL)	//NULL or nullptr
			{
				//복사할 문자열이 널포인터인 경우 str1을 비움
				*str1 = NULL;
			}
			else
			{
				while (*str2 != NULL)
				{
					*str1++ = *str2++;
				}
				*str1 = NULL;
			}
		}
	}
	template <typename T1, typename T2>
	void F_Copy(T1 *str1, T2 *str2, int start, int num)
	{
		if (str1 == NULL)	//str1이 할당되지 않은 경우
		{
			//MessageBox(NULL, L"복사할 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
		}
		else
		{
			if (str2 == NULL)	//NULL or nullptr
			{
				//복사할 문자열이 널포인터인 경우 str1을 비움
				*str1 = NULL;
			}
			else
			{
				if (start < 0)	//시작값이 0보다 작을 경우
				{
					start = 0;	//0부터 시작
				}
				if (num>F_Length(str2))	//복사할 값이 str2의 길이보다 클 경우
				{
					num = F_Length(str2);//str2길이만큼만 복사
				}

				for (int i = 0; i < num; i++)
				{
					*str1++ = *((str2++) + start);
				}
				*str1 = NULL;
			}
		}
	}

	/*
	<F_Catenate>
	유니코드형 문자열 연결
	str2를 str1뒤에 연결한다.
	*/
	template <typename T1, typename T2>
	void F_Catenate(T1 *str1, T2 *str2)
	{
		if (str1 == NULL)
		{
			//MessageBox(NULL, L"이어질 변수가 이상해요!\n아마 할당이 안된것같아요.", L" ", NULL);
		}
		else if (str2 == NULL)
		{
			//이을 변수가 비어있으므로 str1을 변화시키지 않음
		}
		else
		{
			while (*str1 != NULL)
				str1++;

			while (*str2 != NULL)
			{
				*str1++ = *str2++;
			}
			*str1 = NULL;
		}
	}

	/*
	<F_Compare>
	문자열비교
	할당되지않은 변수와 첫번째 값이 NULL포인터인 변수는 동일하게 비어있는 상태로 한다. 그러므로 (NULL == L"") 는 true이다.
	*/
	template <typename T1, typename T2>
	bool F_Compare(T1 *str1, T2 *str2)
	{
		if (str1 == NULL || str2 == NULL)
		{
			if (str1 == str2)	//둘 다 NULL인 경우
			{
				return true;
			}
			else if (str1 != NULL)	//비할당변수 = 첫값이NULL인변수
			{
				if (*str1 == NULL)
					return true;
			}
			else if (str2 != NULL)	//비할당변수 = 첫값이NULL인변수
			{
				if (*str2 == NULL)
					return true;
			}
			else  //둘중 하나만 NULL인 경우
			{
				return false;
			}
		}
		else
		{
			while (*str1++ == *str2++)
			{
				if (*str1 == NULL && *str2 == NULL)	//마지막 널까지 같다면
				{
					return true;
				}
			}
		}
		return false;
	}

	/*
	<F_Trim>
	문자열소거
	세번째 인자가 false일 경우 왼쪽부터, true일 경우 오른쪽부터 trim 수 만큼 소거한다.
	*/
	template <typename T>
	void F_Trim(T *str, int trim, bool direction)	//direction 0 왼쪽부터 1 오른쪽부터
	{
		if (trim > 0 && str != NULL)
		{
			int length = F_Length(str);
			if (length > trim)	//문자열 길이가 지우려는 수보다 작으며 양수임
			{
				if (!direction)	//왼쪽Trim일 경우
				{
					for (int i = 0; i < length - trim; i++)
					{
						str[i] = str[i + trim];
					}
				}
				str[length - trim] = NULL;
			}
			else	//문자열 길이가 지우려는 수보다 큼
			{
				*str = NULL;	//첫번째 문자에 NULL 대입
			}
		}
	}

	/*
	<F_Contain>
	str1문자열에 str2문자열이 포함되는 번지수를 반환
	0부터 시작
	*/
	template <typename T1, typename T2>
	int F_Contain(T1 *str1, T2 *str2, int start)
	{
		if (str1 == NULL)	//str1이 할당되지않음
		{
			return -1;
		}
		else if (str2 == NULL)	//str2가 할당되지않음
		{
			return -1;
		}
		else
		{
			int length1 = F_Length(str1);
			int length2 = F_Length(str2);
			int check;

			if (start < 0)
				start = 0;

			for (int i = start; i < length1 - length2 + 1; i++)
			{
				check = 0;
				for (int j = 0; j < length2; j++)
				{
					if (str1[i + check] == str2[j])//문자가 같지 않을 경우
					{
						check++;
						if (j == length2 - 1)	//j가 마지막까지 브레이크없이 도달
						{
							return i;
						}
					}
					else
					{
						break;
					}
				}
			}
		}
		return -1;
	}

	/*
	<F_Allocation>
	동적 할당&재할당
	*/
	template <typename T>
	void F_Allocation(T *& str, int size)
	{
		if (str == NULL)	//할당할 변수가 아직 할당되지않은 경우(재할당 할 필요가 없는 경우)
		{
			if (size > 1)
			{
				str = new T[size];
				*str = NULL;	//첫문자를 NULL로 할당
			}
		}
		else	//재할당 할 필요가 있는 경우
		{
			delete[] str;
			str = NULL;

			if (size > 1)
			{
				str = new T[size];
				*str = NULL;	//첫문자를 NULL로 할당
			}
		}
	}

	/*
	<F_MultibyteToWideChar>
	멀티바이트형 코드를 유니코드로 변환
	*/
	template <typename T>
	wchar_t* F_MultibyteToWideChar(T *str, int code)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//멀티스레드 사용시 static 변수에 대한 뮤텍스 필요
		WaitForSingleObject(hMutex, INFINITE);	//사용하고있다면 무제한 대기
		static wchar_t *strW = NULL;

		if (str == NULL || *str == NULL)
		{

		}
		else
		{
			int length;
			bool negative = false;	//음수체크
			if (strW != NULL)	//할당할 변수가 널포인터가 아닌경우
			{
				delete[] strW;	//할당한 크기보다 많은 데이터가 들어있을 경우 delete함수호출시 에러발생
				strW = NULL;
			}

			if (code == F_ANSICODE)	//Ansi
			{
				length = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, NULL, NULL);
				strW = new wchar_t[length + 1];
				MultiByteToWideChar(CP_ACP, 0, str, -1, strW, length); //char To TCHAR 변환
			}
			else if (code == F_UTF8)	//UTF-8
			{
				length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, NULL);
				strW = new wchar_t[length + 1];
				MultiByteToWideChar(CP_UTF8, 0, str, -1, strW, length); //char To TCHAR 변환
			}
		}

		ReleaseMutex(hMutex);
		return strW;
	}

	/*
	<F_WideCharToMultibyte>
	유니코드를 멀티바이트형 코드로 변환
	code 0은 안시코드 1은 UTF-8코드
	*/
	template <typename T>
	char* F_WideCharToMultibyte(T *str, int code)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//멀티스레드 사용시 static 변수에 대한 뮤텍스 필요
		WaitForSingleObject(hMutex, INFINITE);	//사용하고있다면 무제한 대기
		static char *strM = NULL;

		if (str == NULL || *str == NULL)
		{

		}
		else
		{
			int length;
			bool negative = false;	//음수체크
			if (strM != NULL)	//할당할 변수가 널포인터가 아닌경우
			{
				delete[] strM;	//할당한 크기보다 많은 데이터가 들어있을 경우 delete함수호출시 에러발생
				strM = NULL;
			}

			if (code == F_ANSICODE)	//Ansi
			{
				length = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, NULL, NULL, NULL);
				strM = new char[length + 1];
				WideCharToMultiByte(CP_ACP, 0, str, -1, strM, length, NULL, NULL);
			}
			else if (code == F_UTF8)	//UTF-8
			{
				length = WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, NULL, NULL, NULL);
				strM = new char[length + 1];
				WideCharToMultiByte(CP_UTF8, 0, str, -1, strM, length, NULL, NULL);
			}
		}

		ReleaseMutex(hMutex);
		return strM;
	}
	/*
	<FMultibyteToWideChar>
	Int형 데이터를 유니코드형으로 변환하며, 주소를 static형으로 보관 및 다음번 호출까지 데이터는 힙에 저장된다.
	*/
	wchar_t* F_IntToWideChar(int num, int radix)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//멀티스레드 사용시 static 변수에 대한 뮤텍스 필요
		WaitForSingleObject(hMutex, INFINITE);	//사용하고있다면 무제한 대기
		static wchar_t *strN;

		bool negative = false;	//음수체크
		int length = F_Length(num, radix);	//'-'기호를 포함한 길이

		if (num < 0)//음수일 경우
		{
			num *= -1;	//양수화
			negative = true;
		}
		if (strN != NULL)	//할당할 변수가 널포인터가 아닌경우
		{
			delete[] strN;	//할당한 크기보다 많은 데이터가 들어있을 경우 delete함수호출시 에러발생
			strN = NULL;
		}
		strN = new wchar_t[length + 1];
		if (negative == true)	//음수체크
		{
			strN[0] = '-';
		}

		int rest = 0;	//나머지
		for (int i = 1; i < length - negative + 1; i++)
		{
			rest = num % radix;
			num /= radix;
			if (rest < 10)	//나머지가 10이하(10진수 이하)
			{
				strN[length - i] = rest + L'0';
			}
			else	//10진수 이상
			{
				strN[length - i] = rest % 10 + L'a';
			}
		}
		strN[length] = NULL;

		ReleaseMutex(hMutex);
		return strN;
	}

	/*
	<FWideCharToInt>
	유니코드형 데이터를 Int형으로 변환해 반환한다.
	*/
	int F_WideCharToInt(wchar_t *str)
	{
		int result = 0;
		if (str == NULL)	//str1이 할당되지않음
		{
			return -1;
		}
		else
		{
			bool negative = false;
			if (str[0] == L'-')
			{
				str[0] = L'0';
				negative = true;
			}
			int length = F_Length(str);
			for (int i = 0; i < length; i++)
			{
				result = result * 10 + (str[i] - L'0');
			}
			if (negative == true)
				result *= -1;
		}
		return result;
	}
public:
	/*
	생성자가 호출되었을 때는 변수가 할당되어있지 않으므로 NULL포인터가 넘어올 경우 m_FString을 비우지 않아도 됨.
	*/
	//(S) 생성자
	FString()
	{

	}
	FString(wchar_t *str)
	{

		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, str);
	}
	FString(const wchar_t *str)
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, str);
	}
	FString(FString &FStr)
	{
		F_Allocation(m_FString, F_Length(FStr.m_FString) + 1);
		F_Copy(m_FString, FStr.m_FString);
	}
	FString(char *str)
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
	}
	FString(const char *str)
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
	}
	FString(int num)
	{
		F_Allocation(m_FString, F_Length(num, 10) + 1);
		F_Copy(m_FString, F_IntToWideChar(num, 10));
	}
	~FString()
	{
		F_Allocation(m_FString, 0);
	}
	//(E) 생성자

	//(S) 연산자 오버로딩
	/*
	<LPCWSTR연산자 오버로딩>
	LPCWSTR(wchar_t*)형 타입캐스팅
	*/
	operator LPCWSTR()	//객체이름을 LPCWSTR로 타입캐스팅할 때 이를 반환
	{					//세번째 문자인 C는 Constance이며, 상수로서 변경불가능
		return m_FString;
	}

	/*
	< = 연산자 오버로딩>
	str를 현재 객체에 대입한 후 현재객체를 반환
	*/
	FString &operator = (wchar_t* str)
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, str);
		return *this;
	}
	FString &operator = (const wchar_t* str)
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, str);
		return *this;
	}
	FString &operator = (FString &FStr)
	{
		F_Allocation(m_FString, F_Length(FStr.m_FString) + 1);
		F_Copy(m_FString, FStr.m_FString);
		return *this;
	}
	FString &operator = (char* str)		//멀티바이트->유니코드 변환할당
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
		return *this;
	}
	FString &operator = (const char* str)	//멀티바이트->유니코드 변환할당
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
		return *this;
	}
	FString &operator = (int num)		//멀티바이트->유니코드 변환할당
	{
		F_Allocation(m_FString, F_Length(num, 10) + 1);
		F_Copy(m_FString, F_IntToWideChar(num, 10));
		return *this;
	}

	/*
	< + 연산자 오버로딩>
	str1과 str2를 연결한 후 FString객체를 반환
	*/
	FString operator + (wchar_t* str)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, str);
		return strTemp;
	}
	FString operator + (const wchar_t* str)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, str);
		return strTemp;
	}
	FString operator + (FString &FStr)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(FStr.m_FString);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, FStr.m_FString);

		return strTemp;
	}
	FString operator + (char* str)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, F_MultibyteToWideChar(str, 0));
		return strTemp;
	}
	FString operator + (const char* str)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, F_MultibyteToWideChar(str, 0));
		return strTemp;
	}
	FString operator + (int num)
	{
		FString strTemp;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(num, 10);

		F_Allocation(strTemp.m_FString, length1 + length2 + 1);
		F_Copy(strTemp.m_FString, m_FString);
		F_Catenate(strTemp.m_FString, F_IntToWideChar(num, 10));
		return strTemp;
	}

	/*
	< += 연산자 오버로딩>
	str1과 str2를 연결한 후 FString객체에 저장 후 주소 반환
	*/
	FString& operator += (wchar_t *str)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, str);

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}
	FString& operator += (const wchar_t *str)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, str);

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}
	FString& operator += (FString &FStr)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(FStr.m_FString);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, FStr.m_FString);

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}
	FString& operator += (char *str)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, F_MultibyteToWideChar(str, 0));

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}
	FString& operator += (const char *str)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(str);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, F_MultibyteToWideChar(str, 0));

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}
	FString& operator += (int num)
	{
		wchar_t *strTemp = NULL;
		int length1 = F_Length(m_FString);
		int length2 = F_Length(num, 10);

		F_Allocation(strTemp, length1 + length2 + 1);
		F_Copy(strTemp, m_FString);
		F_Catenate(strTemp, F_IntToWideChar(num, 10));

		F_Allocation(m_FString, length1 + length2 + 1);
		F_Copy(m_FString, strTemp);

		F_Allocation(strTemp, 0);
		return *this;
	}

	/*
	< == 연산자 오버로딩>
	str1과 str2를 비교한 후 동일유무를 반환
	*/
	bool operator == (wchar_t *str)
	{
		return F_Compare(m_FString, str);
	}
	bool operator == (const wchar_t *str)
	{
		return F_Compare(m_FString, str);
	}
	bool operator == (FString &FStr)
	{
		return F_Compare(m_FString, FStr.m_FString);
	}
	bool operator == (char *str)
	{
		return F_Compare(m_FString, F_MultibyteToWideChar(str, 0));
	}
	bool operator == (const char *str)
	{
		return F_Compare(m_FString, F_MultibyteToWideChar(str, 0));
	}
	bool operator == (int num)
	{
		return F_Compare(m_FString, F_IntToWideChar(num, 10));
	}

	/*
	< != 연산자 오버로딩>
	str1과 str2를 비교한 후 동일유무를 역반환
	*/
	bool operator != (wchar_t *str)
	{
		return !F_Compare(m_FString, str);
	}
	bool operator != (const wchar_t *str)
	{
		return !F_Compare(m_FString, str);
	}
	bool operator != (FString &FStr)
	{
		return !F_Compare(m_FString, FStr.m_FString);
	}
	bool operator != (char *str)
	{
		return !F_Compare(m_FString, F_MultibyteToWideChar(str, 0));
	}
	bool operator != (const char *str)
	{
		return !F_Compare(m_FString, F_MultibyteToWideChar(str, 0));
	}
	bool operator != (int num)
	{
		return !F_Compare(m_FString, F_IntToWideChar(num, 10));
	}

	/*
	< <,> 연산자 오버로딩>
	str1과 str2의 문자열 길이를 비교 후 참 거짓 반환
	*/
	bool operator < (wchar_t *str)
	{
		return F_Length(m_FString) < F_Length(str) ? true : false;
	}
	bool operator < (const wchar_t *str)
	{
		return F_Length(m_FString) < F_Length(str) ? true : false;
	}
	bool operator < (FString &FStr)
	{
		return F_Length(m_FString) < F_Length(FStr.m_FString) ? true : false;
	}
	bool operator < (char *str)
	{
		return F_Length(m_FString) < F_Length(str) ? true : false;
	}
	bool operator < (const char *str)
	{
		return F_Length(m_FString) < F_Length(str) ? true : false;
	}
	bool operator < (int num)
	{
		return F_Length(m_FString) < F_Length(num, 10) ? true : false;
	}
	bool operator > (wchar_t *str)
	{
		return F_Length(m_FString) > F_Length(str) ? true : false;
	}
	bool operator > (const wchar_t *str)
	{
		return F_Length(m_FString) > F_Length(str) ? true : false;
	}
	bool operator > (FString &FStr)
	{
		return F_Length(m_FString) > F_Length(FStr.m_FString) ? true : false;
	}
	bool operator > (char *str)
	{
		return F_Length(m_FString) > F_Length(str) ? true : false;
	}
	bool operator > (const char *str)
	{
		return F_Length(m_FString) > F_Length(str) ? true : false;
	}
	bool operator > (int num)
	{
		return F_Length(m_FString) > F_Length(num, 10) ? true : false;
	}

	/*
	< <=,>= 연산자 오버로딩>
	str1과 str2문자열이 동일하면 참, 그렇지 않다면 길이를 따져 크고 작음의 참 거짓을 판별한다.
	*/
	bool operator <= (wchar_t *str)
	{
		return (F_Length(m_FString) <= F_Length(str)) ? true : false;
	}
	bool operator <= (const wchar_t *str)
	{
		return (F_Length(m_FString) <= F_Length(str)) ? true : false;
	}
	bool operator <= (FString &FStr)
	{
		return (F_Length(m_FString) <= F_Length(FStr.m_FString)) ? true : false;
	}
	bool operator <= (char *str)
	{
		return (F_Length(m_FString) <= F_Length(str)) ? true : false;
	}
	bool operator <= (const char *str)
	{
		return (F_Length(m_FString) <= F_Length(str)) ? true : false;
	}
	bool operator <= (int num)
	{
		return (F_Length(m_FString) <= F_Length(num, 10)) ? true : false;
	}
	bool operator >= (wchar_t *str)
	{
		return (F_Length(m_FString) >= F_Length(str)) ? true : false;
	}
	bool operator >= (const wchar_t *str)
	{
		return (F_Length(m_FString) >= F_Length(str)) ? true : false;
	}
	bool operator >= (FString &FStr)
	{
		return (F_Length(m_FString) >= F_Length(FStr.m_FString)) ? true : false;
	}
	bool operator >= (char *str)
	{
		return (F_Length(m_FString) >= F_Length(str)) ? true : false;
	}
	bool operator >= (const char *str)
	{
		return (F_Length(m_FString) >= F_Length(str)) ? true : false;
	}
	bool operator >= (int num)
	{
		return (F_Length(m_FString) >= F_Length(num, 10)) ? true : false;
	}

	/*
	< [] 연산자 오버로딩>
	배열첨자를 가져와 해당 번지의 유니코드형 문자를 반환
	*/
	wchar_t operator[](int num)
	{
		return *(m_FString + num);
	}
	//(E) 연산자 오버로딩

	//(S) 멤버함수
	/*
	<Append>
	str1과 str2를 연결한 후 FString객체에 저장 후 주소 반환
	*/
	FString& Append(wchar_t *str)
	{
		return *this += str;
	}
	FString& Append(const wchar_t *str)
	{
		return *this += str;
	}
	FString& Append(char *str)
	{
		return *this += str;
	}
	FString& Append(FString &FStr)
	{
		return *this += FStr;
	}
	FString& Append(const char *str)
	{
		return *this += str;
	}
	FString& Append(int num)
	{
		return *this += num;
	}

	/*
	<Trim~>
	인자의 수만큼 왼쪽, 오른쪽 자른 후 주소 반환
	*/
	FString& TrimLeft(int trim)
	{
		F_Trim(m_FString, trim, false);
		int length = F_Length(m_FString);
		wchar_t *strTemp = NULL;

		F_Allocation(strTemp, length + 1);
		F_Copy(strTemp, m_FString);
		F_Allocation(m_FString, length + 1);
		F_Copy(m_FString, strTemp);
		F_Allocation(strTemp, 0);

		return *this;
	}
	FString& TrimRight(int trim)
	{
		F_Trim(m_FString, trim, true);
		int length = F_Length(m_FString);
		wchar_t *strTemp = NULL;

		F_Allocation(strTemp, length + 1);
		F_Copy(strTemp, m_FString);
		F_Allocation(m_FString, length + 1);
		F_Copy(m_FString, strTemp);
		F_Allocation(strTemp, 0);

		return *this;
	}

	/*
	<IsCotains>
	객체의 문자열과 비교하여 모든 인수 중 일부분이 일치하는것이 하나라도 있다면 true를 반환
	*/
	bool IsContains(int count, ...)	//가변인수의 갯수,비교할 문자열 배열의 포인터,가변인수
	{
		bool result = false;	//true : 일치하는문자열 있음, false : 일치하는 문자열 없음
		if (count == 0)	//카운트가 0일 경우
		{
			//연산하려는 값이 아무것도 없으므로 연산하지 않음
		}
		else if (m_FString == NULL)	//현재 객체가 비어있는 경우
		{
			//연산하려는 값이 아무것도 없으므로 연산하지 않음
		}
		else
		{
			va_list ap;
			va_start(ap, count);	//고정인수+번지=시작지점이므로, count다음인자부터 차례로 가져옴.
			for (int i = 0; i < count; i++)
			{
				if (F_Contain(m_FString, va_arg(ap, wchar_t*), 0) != -1)	//결과를 찾지 못한다면 NULL값이 반환됨.
				{
					result = true;
				}
			}
			va_end(ap);
		}
		return result;
	}

	/*
	<IsEquals>
	객체의 문자열과 비교하여 모든 인수 중 일치하는것이 하나라도 있다면 true를 반환
	*/
	bool IsEquals(int count, ...)	//가변인수의 갯수,비교할 문자열 배열의 포인터,가변인수
	{
		bool result = false;	//true : 일치하는문자열 있음, false : 일치하는 문자열 없음
		if (count == 0)	//카운트가 0일 경우
		{
			//연산하려는 값이 아무것도 없으므로 연산하지 않음
		}
		else if (m_FString == NULL)	//현재 객체가 비어있는 경우
		{
			//연산하려는 값이 아무것도 없으므로 연산하지 않음
		}
		else
		{
			va_list ap;
			va_start(ap, count);	//고정인수+번지=시작지점이므로, count다음인자부터 차례로 가져옴.
			for (int i = 0; i < count; i++)
			{
				if (F_Compare(m_FString, va_arg(ap, wchar_t*)))
				{
					result = true;
				}
			}
			va_end(ap);
		}
		return result;
	}

	/*
	<IsCotain>
	객체의 문자열과 비교하여 일부분이 일치하는것이 있다면 true를 반환
	*/
	bool IsContain(wchar_t *str)
	{
		if (F_Contain(m_FString, str, 0) != -1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/*
	<IsCotainFind>
	객체의 문자열과 비교하여 일부분이 일치하는것이 있다면 번지수를 반환
	start인자를 지정한다면 start번지부터 찾아나감
	*/
	int IsContainFind(wchar_t *str)
	{
		return F_Contain(m_FString, str, 0);
	}
	int IsContainFind(wchar_t *str, int start)
	{
		return F_Contain(m_FString, str, start);
	}

	/*
	<Tokenizing>
	객체의 문자열을 특정 기준으로 나누어 자른 후 자른 문자열을 반환
	*/
	FString Tokenizing(wchar_t *standard)
	{
		FString strTemp;
		int length = F_Length(standard);
		int find = F_Contain(m_FString, standard, 0);	//찾은 번지 저장

		F_Allocation(strTemp.m_FString, find + 1);
		F_Copy(strTemp.m_FString, m_FString, 0, find);
		TrimLeft(find + length);

		return strTemp;
	}
	/*
	<Parsing>
	객체의 문자열 중 두 기준 사이의 문자열을 반환한다.
	*/
	FString Parsing(wchar_t *standard_start, wchar_t *standart_end)
	{
		FString strTemp;
		int start_pos = F_Contain(m_FString, standard_start, 0);
		int end_pos = F_Contain(m_FString, standart_end, start_pos + 1);

		if (start_pos != -1 && end_pos != -1)	//두 기준을 모두 찾은 경우
		{
			int start_length = F_Length(standard_start);
			int length = end_pos - (start_pos + start_length);

			F_Allocation(strTemp.m_FString, length + 1);
			F_Copy(strTemp.m_FString, m_FString, start_pos + start_length, length);
		}
		return strTemp;
	}

	/*
	<FStringToFString>
	=연산과 동일하며, int형 인자가 두개인 오버로딩의 경우 start번지부터 num수 만큼 복사
	*/
	FString FStringToFString()
	{
		FString strTemp;
		F_Allocation(strTemp.m_FString, F_Length(m_FString) + 1);
		F_Copy(strTemp.m_FString, m_FString);

		return strTemp;
	}
	FString FStringToFString(int start, int num)
	{
		FString strTemp;
		F_Allocation(strTemp.m_FString, num + 1);
		F_Copy(strTemp.m_FString, m_FString, start, num);

		return strTemp;
	}

	/*
	<FStringToInt>
	객체의 문자열형 숫자를 Int형으로 변환 후 반환
	*/
	int FStringToInt()
	{
		return F_WideCharToInt(m_FString);
	}

	/*
	<FStringToMultibyte>
	객체의 유니코드형 문자열을 멀티바이트로 변환 후 포인터를 반환
	char변수의 크기가 현재 객체의 문자열 길이보다 커야함을 주의해야한다.
	*/
	char* FStringToMultibyte(char* str)
	{
		F_Copy(str, F_WideCharToMultibyte(m_FString, 0));
		return str;
	}
	wchar_t* FStringToWideChar(wchar_t* str)
	{
		F_Copy(str, m_FString);
		return str;
	}

	/*
	<FileToFString>
	파일로부터 데이터를 읽어들인다

	-유니코드형 파일 가장 앞에는 0xFEFF = 65279 값이 붙어있다.
	*/
	FString& FileToFString(wchar_t* path)
	{
		DWORD dwRead;	//실제 읽어진 양
		HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		int length = GetFileSize(hFile, 0);

		if (hFile != INVALID_HANDLE_VALUE && length > 0)
		{
			//인코딩 캐치
			BYTE lpHeader[2];
			ReadFile(hFile, lpHeader, 2, 0, NULL);

			//유니코드
			if (lpHeader[0] == 0xFF && lpHeader[1] == 0xFE)	//유니코드는 0xFF 0xFE
			{
				wchar_t *strTemp = NULL;
				F_Allocation(strTemp, (length / 2) + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead / 2] = NULL;	//유니코드는 2바이트

				F_Allocation(m_FString, (dwRead / 2) + 1);
				F_Copy(m_FString, strTemp);	//유니코드 표시기호 제외하고 복사
				F_Allocation(strTemp, 0);
			}
			//UTF-8
			else if (lpHeader[0] == 0xEF && lpHeader[1] == 0xBB)//UTF-8은 0xEF 0xBB 0xBF
			{
				//파일포인터를 3바이트 지점부터(헤더 뛰어넘음)
				LARGE_INTEGER FilePointer;
				FilePointer.QuadPart = 3;
				SetFilePointerEx(hFile, FilePointer, FILE_BEGIN, NULL);


				char *strTemp = NULL;
				F_Allocation(strTemp, length + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead] = NULL;		//멀티바이트코드는 1바이트

				F_Allocation(m_FString, dwRead + 1);
				F_Copy(m_FString, F_MultibyteToWideChar(strTemp, F_UTF8));
				F_Allocation(strTemp, 0);
			}
			//안시코드
			else	//안시코드파일은 헤더가 없기때문에 파일 포인터를 처음으로 되돌려야한다.
			{
				//파일포인터를 다시 처음으로
				LARGE_INTEGER FilePointer;
				FilePointer.QuadPart = 0;
				SetFilePointerEx(hFile, FilePointer, FILE_BEGIN, NULL);


				char *strTemp = NULL;
				F_Allocation(strTemp, length + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead] = NULL;		//멀티바이트코드는 1바이트

				F_Allocation(m_FString, dwRead + 1);
				F_Copy(m_FString, F_MultibyteToWideChar(strTemp, F_ANSICODE));
				F_Allocation(strTemp, 0);
			}
		}
		CloseHandle(hFile);
		return *this;
	}
	/*
	<FStringToFile>
	FString데이터를 파일에 저장한다
	*/
	FString& FStringToFile(wchar_t* path, int code)
	{
		HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD dwWritten;	//실제 읽어진 양

		if (hFile != INVALID_HANDLE_VALUE && F_Length(m_FString) > 0)	//파일을 열 수 있으며 저장할 데이터가 있을 경우
		{
			if (code == F_ANSICODE)
			{
				char *strTemp = F_WideCharToMultibyte(m_FString, code);
				WriteFile(hFile, strTemp, F_Length(strTemp), &dwWritten, NULL);
			}
			else if (code == F_UTF8)
			{
				char *strTemp = F_WideCharToMultibyte(m_FString, code);
				char *strTemp2 = NULL;
				F_Allocation(strTemp2, F_Length(strTemp) + 1 + 3);
				memset(strTemp2, NULL, F_Length(strTemp) + 1 + 3);
				strTemp2[0] = (char)0xEF;
				strTemp2[1] = (char)0xBB;
				strTemp2[2] = (char)0xBF;
				F_Catenate(strTemp2, strTemp);
				WriteFile(hFile, strTemp2, F_Length(strTemp2), &dwWritten, NULL);
				F_Allocation(strTemp2, 0);
			}
			else if (code == F_UNICODE)
			{
				wchar_t *strTemp = NULL;
				F_Allocation(strTemp, F_Length(m_FString) + 1 + 1);
				memset(strTemp, NULL, F_Length(m_FString) + 1 + 1);
				strTemp[0] = 0xFEFF;
				F_Catenate(strTemp, m_FString);
				WriteFile(hFile, strTemp, F_Length(strTemp) * 2, &dwWritten, NULL);	//유니코드는 2바이트
				F_Allocation(strTemp, 0);
			}
		}
		CloseHandle(hFile);
		return *this;
	}


	bool FStringToClipboard()
	{
		if (!OpenClipboard(NULL))
		{
			return FALSE;
		}
		if (!EmptyClipboard())
		{
			return FALSE;
		}

		wchar_t *wcBuffer = 0;
		HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, (F_Length(m_FString) + 1) * sizeof (wchar_t));
		wcBuffer = (wchar_t*)GlobalLock(hglbCopy);
		F_Copy(wcBuffer, m_FString);
		GlobalUnlock(hglbCopy);

		if (::SetClipboardData(CF_UNICODETEXT, hglbCopy) == NULL)
		{
			CloseClipboard();
			return FALSE;
		}
		CloseClipboard();
		return TRUE;
	}
	FString& URLEncode()
	{
		if (m_FString == NULL)//현재 객체가 비어있는 경우
		{
			//연산하려는 값이 아무것도 없으므로 아무 작업도 하지 않음
		}
		else
		{
			char *UTF8Str = F_WideCharToMultibyte(m_FString, 1);
			//(Start)URL 인코딩
			char *URLStr = NULL;
			F_Allocation(URLStr, F_Length(UTF8Str) * 9 + 1);
			int opt_inx, ipt_inx;
			for (ipt_inx = 0, opt_inx = 0; UTF8Str[ipt_inx]; ipt_inx++, opt_inx++)
			{
				int char_val = UTF8Str[ipt_inx];
				if (char_val < 0) char_val += 256;
				// 그리고 어레이를 참조하게 되면 그만큼 느리기때문에 char_val에 값을 넣습니다
				// char를 int 로 바꾸는 과정에서 127이 넘는 값은 음수로 들어가기때문에 위와 같이 256을 더합니다
				if (char_val <= 0x1F || char_val == 0x7F || char_val >= 0x80 || char_val == ' ' ||
					char_val == '{' || char_val == '}' || char_val == '[' || char_val == ']' ||
					char_val == '|' || char_val == '\\' || char_val == '^' || char_val == '~' ||
					char_val == '`' || char_val == '#' || char_val == ';' || char_val == '/' ||
					char_val == '?' || char_val == '@' || char_val == '=' || char_val == '&')
				{
					URLStr[opt_inx] = '%';
					int UpperBit = char_val / 0x10;
					// 16을 나눠서 상위바이트를 얻습니다.
					if (UpperBit >= 0 && UpperBit <= 9)
						URLStr[++opt_inx] = UpperBit + '0';
					else
						URLStr[++opt_inx] = UpperBit + 'A' - 10;
					// 값을 보고 숫자인지 A~ E 인지 구분해보고 넣습니다. 16으로 나누면 하위 바이트가 나오겠죠..
					int LowerBit = char_val % 0x10;
					if (LowerBit >= 0 && LowerBit <= 9)
						URLStr[++opt_inx] = LowerBit + '0';
					else
						URLStr[++opt_inx] = LowerBit + 'A' - 10;
				}
				else
					URLStr[opt_inx] = char_val;
			}
			URLStr[opt_inx] = 0;
			//(End)URL 인코딩
			int length = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, URLStr, -1, NULL, NULL); //동적할당 하기위해 len 선언
			F_Allocation(m_FString, length);
			MultiByteToWideChar(CP_ACP, 0, URLStr, -1, m_FString, length); //char To TCHAR 변환
			F_Allocation(URLStr, 0);
		}

		return *this;
	}
	/*
	<PopupMessage>
	메시지박스 오버로딩
	*/
	void PopupMessage()
	{
		MessageBox(NULL, m_FString, L" ", NULL);
	}
	void PopupMessage(const wchar_t *str)
	{
		MessageBox(NULL, str, L" ", NULL);
	}
	void PopupMessage(wchar_t *str)
	{
		MessageBox(NULL, str, L" ", NULL);
	}
	void PopupMessage(char *str)
	{
		MessageBox(NULL, F_MultibyteToWideChar(str, 0), L" ", NULL);
	}
	void PopupMessage(const char *str)
	{
		MessageBox(NULL, F_MultibyteToWideChar(str, 0), L" ", NULL);
	}
	void PopupMessage(int num)
	{
		MessageBox(NULL, F_IntToWideChar(num, 10), L" ", NULL);
	}
	void PopupMessage(int num, int radix)
	{
		MessageBox(NULL, F_IntToWideChar(num, radix), L" ", NULL);
	}
	/*
	<IsEmpty>
	객체의 할당여부를 반환
	*/
	bool IsEmpty()
	{
		return m_FString == NULL ? true : false;
	}
	/*
	<Empty>
	객체의 할당해제
	*/
	void Empty()
	{
		F_Allocation(m_FString, 0);
	}
	/*
	<GetLength>
	객체의 문자열 길이를 반환
	*/
	int GetLength()
	{
		return F_Length(m_FString);
	}
};
#endif