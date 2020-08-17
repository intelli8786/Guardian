
/*
1.�����Ҵ��� ���� ����� ������ ������ �ݵ�� NULL�� �ʱ�ȭ ���ش�.
*/

#ifndef FSTRING_H	//�ߺ����� ����
#define FSTRING_H

#define F_ANSICODE 0
#define F_UTF8 1
#define F_UNICODE 2


//(S)�����Լ�
template <typename T>
static int FS_Length(T *str)
{
	int length = 0;
	if (str == NULL)	//NULL or nullptr
	{
		//���������� ��� �ƹ� �۾��� ���� �ʰ� 0�� ��ȯ
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
static int FS_Length(int num, int radix)	//������ ��� '-'��ȣ�� ������ ���̸� ��ȯ�Ѵ�.
{
	int length = 0;
	bool negative = false;	//����üũ

	if (num < 0)//������ ���
	{
		num *= -1;	//���ȭ
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
	if (str1 == NULL)	//str1�� �Ҵ���� ���� ���
	{
		//MessageBox(NULL, L"������ ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
	}
	else
	{
		if (str2 == NULL)	//NULL or nullptr
		{
			//������ ���ڿ��� ���������� ��� str1�� ���
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
	if (str1 == NULL)	//str1�� �Ҵ���� ���� ���
	{
		//MessageBox(NULL, L"������ ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
	}
	else
	{
		if (str2 == NULL)	//NULL or nullptr
		{
			//������ ���ڿ��� ���������� ��� str1�� ���
			*str1 = NULL;
		}
		else
		{
			if (start < 0)	//���۰��� 0���� ���� ���
			{
				start = 0;	//0���� ����
			}
			if (num > FS_Length(str2))	//������ ���� str2�� ���̺��� Ŭ ���
			{
				num = FS_Length(str2);//str2���̸�ŭ�� ����
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
		//MessageBox(NULL, L"�̾��� ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
	}
	else if (str2 == NULL)
	{
		//���� ������ ��������Ƿ� str1�� ��ȭ��Ű�� ����
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
		if (str1 == str2)	//�� �� NULL�� ���
		{
			return true;
		}
		else if (str1 != NULL)	//���Ҵ纯�� = ù����NULL�κ���
		{
			if (*str1 == NULL)
				return true;
		}
		else if (str2 != NULL)	//���Ҵ纯�� = ù����NULL�κ���
		{
			if (*str2 == NULL)
				return true;
		}
		else  //���� �ϳ��� NULL�� ���
		{
			return false;
		}
	}
	else
	{
		while (*str1++ == *str2++)
		{
			if (*str1 == NULL && *str2 == NULL)	//������ �α��� ���ٸ�
			{
				return true;
			}
		}
	}
	return false;
}
template <typename T>
void FS_Trim(T *str, int trim, bool direction)	//direction 0 ���ʺ��� 1 �����ʺ���
{
	if (trim > 0 && str != NULL)
	{
		int length = FS_Length(str);
		if (length > trim)	//���ڿ� ���̰� ������� ������ ������ �����
		{
			if (!direction)	//����Trim�� ���
			{
				for (int i = 0; i < length - trim; i++)
				{
					str[i] = str[i + trim];
				}
			}
			str[length - trim] = NULL;
		}
		else	//���ڿ� ���̰� ������� ������ ŭ
		{
			*str = NULL;	//ù��° ���ڿ� NULL ����
		}
	}
}
template <typename T1, typename T2>
int FS_Contain(T1 *str1, T2 *str2, int start)
{
	if (str1 == NULL)	//str1�� �Ҵ��������
	{
		return -1;
	}
	else if (str2 == NULL)	//str2�� �Ҵ��������
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
				if (str1[i + check] == str2[j])//���ڰ� ���� ���� ���
				{
					check++;
					if (j == length2 - 1)	//j�� ���������� �극��ũ���� ����
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
//(E)�����Լ�

class FString
{
public:
	wchar_t *m_FString = NULL;

	/*
	<F_Length>
	�����ڵ��� ���ڿ��� ���� ��ȯ�Լ�
	NULL�� ������ ����
	*/
	template <typename T>
	int F_Length(T *str)
	{
		int length = 0;
		if (str == NULL)	//NULL or nullptr
		{
			//���������� ��� �ƹ� �۾��� ���� �ʰ� 0�� ��ȯ
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
	int F_Length(int num, int radix)	//������ ��� '-'��ȣ�� ������ ���̸� ��ȯ�Ѵ�.
	{
		int length = 0;
		bool negative = false;	//����üũ

		if (num < 0)//������ ���
		{
			num *= -1;	//���ȭ
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
	�����ڵ��� ���ڿ��� ����
	str2�� str1�� �����Ѵ�.
	�Ǵ� str2�� str1�� start�������� num�� ��ŭ ����
	*/
	template <typename T1, typename T2>
	void F_Copy(T1 *str1, T2 *str2)
	{
		if (str1 == NULL)	//str1�� �Ҵ���� ���� ���
		{
			//MessageBox(NULL, L"������ ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
		}
		else
		{
			if (str2 == NULL)	//NULL or nullptr
			{
				//������ ���ڿ��� ���������� ��� str1�� ���
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
		if (str1 == NULL)	//str1�� �Ҵ���� ���� ���
		{
			//MessageBox(NULL, L"������ ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
		}
		else
		{
			if (str2 == NULL)	//NULL or nullptr
			{
				//������ ���ڿ��� ���������� ��� str1�� ���
				*str1 = NULL;
			}
			else
			{
				if (start < 0)	//���۰��� 0���� ���� ���
				{
					start = 0;	//0���� ����
				}
				if (num>F_Length(str2))	//������ ���� str2�� ���̺��� Ŭ ���
				{
					num = F_Length(str2);//str2���̸�ŭ�� ����
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
	�����ڵ��� ���ڿ� ����
	str2�� str1�ڿ� �����Ѵ�.
	*/
	template <typename T1, typename T2>
	void F_Catenate(T1 *str1, T2 *str2)
	{
		if (str1 == NULL)
		{
			//MessageBox(NULL, L"�̾��� ������ �̻��ؿ�!\n�Ƹ� �Ҵ��� �ȵȰͰ��ƿ�.", L" ", NULL);
		}
		else if (str2 == NULL)
		{
			//���� ������ ��������Ƿ� str1�� ��ȭ��Ű�� ����
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
	���ڿ���
	�Ҵ�������� ������ ù��° ���� NULL�������� ������ �����ϰ� ����ִ� ���·� �Ѵ�. �׷��Ƿ� (NULL == L"") �� true�̴�.
	*/
	template <typename T1, typename T2>
	bool F_Compare(T1 *str1, T2 *str2)
	{
		if (str1 == NULL || str2 == NULL)
		{
			if (str1 == str2)	//�� �� NULL�� ���
			{
				return true;
			}
			else if (str1 != NULL)	//���Ҵ纯�� = ù����NULL�κ���
			{
				if (*str1 == NULL)
					return true;
			}
			else if (str2 != NULL)	//���Ҵ纯�� = ù����NULL�κ���
			{
				if (*str2 == NULL)
					return true;
			}
			else  //���� �ϳ��� NULL�� ���
			{
				return false;
			}
		}
		else
		{
			while (*str1++ == *str2++)
			{
				if (*str1 == NULL && *str2 == NULL)	//������ �α��� ���ٸ�
				{
					return true;
				}
			}
		}
		return false;
	}

	/*
	<F_Trim>
	���ڿ��Ұ�
	����° ���ڰ� false�� ��� ���ʺ���, true�� ��� �����ʺ��� trim �� ��ŭ �Ұ��Ѵ�.
	*/
	template <typename T>
	void F_Trim(T *str, int trim, bool direction)	//direction 0 ���ʺ��� 1 �����ʺ���
	{
		if (trim > 0 && str != NULL)
		{
			int length = F_Length(str);
			if (length > trim)	//���ڿ� ���̰� ������� ������ ������ �����
			{
				if (!direction)	//����Trim�� ���
				{
					for (int i = 0; i < length - trim; i++)
					{
						str[i] = str[i + trim];
					}
				}
				str[length - trim] = NULL;
			}
			else	//���ڿ� ���̰� ������� ������ ŭ
			{
				*str = NULL;	//ù��° ���ڿ� NULL ����
			}
		}
	}

	/*
	<F_Contain>
	str1���ڿ��� str2���ڿ��� ���ԵǴ� �������� ��ȯ
	0���� ����
	*/
	template <typename T1, typename T2>
	int F_Contain(T1 *str1, T2 *str2, int start)
	{
		if (str1 == NULL)	//str1�� �Ҵ��������
		{
			return -1;
		}
		else if (str2 == NULL)	//str2�� �Ҵ��������
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
					if (str1[i + check] == str2[j])//���ڰ� ���� ���� ���
					{
						check++;
						if (j == length2 - 1)	//j�� ���������� �극��ũ���� ����
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
	���� �Ҵ�&���Ҵ�
	*/
	template <typename T>
	void F_Allocation(T *& str, int size)
	{
		if (str == NULL)	//�Ҵ��� ������ ���� �Ҵ�������� ���(���Ҵ� �� �ʿ䰡 ���� ���)
		{
			if (size > 1)
			{
				str = new T[size];
				*str = NULL;	//ù���ڸ� NULL�� �Ҵ�
			}
		}
		else	//���Ҵ� �� �ʿ䰡 �ִ� ���
		{
			delete[] str;
			str = NULL;

			if (size > 1)
			{
				str = new T[size];
				*str = NULL;	//ù���ڸ� NULL�� �Ҵ�
			}
		}
	}

	/*
	<F_MultibyteToWideChar>
	��Ƽ����Ʈ�� �ڵ带 �����ڵ�� ��ȯ
	*/
	template <typename T>
	wchar_t* F_MultibyteToWideChar(T *str, int code)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//��Ƽ������ ���� static ������ ���� ���ؽ� �ʿ�
		WaitForSingleObject(hMutex, INFINITE);	//����ϰ��ִٸ� ������ ���
		static wchar_t *strW = NULL;

		if (str == NULL || *str == NULL)
		{

		}
		else
		{
			int length;
			bool negative = false;	//����üũ
			if (strW != NULL)	//�Ҵ��� ������ �������Ͱ� �ƴѰ��
			{
				delete[] strW;	//�Ҵ��� ũ�⺸�� ���� �����Ͱ� ������� ��� delete�Լ�ȣ��� �����߻�
				strW = NULL;
			}

			if (code == F_ANSICODE)	//Ansi
			{
				length = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, NULL, NULL);
				strW = new wchar_t[length + 1];
				MultiByteToWideChar(CP_ACP, 0, str, -1, strW, length); //char To TCHAR ��ȯ
			}
			else if (code == F_UTF8)	//UTF-8
			{
				length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, NULL);
				strW = new wchar_t[length + 1];
				MultiByteToWideChar(CP_UTF8, 0, str, -1, strW, length); //char To TCHAR ��ȯ
			}
		}

		ReleaseMutex(hMutex);
		return strW;
	}

	/*
	<F_WideCharToMultibyte>
	�����ڵ带 ��Ƽ����Ʈ�� �ڵ�� ��ȯ
	code 0�� �Ƚ��ڵ� 1�� UTF-8�ڵ�
	*/
	template <typename T>
	char* F_WideCharToMultibyte(T *str, int code)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//��Ƽ������ ���� static ������ ���� ���ؽ� �ʿ�
		WaitForSingleObject(hMutex, INFINITE);	//����ϰ��ִٸ� ������ ���
		static char *strM = NULL;

		if (str == NULL || *str == NULL)
		{

		}
		else
		{
			int length;
			bool negative = false;	//����üũ
			if (strM != NULL)	//�Ҵ��� ������ �������Ͱ� �ƴѰ��
			{
				delete[] strM;	//�Ҵ��� ũ�⺸�� ���� �����Ͱ� ������� ��� delete�Լ�ȣ��� �����߻�
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
	Int�� �����͸� �����ڵ������� ��ȯ�ϸ�, �ּҸ� static������ ���� �� ������ ȣ����� �����ʹ� ���� ����ȴ�.
	*/
	wchar_t* F_IntToWideChar(int num, int radix)
	{
		HANDLE hMutex = CreateMutex(NULL, false, NULL);	//��Ƽ������ ���� static ������ ���� ���ؽ� �ʿ�
		WaitForSingleObject(hMutex, INFINITE);	//����ϰ��ִٸ� ������ ���
		static wchar_t *strN;

		bool negative = false;	//����üũ
		int length = F_Length(num, radix);	//'-'��ȣ�� ������ ����

		if (num < 0)//������ ���
		{
			num *= -1;	//���ȭ
			negative = true;
		}
		if (strN != NULL)	//�Ҵ��� ������ �������Ͱ� �ƴѰ��
		{
			delete[] strN;	//�Ҵ��� ũ�⺸�� ���� �����Ͱ� ������� ��� delete�Լ�ȣ��� �����߻�
			strN = NULL;
		}
		strN = new wchar_t[length + 1];
		if (negative == true)	//����üũ
		{
			strN[0] = '-';
		}

		int rest = 0;	//������
		for (int i = 1; i < length - negative + 1; i++)
		{
			rest = num % radix;
			num /= radix;
			if (rest < 10)	//�������� 10����(10���� ����)
			{
				strN[length - i] = rest + L'0';
			}
			else	//10���� �̻�
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
	�����ڵ��� �����͸� Int������ ��ȯ�� ��ȯ�Ѵ�.
	*/
	int F_WideCharToInt(wchar_t *str)
	{
		int result = 0;
		if (str == NULL)	//str1�� �Ҵ��������
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
	�����ڰ� ȣ��Ǿ��� ���� ������ �Ҵ�Ǿ����� �����Ƿ� NULL�����Ͱ� �Ѿ�� ��� m_FString�� ����� �ʾƵ� ��.
	*/
	//(S) ������
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
	//(E) ������

	//(S) ������ �����ε�
	/*
	<LPCWSTR������ �����ε�>
	LPCWSTR(wchar_t*)�� Ÿ��ĳ����
	*/
	operator LPCWSTR()	//��ü�̸��� LPCWSTR�� Ÿ��ĳ������ �� �̸� ��ȯ
	{					//����° ������ C�� Constance�̸�, ����μ� ����Ұ���
		return m_FString;
	}

	/*
	< = ������ �����ε�>
	str�� ���� ��ü�� ������ �� ���簴ü�� ��ȯ
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
	FString &operator = (char* str)		//��Ƽ����Ʈ->�����ڵ� ��ȯ�Ҵ�
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
		return *this;
	}
	FString &operator = (const char* str)	//��Ƽ����Ʈ->�����ڵ� ��ȯ�Ҵ�
	{
		F_Allocation(m_FString, F_Length(str) + 1);
		F_Copy(m_FString, F_MultibyteToWideChar(str, 0));
		return *this;
	}
	FString &operator = (int num)		//��Ƽ����Ʈ->�����ڵ� ��ȯ�Ҵ�
	{
		F_Allocation(m_FString, F_Length(num, 10) + 1);
		F_Copy(m_FString, F_IntToWideChar(num, 10));
		return *this;
	}

	/*
	< + ������ �����ε�>
	str1�� str2�� ������ �� FString��ü�� ��ȯ
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
	< += ������ �����ε�>
	str1�� str2�� ������ �� FString��ü�� ���� �� �ּ� ��ȯ
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
	< == ������ �����ε�>
	str1�� str2�� ���� �� ���������� ��ȯ
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
	< != ������ �����ε�>
	str1�� str2�� ���� �� ���������� ����ȯ
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
	< <,> ������ �����ε�>
	str1�� str2�� ���ڿ� ���̸� �� �� �� ���� ��ȯ
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
	< <=,>= ������ �����ε�>
	str1�� str2���ڿ��� �����ϸ� ��, �׷��� �ʴٸ� ���̸� ���� ũ�� ������ �� ������ �Ǻ��Ѵ�.
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
	< [] ������ �����ε�>
	�迭÷�ڸ� ������ �ش� ������ �����ڵ��� ���ڸ� ��ȯ
	*/
	wchar_t operator[](int num)
	{
		return *(m_FString + num);
	}
	//(E) ������ �����ε�

	//(S) ����Լ�
	/*
	<Append>
	str1�� str2�� ������ �� FString��ü�� ���� �� �ּ� ��ȯ
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
	������ ����ŭ ����, ������ �ڸ� �� �ּ� ��ȯ
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
	��ü�� ���ڿ��� ���Ͽ� ��� �μ� �� �Ϻκ��� ��ġ�ϴ°��� �ϳ��� �ִٸ� true�� ��ȯ
	*/
	bool IsContains(int count, ...)	//�����μ��� ����,���� ���ڿ� �迭�� ������,�����μ�
	{
		bool result = false;	//true : ��ġ�ϴ¹��ڿ� ����, false : ��ġ�ϴ� ���ڿ� ����
		if (count == 0)	//ī��Ʈ�� 0�� ���
		{
			//�����Ϸ��� ���� �ƹ��͵� �����Ƿ� �������� ����
		}
		else if (m_FString == NULL)	//���� ��ü�� ����ִ� ���
		{
			//�����Ϸ��� ���� �ƹ��͵� �����Ƿ� �������� ����
		}
		else
		{
			va_list ap;
			va_start(ap, count);	//�����μ�+����=���������̹Ƿ�, count�������ں��� ���ʷ� ������.
			for (int i = 0; i < count; i++)
			{
				if (F_Contain(m_FString, va_arg(ap, wchar_t*), 0) != -1)	//����� ã�� ���Ѵٸ� NULL���� ��ȯ��.
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
	��ü�� ���ڿ��� ���Ͽ� ��� �μ� �� ��ġ�ϴ°��� �ϳ��� �ִٸ� true�� ��ȯ
	*/
	bool IsEquals(int count, ...)	//�����μ��� ����,���� ���ڿ� �迭�� ������,�����μ�
	{
		bool result = false;	//true : ��ġ�ϴ¹��ڿ� ����, false : ��ġ�ϴ� ���ڿ� ����
		if (count == 0)	//ī��Ʈ�� 0�� ���
		{
			//�����Ϸ��� ���� �ƹ��͵� �����Ƿ� �������� ����
		}
		else if (m_FString == NULL)	//���� ��ü�� ����ִ� ���
		{
			//�����Ϸ��� ���� �ƹ��͵� �����Ƿ� �������� ����
		}
		else
		{
			va_list ap;
			va_start(ap, count);	//�����μ�+����=���������̹Ƿ�, count�������ں��� ���ʷ� ������.
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
	��ü�� ���ڿ��� ���Ͽ� �Ϻκ��� ��ġ�ϴ°��� �ִٸ� true�� ��ȯ
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
	��ü�� ���ڿ��� ���Ͽ� �Ϻκ��� ��ġ�ϴ°��� �ִٸ� �������� ��ȯ
	start���ڸ� �����Ѵٸ� start�������� ã�Ƴ���
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
	��ü�� ���ڿ��� Ư�� �������� ������ �ڸ� �� �ڸ� ���ڿ��� ��ȯ
	*/
	FString Tokenizing(wchar_t *standard)
	{
		FString strTemp;
		int length = F_Length(standard);
		int find = F_Contain(m_FString, standard, 0);	//ã�� ���� ����

		F_Allocation(strTemp.m_FString, find + 1);
		F_Copy(strTemp.m_FString, m_FString, 0, find);
		TrimLeft(find + length);

		return strTemp;
	}
	/*
	<Parsing>
	��ü�� ���ڿ� �� �� ���� ������ ���ڿ��� ��ȯ�Ѵ�.
	*/
	FString Parsing(wchar_t *standard_start, wchar_t *standart_end)
	{
		FString strTemp;
		int start_pos = F_Contain(m_FString, standard_start, 0);
		int end_pos = F_Contain(m_FString, standart_end, start_pos + 1);

		if (start_pos != -1 && end_pos != -1)	//�� ������ ��� ã�� ���
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
	=����� �����ϸ�, int�� ���ڰ� �ΰ��� �����ε��� ��� start�������� num�� ��ŭ ����
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
	��ü�� ���ڿ��� ���ڸ� Int������ ��ȯ �� ��ȯ
	*/
	int FStringToInt()
	{
		return F_WideCharToInt(m_FString);
	}

	/*
	<FStringToMultibyte>
	��ü�� �����ڵ��� ���ڿ��� ��Ƽ����Ʈ�� ��ȯ �� �����͸� ��ȯ
	char������ ũ�Ⱑ ���� ��ü�� ���ڿ� ���̺��� Ŀ������ �����ؾ��Ѵ�.
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
	���Ϸκ��� �����͸� �о���δ�

	-�����ڵ��� ���� ���� �տ��� 0xFEFF = 65279 ���� �پ��ִ�.
	*/
	FString& FileToFString(wchar_t* path)
	{
		DWORD dwRead;	//���� �о��� ��
		HANDLE hFile = CreateFile(path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		int length = GetFileSize(hFile, 0);

		if (hFile != INVALID_HANDLE_VALUE && length > 0)
		{
			//���ڵ� ĳġ
			BYTE lpHeader[2];
			ReadFile(hFile, lpHeader, 2, 0, NULL);

			//�����ڵ�
			if (lpHeader[0] == 0xFF && lpHeader[1] == 0xFE)	//�����ڵ�� 0xFF 0xFE
			{
				wchar_t *strTemp = NULL;
				F_Allocation(strTemp, (length / 2) + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead / 2] = NULL;	//�����ڵ�� 2����Ʈ

				F_Allocation(m_FString, (dwRead / 2) + 1);
				F_Copy(m_FString, strTemp);	//�����ڵ� ǥ�ñ�ȣ �����ϰ� ����
				F_Allocation(strTemp, 0);
			}
			//UTF-8
			else if (lpHeader[0] == 0xEF && lpHeader[1] == 0xBB)//UTF-8�� 0xEF 0xBB 0xBF
			{
				//���������͸� 3����Ʈ ��������(��� �پ����)
				LARGE_INTEGER FilePointer;
				FilePointer.QuadPart = 3;
				SetFilePointerEx(hFile, FilePointer, FILE_BEGIN, NULL);


				char *strTemp = NULL;
				F_Allocation(strTemp, length + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead] = NULL;		//��Ƽ����Ʈ�ڵ�� 1����Ʈ

				F_Allocation(m_FString, dwRead + 1);
				F_Copy(m_FString, F_MultibyteToWideChar(strTemp, F_UTF8));
				F_Allocation(strTemp, 0);
			}
			//�Ƚ��ڵ�
			else	//�Ƚ��ڵ������� ����� ���⶧���� ���� �����͸� ó������ �ǵ������Ѵ�.
			{
				//���������͸� �ٽ� ó������
				LARGE_INTEGER FilePointer;
				FilePointer.QuadPart = 0;
				SetFilePointerEx(hFile, FilePointer, FILE_BEGIN, NULL);


				char *strTemp = NULL;
				F_Allocation(strTemp, length + 1);
				ReadFile(hFile, strTemp, length, &dwRead, NULL);
				strTemp[dwRead] = NULL;		//��Ƽ����Ʈ�ڵ�� 1����Ʈ

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
	FString�����͸� ���Ͽ� �����Ѵ�
	*/
	FString& FStringToFile(wchar_t* path, int code)
	{
		HANDLE hFile = CreateFile(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD dwWritten;	//���� �о��� ��

		if (hFile != INVALID_HANDLE_VALUE && F_Length(m_FString) > 0)	//������ �� �� ������ ������ �����Ͱ� ���� ���
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
				WriteFile(hFile, strTemp, F_Length(strTemp) * 2, &dwWritten, NULL);	//�����ڵ�� 2����Ʈ
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
		if (m_FString == NULL)//���� ��ü�� ����ִ� ���
		{
			//�����Ϸ��� ���� �ƹ��͵� �����Ƿ� �ƹ� �۾��� ���� ����
		}
		else
		{
			char *UTF8Str = F_WideCharToMultibyte(m_FString, 1);
			//(Start)URL ���ڵ�
			char *URLStr = NULL;
			F_Allocation(URLStr, F_Length(UTF8Str) * 9 + 1);
			int opt_inx, ipt_inx;
			for (ipt_inx = 0, opt_inx = 0; UTF8Str[ipt_inx]; ipt_inx++, opt_inx++)
			{
				int char_val = UTF8Str[ipt_inx];
				if (char_val < 0) char_val += 256;
				// �׸��� ��̸� �����ϰ� �Ǹ� �׸�ŭ �����⶧���� char_val�� ���� �ֽ��ϴ�
				// char�� int �� �ٲٴ� �������� 127�� �Ѵ� ���� ������ ���⶧���� ���� ���� 256�� ���մϴ�
				if (char_val <= 0x1F || char_val == 0x7F || char_val >= 0x80 || char_val == ' ' ||
					char_val == '{' || char_val == '}' || char_val == '[' || char_val == ']' ||
					char_val == '|' || char_val == '\\' || char_val == '^' || char_val == '~' ||
					char_val == '`' || char_val == '#' || char_val == ';' || char_val == '/' ||
					char_val == '?' || char_val == '@' || char_val == '=' || char_val == '&')
				{
					URLStr[opt_inx] = '%';
					int UpperBit = char_val / 0x10;
					// 16�� ������ ��������Ʈ�� ����ϴ�.
					if (UpperBit >= 0 && UpperBit <= 9)
						URLStr[++opt_inx] = UpperBit + '0';
					else
						URLStr[++opt_inx] = UpperBit + 'A' - 10;
					// ���� ���� �������� A~ E ���� �����غ��� �ֽ��ϴ�. 16���� ������ ���� ����Ʈ�� ��������..
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
			//(End)URL ���ڵ�
			int length = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, URLStr, -1, NULL, NULL); //�����Ҵ� �ϱ����� len ����
			F_Allocation(m_FString, length);
			MultiByteToWideChar(CP_ACP, 0, URLStr, -1, m_FString, length); //char To TCHAR ��ȯ
			F_Allocation(URLStr, 0);
		}

		return *this;
	}
	/*
	<PopupMessage>
	�޽����ڽ� �����ε�
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
	��ü�� �Ҵ翩�θ� ��ȯ
	*/
	bool IsEmpty()
	{
		return m_FString == NULL ? true : false;
	}
	/*
	<Empty>
	��ü�� �Ҵ�����
	*/
	void Empty()
	{
		F_Allocation(m_FString, 0);
	}
	/*
	<GetLength>
	��ü�� ���ڿ� ���̸� ��ȯ
	*/
	int GetLength()
	{
		return F_Length(m_FString);
	}
};
#endif