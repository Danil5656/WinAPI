#include "ProcessManager.h"

//���������� ������������ �������������
ProcessManager::ProcessManager(const LPWSTR path_)
{
	size_t length = wcslen(path_);	  //��������� ����� path
	path = new wchar_t[length + 1];	  //�������� ������ ��� ������ � ��� ����������� ������ '\0'

	for (uint32_t i = 0; i < length; ++i)
	{
		path[i] = path_[i];			  //������������ ������������ ������
	}

	path[length] = '\0';			  //���������� ������������ ������� '\0' � ����� ������

	hProcess = nullptr;				  //������������ �������� ��������� ����������� ��������
	hThread  = nullptr;				  //������������ �������� ��������� ����������� ������
	threadID = NULL;			      //������������ ��������� �������� ��������� �������������� ������
}

//���������� ����������� ��� ������������ ������
ProcessManager::~ProcessManager()
{
	delete[] path;
}

//���������� ������ ��� �������� ��������� ��������
BOOL ProcessManager::�reateChildProcess()
{
	STARTUPINFO         si;	//��������� �� ���������, ������������ ��� ����������� ������ �������� ������ ��������
	PROCESS_INFORMATION pi;	//��������� �� ��������� ��� �������� ����������� ���������� ��������

	ZeroMemory(&si, sizeof(si));	//������� ������ ��������� STARTUPINFO
	si.cb = sizeof(si);				//��������� ������� ���������
	ZeroMemory(&pi, sizeof(pi));	//������� ������ ��������� PROCESS_INFORMATION

	//��������� ������ �������� ��������� ��������
	if (!CreateProcess(NULL,		//��� ������������ ������ (��� �����, ������������ �������)
					   path,		//��� ������������ �����, ������� ����� ������������ ����� �������
					   NULL,		//��������� �� ��������� SECURITY_ATRIBUTES
					   NULL,		//��������� �� ��������� SECURITY_ATRIBUTES
					   TRUE,		//���� ������������ ������������ �������� ��������		
					   NULL,		//����� �������� �������� ��������
					   NULL,		//��������� �� ���� �����
					   NULL,		//������� ���� ��� �������
					   &si,			//��������� �� ��������� STARTUPINFO
					   &pi			//��������� �� ��������� PROCESS_INFORMATION
	))
	{
		//������� ��������� �� ������ � ����� ����������, ���� �������� �������� �� �������
		std::cerr << "Process creation error. Error code: " << GetLastError() << std::endl;
		return false;
	}
	else
	{
		std::cout << "Process created successfully" << std::endl; //������� ��������� �� �������� �������� ��������
		WaitForSingleObject(pi.hProcess, INFINITE);			      //��������, ���� ������ ����������

		//_getch();	//������� ����� (��������� ���� ������ � ����������, �� �� ����� �� �� ���������) 

		hProcess = pi.hProcess;	//��������� ������������� ��������
		hThread = pi.hThread;	//��������� ������������� ������

		return true;			//�������� ���������� ������ �������
	}
}

// ����� ��� �������� ������� ������� Enter � ���������� ��������.
void ProcessManager::emulationEnter()
{
	//������� ��������� ��� �������� ������������ �������.
	INPUT input;
	input.type = INPUT_KEYBOARD; //��������� ��� ������� (������������)

	//������� ������� Enter
	input.ki.wVk = VK_RETURN;   //��������� ����������� ��� ������� Enter.
	input.ki.dwFlags = 0;       //��������� ����, ���������� ������� �������.

	//���������� ������� ����� (������� �������)
	SendInput(1, &input, sizeof(INPUT));

	//�������� ����� ��������� ������� ���������� �������.
	Sleep(10); //����� ������������� ��������� ������� ��������

	//���������� ������� Enter.
	input.ki.dwFlags = KEYEVENTF_KEYUP; //��������� ����, ���������� ���������� �������

	//���������� ������� ����� (���������� �������)
	SendInput(1, &input, sizeof(INPUT));
}

//���������� ������ ��� �������� ���������� ������ ��� ������� ��������
void ProcessManager::createThread()
{
	//��������� ��� ������� ������� ��������
	if (�reateChildProcess())
	{
		//������� ��������� ����� ��� ������� ��������
		hThread = CreateThread(NULL,									//���������� ������
							   0,										//������ ����� (��-��������� 1 ��)
							   threadFunction,							//��������� �� ��������� �������
							   NULL,									//�������� ������ (NULL)
							   0,									    //����� �������� ������
							   &threadID							    //������������� ������
		);
		//��������� ����� �� ���������� ��������
		if (hThread)
		{
			std::cout << "Thread creating successfully!" << std::endl;
			//�������� ������� �������� ������� ������� Enter � ��������� ��������
			emulationEnter();
		}
	}
}

DWORD WINAPI ProcessManager::threadFunction(LPVOID lpParam)
{
	//�������� �������� ������� � ���� ProcessManager
	ProcessManager* pManager = static_cast<ProcessManager*>(lpParam);

	//������� ��������� ��� ����� �����������
	std::cout << "Thread is executing..." << std::endl;

	//����� ����� �������� ����� ���, ������� ����� ��������� ������ ������

	// ���������� ��� ���������� ������
	return 0;
}

//���������� ������ �� ���������� ��������
void ProcessManager::exitProcess()
{
	if (hProcess != NULL)
	{
		TerminateProcess(hProcess, 0);									//������� ��� ���������� �������� � ���� ��� �������
		CloseHandle(hProcess);											//��������� ���������� ��������
		CloseHandle(hThread);											//��������� ���������� ������
		std::cout << "Process completed successfully!" << std::endl;	//������� ��������� �� �������� ���������� ��������
	}
}

//���������� ������ �� ��������� ���������� � ��������
//void ProcessManager::getInfoProcess(){}