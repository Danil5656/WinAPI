#include "BaseProcessManager.h"
#include "Logger.h"

//реализация конструктора инициализации для родительского класса
BaseProcessManager::BaseProcessManager(const std::wstring path): path_{ path }, hProcess{ nullptr }{}

//реализация метода для получения пути
const std::wstring BaseProcessManager::GetPath() const noexcept { return path_; }

//реализация метода для получения идентификатора процесса
const HANDLE BaseProcessManager::GethProcess() const noexcept { return hProcess; }

//реализация статического метода для экранирования слешей в путях до программы
std::wstring BaseProcessManager::forkedSlashes(std::string& path)
{
	std::wstring doublePath;

	for (wchar_t i : path)
	{
		if (i == '\\')
		{
			doublePath += L"\\\\";
		}
		else
		{
			doublePath += i;
		}
	}

	return doublePath;
}

//реализация метода для создания дочернего процесса
bool BaseProcessManager::StartProcess()
{
	STARTUPINFO         si;		 //указатель на структуру, используемый для определения режима открытия нового процесса
	PROCESS_INFORMATION pi;		 //указатель на структуру для хранения дескриптора созданного процесса

	ZeroMemory(&si, sizeof(si)); //очистка памяти структуры STARTUPINFO
	si.cb = sizeof(si);			 //установка размера структуры
	ZeroMemory(&pi, sizeof(pi)); //очистка памяти структуры PROCESS_INFORMATION

	//создание процесса для cmd.exe и выполнение команд оттуда
	if (!CreateProcessW(NULL,                  //имя исполняемого модуля (нет имени, используется командный интерпретатор)
		const_cast<LPWSTR>(path_.c_str()),	   //команда, которую нужно выполнить
		NULL,                                  //указатель на структуру SECURITY_ATRIBUTES
		NULL,                                  //указатель на структуру SECURITY_ATRIBUTES
		TRUE,                                  //флаг наследования дескрипторов текущего процесса 
		CREATE_NEW_CONSOLE,                    //флаги способов создания процесса
		NULL,                                  //указатель на блок среды
		NULL,                                  //текущий диск или каталог
		&si,                                   //указатель на структуру STARTUPINFO
		&pi                                    //указатель на структуру PROCESS_INFORMATION
	))
	{
		std::cerr << "CreateProcess Failed. Error code: " << GetLastError() << std::endl;
		return false;
	}
	else
	{
		std::cout << "Process created successfully" << std::endl;
		hProcess = pi.hProcess;					//сохраняем идентификатор процесса
		return true;
	}

}

void BaseProcessManager::GetConsoleOutput()
{
	HANDLE hReadPipe;       //дескриптор чтения из канала
	HANDLE hWritePipe;      //дескриптор записи в канал

	//создание анонимного канала с одним концом для чтения и другим для записи
	if (!CreatePipe(&hReadPipe, &hWritePipe, NULL, 1024))
	{
		std::cerr << "CreatePipe Failed. Error code: " << GetLastError() << std::endl;
		return;
	}

	//замена дескриптора стандартного вывода текущего процесса на дескриптор записи в канал
	if (!SetStdHandle(STD_OUTPUT_HANDLE, hWritePipe))
	{
		std::cerr << "SetStdHandle Failed. Error code: " << GetLastError() << std::endl;
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		return;
	}

	//запуск процесса KOSH.bat
	if (!StartProcess())
	{
		std::cerr << "StartProcess Failed" << std::endl;
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		return;
	}

	//закрытие дескриптора записи в канал, чтобы данные из него можно было прочитать
	CloseHandle(hWritePipe);

	std::string output;
	char buffer[4096];
	DWORD bytesRead;

	//чтение данных из канала и запись их в строку output
	while (ReadFile(hReadPipe, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0)
	{
		output.append(buffer, bytesRead);
	}

	//закрытие дескриптора чтения из канала
	CloseHandle(hReadPipe);

	std::cout << "Output: " << output << std::endl;
}

//реализация метода по получению информации о процессе
void BaseProcessManager::GetInfoProcess()
{
	//создаем структуру для хранения статистики памяти о процессе
	PROCESS_MEMORY_COUNTERS pmc;

	//функция для извлеченеия сведения об использовании памяти указанного процесса
	if (!GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc)))
	{
		std::cout << "Failed to get process information. Error code: " << GetLastError() << std::endl;
		return;
	}
	else
	{
		std::cout << "WorkingSetSize\t-\t"			   << pmc.WorkingSetSize			 << std::endl;
		std::cout << "PageFaultCount\t-\t"			   << pmc.PageFaultCount		     << std::endl;
		std::cout << "PagefileUsage\t-\t"			   << pmc.PagefileUsage			     << std::endl;
		std::cout << "PeakPagefileUsage\t-\t"		   << pmc.PeakPagefileUsage			 << std::endl;
		std::cout << "PeakWorkingSetSize\t-\t"		   << pmc.PeakWorkingSetSize		 << std::endl;
		std::cout << "QuotaNonPagedPoolUsage\t-\t"	   << pmc.QuotaNonPagedPoolUsage	 << std::endl;
		std::cout << "QuotaPagedPoolUsage\t-\t"		   << pmc.QuotaPagedPoolUsage		 << std::endl;
		std::cout << "QuotaPeakNonPagedPoolUsage\t-\t" << pmc.QuotaPeakNonPagedPoolUsage << std::endl;
		std::cout << "QuotaPeakPagedPoolUsage\t-\t"	   << pmc.QuotaPeakPagedPoolUsage	 << std::endl;
		std::cout << std::endl;
	}
}

//реализация метода по завершению процесса
void BaseProcessManager::StopProcess()
{
	if (hProcess != NULL)
	{
		CloseHandle(hProcess);											//закрываем дескриптор процесса
		std::cout << "Process completed successfully!" << std::endl;	//выводим сообщение об успешном завершении процесса
	}
}

//реализация метода 
void BaseProcessManager::CalculateProcessTime(){}

//реализация метода по записи вывода программы в строку
/*void BaseProcessManager::GetConsoleOutput()
{
	HANDLE hReadPipe;		//дескриптор чтения из канала
	HANDLE hWritePipe;		//дескриптор записи в канал

	//создание анонимного канала с одним концом для чтения и другим для записи
	if (!CreatePipe(&hReadPipe, &hWritePipe, NULL, 1024))
	{
		std::cerr << "CreatePipe Failed. Error code: " << GetLastError() << std::endl;
		return;
	}

	//замена дескриптора стандартного вывода текущего процесса на дескриптор записи в канал
	if (!SetStdHandle(STD_OUTPUT_HANDLE, hWritePipe))
	{
		std::cerr << "SetStdHandle Failed. Error code: " << GetLastError() << std::endl;
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		return;
	}

	//запуск процесса KOSH.bat
	if (!StartProcess())
	{
		std::cerr << "StartProcess Failed" << std::endl;
		CloseHandle(hReadPipe);
		CloseHandle(hWritePipe);
		return;
	}

	//закрытие дескриптора записи в канал, чтобы данные из него можно было прочитать
	//CloseHandle(hWritePipe);

	std::string output;
	char buffer[4096];
	DWORD bytesRead;

	//чтение данных из канала и запись их в строку output
	while (ReadFile(hReadPipe, buffer, sizeof(buffer), &bytesRead, NULL))
	{
		output.append(buffer, bytesRead);
	}

	//закрытие дескриптора чтения из канала
	CloseHandle(hReadPipe);

	std::cout << "Output: " << output << std::endl;
}
*/