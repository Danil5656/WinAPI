#include "BaseProcessManager.h"
#include "Logger.h"
#include "GatewayApp.h"
#include "TestApp.h"

//WinAPI.exe C:\Users\Ilya\Desktop\WinApiData\Gateway\KOSH.bat C:\Users\Ilya\Desktop\WinApiData\Test\KOSH.exe

//int main(int argc, char* argv[])
int main()
{
	//запуск с прототипом int main(int argc, char* argv[])
	/*if (argc != 3)
	{
		std::cerr << "Invalid number of arguments!" << std::endl;
		exit(1);
	}

	std::string tmp1(argv[1]);
	std::string tmp2(argv[2]);
	std::cout << tmp1 << '\n' << tmp2 << std::endl;

	std::wstring controlPath = BaseProcessManager::forkedSlashes(tmp1);
	std::wstring testPath    = BaseProcessManager::forkedSlashes(tmp2);
	std::wcout << controlPath << '\n' << testPath << std::endl;

	controlPath = L"cmd.exe /C cd /d " + controlPath.substr(0, controlPath.rfind(L"\\\\")) + L" && " + controlPath.substr(controlPath.rfind(L"\\") + 1);
	testPath    = L"cmd.exe /C cd /d " + testPath.substr(0, testPath.rfind(L"\\\\")) + L" && " + testPath.substr(testPath.rfind(L"\\") + 1) + L" KOSH 127.0.0.1:11000 & pause";
	//testPath    = L"cmd.exe /C cd /d " + testPath.substr(0, testPath.rfind(L"\\\\")) + L" && " + testPath.substr(testPath.rfind(L"\\") + 1) + L" KOSH 127.0.0.1:11000 >> C:\\Users\\Ilya\\Desktop\\tmp.txt & pause";

	//std::wcout << controlPath << std::endl;
	//std::wcout << testPath    << std::endl;

	//создаем два экземпляра класса для управляющей и тестовой программы
	GatewayApp controlProgram{ controlPath };
	TestApp	    testProgram{ testPath };
	*/



	//запуск с прототипом int main()
	//const std::wstring controlPath = L"cmd.exe /C cd /d C:\\Users\\Счастливый Мощный ПК\\OneDrive\\Рабочий стол\\Work\\ProjectVS\\lite\\lite\\Debug && CALL lite.exe & pause";
	//const std::wstring path_ = L"C:\\Windows\\System32\\cmd.exe /C \"cd /d C:\\Gateway && KOSH.bat\"";
	//const std::wstring controlPath = L"C:\\Windows\\System32\\cmd.exe /C \"cd /d C:\\Users\\Счастливый Мощный ПК\\OneDrive\\Рабочий стол\\WinApiData\\Gateway && KOSH.bat\"";
	const std::wstring controlPath = L"cmd.exe /C cd /d C:\\Users\\Счастливый Мощный ПК\\OneDrive\\Рабочий стол\\WinApiData\\Gateway && KOSH.bat";
	const std::wstring testPath    = L"cmd.exe /C cd /d C:\\Users\\Счастливый Мощный ПК\\OneDrive\\Рабочий стол\\WinApiData\\Test && CALL KOSH.exe KOSH 127.0.0.1:11000 & pause";

	//создаем два экземпляра класса для управляющей и тестовой программы
	GatewayApp controlProgram{ controlPath };
	TestApp	    testProgram   { testPath };

	//начало работы программы
	for (int i = 0; i < 1; ++i)
	{
		auto res1 = std::async([&controlProgram]()
			{
				//controlProgram.StartProcess();
				controlProgram.GetConsoleOutput();
				controlProgram.EmulationEnter();
				controlProgram.GetInfoProcess();
				//do something
				controlProgram.StopProcess();
			});
		auto res2 = std::async([&testProgram]()
			{
				Sleep(2000);
				//testProgram.StartProcess();
				testProgram.GetConsoleOutput();
				testProgram.GetInfoProcess();
				// Do something
				testProgram.StopProcess();
			});
		//метод для приостановки потока
		res1.wait();
		res2.wait();
	}

	system("PAUSE");
	return 0;
}