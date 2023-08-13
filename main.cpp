#include "ProcessManager.h"

int main()
{
	std::wcout << L"Enter the path to the control program: ";	//D:\test\testProject.exe
	std::wstring controlPath;
	std::wcin >> controlPath;

	std::wcout << L"Enter the path to the test program: ";      //D:\test\ATLAS.exe
	std::wstring testPath;
	std::wcin >> testPath;

	//преобразуем пути для управляющей и тестовой программы к типу LPWSTR (wchar_t*)
	LPWSTR controlProgramPath = const_cast<LPWSTR>(controlPath.data());
	LPWSTR testProgramPath    = const_cast<LPWSTR>(testPath.data());

	//создаем два экземпляра класса и передаем в конструктор соответствующие пути
	ProcessManager controlProgram { controlProgramPath };
	ProcessManager testProgram	  { testProgramPath };

	//запускам управляющую и тестовую программу, создаем для них отдельные потоки и процессы
	controlProgram.createThread();
	testProgram.createThread();

	//завершаем оба процесса
	controlProgram.exitProcess();
	testProgram.exitProcess();

	system("PAUSE");
	return 0;
}