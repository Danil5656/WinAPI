#pragma once			//��������� ��� �������� �� ���, ����� ���������� �������� ���� ��� ���������� ����������� ������ 1 ���
#include <iostream>		//���������� ��� ������ � �������� �����-������ (cerr, cout)
#include <string>		//���������� ��� ������ � ������� String
#include <Windows.h>	//���������� ��� ������� � �������� Windows API (CreateProcessW, CloseHandle)
#include <psapi.h>		//��������� ��� ������� � ��������� � ��������� �������� (GetProcessMemoryInfo)
#include <future>		//���������� ��� ������������ ���������� ����� (async)
#include <chrono>		//���������� ��� ������ �� ��������	(chrono::steady_clock::now)

class BaseProcessManager
{
private:
	//���� ��� �������� ����� �� ���������� � �������� ��������
	const std::wstring path_;
	//���� ��� �������� ����������� ��������
	HANDLE hProcess;
public:
	//����������� ������������� (�������� ���� ���� �� ����������� � �������� ���������)
	BaseProcessManager(const std::wstring path);
	//����������� ����� ��� ������������� ������ � ����� �� ���������
	static std::wstring forkedSlashes(std::string& path);

	//����� ��� ��������� ���� �� ���������
	const std::wstring GetPath() const noexcept;
	//����� ��� ��������� ����������� ��������
	const HANDLE GethProcess()   const noexcept;

	//����� ��� �������� � ������� ��������
	bool StartProcess();
	//����� ��� ��������� ������ �� ��������� �������
	void GetConsoleOutput();
	//����� ��� ��������� ���������� � ��������
	void GetInfoProcess();
	//����� ��� ���������� ��������
	void StopProcess();
	
	//����������� ����� ��� ������� �������� ������� ���������
	virtual void Run (BaseProcessManager &object) {};
	//����� ��� ��������� ������� ���������� ��������
	void CalculateProcessTime();
};