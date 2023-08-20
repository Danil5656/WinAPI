#pragma once			//директива дл€ контрол€ за тем, чтобы конкретный исходный файл при компил€ции подключалс€ строго 1 раз
#include <iostream>		//библиотека дл€ работы с потоками ввода-вывода (cerr, cout)
#include <string>		//библиотека дл€ работы с классом String
#include <Windows.h>	//библиотека дл€ доступа к функци€м Windows API (CreateProcessW, CloseHandle)
#include <psapi.h>		//библиотек дл€ доступа к сведени€м о состо€нии процесса (GetProcessMemoryInfo)
#include <future>		//библиотека дл€ асинхронного выполнени€ задач (async)
#include <chrono>		//библиотека дл€ работы со временем	(chrono::steady_clock::now)

class BaseProcessManager
{
private:
	//поле дл€ хранени€ путей до управл€щей и тестовой программ
	const std::wstring path_;
	//поле дл€ хранени€ дескриптора процесса
	HANDLE hProcess;
public:
	//конструктор инициализации (передаем сюда пути до управл€ющей и тестовой программы)
	BaseProcessManager(const std::wstring path);
	//статический метод дл€ экранировани€ слешей в пут€х до программы
	static std::wstring forkedSlashes(std::string& path);

	//метод дл€ получени€ пути до программы
	const std::wstring GetPath() const noexcept;
	//метод дл€ получени€ дескриптора процесса
	const HANDLE GethProcess()   const noexcept;

	//метод дл€ создани€ и запуска процесса
	bool StartProcess();
	//метод дл€ получени€ вывода из отдельной консоли
	void GetConsoleOutput();
	//метод дл€ получени€ информации о процессе
	void GetInfoProcess();
	//метод дл€ завершени€ процесса
	void StopProcess();
	
	//виртуальный метод дл€ запуска основных методов программы
	virtual void Run (BaseProcessManager &object) {};
	//метод дл€ засечени€ времени выполнени€ программ
	void CalculateProcessTime();
};