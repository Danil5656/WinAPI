#pragma once			//директива для контроля за тем, чтобы конкретный исходный файл при компиляции подключался строго 1 раз
#include <iostream>		//библиотека для работы с потоками ввода-вывода
#include <string>		//библиотека для работы с классом String
#include <Windows.h>	//библиотека для доступа к функциям Windows API
//#include <conio.h>    //библиотека для использования функции _getch()

//typedef unsigned long DWORD;
//typedef PVOID			HANDLE;
//typedef wchar_t*		LPWSTR
//typedef int			BOOL;

class ProcessManager
{
private:
	//поле для хранения путей до управлящей и тестовой программ
	LPWSTR path;
	//поле для хранения дескриптора процесса
	HANDLE hProcess;
	//поле для хранения дескриптора потока
	HANDLE hThread;
	//поле для хранения идентификатора потока
	DWORD threadID;
public:
	//конструктор инициализации (передаем сюда пути до управляющей и тестовой программы)
	ProcessManager(LPWSTR path_);
	//деструктор для освобождения памяти
	~ProcessManager();

	//метод для создания дочернего процесса
	BOOL сreateChildProcess();
	//метод для создания отдельного потока для данного процесса
	void createThread();
	//статический метод потока
	static DWORD WINAPI threadFunction(LPVOID lpParam);
	//метод для эмуляции нажатия клавиши Enter в программах
	void emulationEnter();
	//метод для завершения процесса
	void exitProcess();

	//метод для получения информации о процессе
	//void getInfoProcess();
};