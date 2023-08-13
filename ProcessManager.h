#pragma once			//��������� ��� �������� �� ���, ����� ���������� �������� ���� ��� ���������� ����������� ������ 1 ���
#include <iostream>		//���������� ��� ������ � �������� �����-������
#include <string>		//���������� ��� ������ � ������� String
#include <Windows.h>	//���������� ��� ������� � �������� Windows API
//#include <conio.h>    //���������� ��� ������������� ������� _getch()

//typedef unsigned long DWORD;
//typedef PVOID			HANDLE;
//typedef wchar_t*		LPWSTR
//typedef int			BOOL;

class ProcessManager
{
private:
	//���� ��� �������� ����� �� ���������� � �������� ��������
	LPWSTR path;
	//���� ��� �������� ����������� ��������
	HANDLE hProcess;
	//���� ��� �������� ����������� ������
	HANDLE hThread;
	//���� ��� �������� �������������� ������
	DWORD threadID;
public:
	//����������� ������������� (�������� ���� ���� �� ����������� � �������� ���������)
	ProcessManager(LPWSTR path_);
	//���������� ��� ������������ ������
	~ProcessManager();

	//����� ��� �������� ��������� ��������
	BOOL �reateChildProcess();
	//����� ��� �������� ���������� ������ ��� ������� ��������
	void createThread();
	//����������� ����� ������
	static DWORD WINAPI threadFunction(LPVOID lpParam);
	//����� ��� �������� ������� ������� Enter � ����������
	void emulationEnter();
	//����� ��� ���������� ��������
	void exitProcess();

	//����� ��� ��������� ���������� � ��������
	//void getInfoProcess();
};