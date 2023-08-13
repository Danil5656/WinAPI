#pragma once			//директива дл€ контрол€ за тем, чтобы конкретный исходный файл при компил€ции подключалс€ строго 1 раз
#include <iostream>		//библиотека дл€ работы с потоками ввода-вывода
#include <string>		//библиотека дл€ работы с классом String
#include <Windows.h>	//библиотека дл€ доступа к функци€м Windows API
//#include <conio.h>    //библиотека дл€ использовани€ функции _getch()

//typedef unsigned long DWORD;
//typedef PVOID			HANDLE;
//typedef wchar_t*		LPWSTR
//typedef int			BOOL;

class ProcessManager
{
private:
	//поле дл€ хранени€ путей до управл€щей и тестовой программ
	LPWSTR path;
	//поле дл€ хранени€ дескриптора процесса
	HANDLE hProcess;
	//поле дл€ хранени€ дескриптора потока
	HANDLE hThread;
	//поле дл€ хранени€ идентификатора потока
	DWORD threadID;
public:
	//конструктор инициализации (передаем сюда пути до управл€ющей и тестовой программы)
	ProcessManager(LPWSTR path_);
	//деструктор дл€ освобождени€ пам€ти
	~ProcessManager();

	//метод дл€ создани€ дочернего процесса
	BOOL сreateChildProcess();
	//метод дл€ создани€ отдельного потока дл€ данного процесса
	void createThread();
	//статический метод потока
	static DWORD WINAPI threadFunction(LPVOID lpParam);
	//метод дл€ эмул€ции нажати€ клавиши Enter в программах
	void emulationEnter();
	//метод дл€ завершени€ процесса
	void exitProcess();

	//метод дл€ получени€ информации о процессе
	//void getInfoProcess();
};