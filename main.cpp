#include "ProcessManager.h"

int main()
{
	std::wcout << L"Enter the path to the control program: ";	//D:\test\testProject.exe
	std::wstring controlPath;
	std::wcin >> controlPath;

	std::wcout << L"Enter the path to the test program: ";      //D:\test\ATLAS.exe
	std::wstring testPath;
	std::wcin >> testPath;

	//����������� ���� ��� ����������� � �������� ��������� � ���� LPWSTR (wchar_t*)
	LPWSTR controlProgramPath = const_cast<LPWSTR>(controlPath.data());
	LPWSTR testProgramPath    = const_cast<LPWSTR>(testPath.data());

	//������� ��� ���������� ������ � �������� � ����������� ��������������� ����
	ProcessManager controlProgram{ controlProgramPath };
	ProcessManager testProgram	 { testProgramPath };

	//�������� ����������� � �������� ���������, ������� ��� ��� ��������� ������ � ��������
	controlProgram.createThread();
	testProgram.createThread();

	//��������� ��� ��������
	controlProgram.exitProcess();
	testProgram.exitProcess();

	system("PAUSE");
	return 0;
}