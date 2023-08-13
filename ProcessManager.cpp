#include "ProcessManager.h"

//реализация конструктора инициализации
ProcessManager::ProcessManager(const LPWSTR path_)
{
	size_t length = wcslen(path_);	  //вычисляем длину path
	path = new wchar_t[length + 1];	  //выделяем память под строку и под завершающий символ '\0'

	for (uint32_t i = 0; i < length; ++i)
	{
		path[i] = path_[i];			  //посимвольное присваивание строки
	}

	path[length] = '\0';			  //добавление завершающего символа '\0' в конец строки

	hProcess = nullptr;				  //присваивание нулевого указателя дескриптору процесса
	hThread  = nullptr;				  //присваивание нулевого указателя дескриптору потока
	threadID = NULL;			      //присваивание константы нулевого указателя идентификатору потока
}

//реализация деструктора для освобождения памяти
ProcessManager::~ProcessManager()
{
	delete[] path;
}

//реализация метода для создания дочернего процесса
BOOL ProcessManager::сreateChildProcess()
{
	STARTUPINFO         si;	//указатель на структуру, используемый для определения режима открытия нового процесса
	PROCESS_INFORMATION pi;	//указатель на структуру для хранения дескриптора созданного процесса

	ZeroMemory(&si, sizeof(si));	//очистка памяти структуры STARTUPINFO
	si.cb = sizeof(si);				//установка размера структуры
	ZeroMemory(&pi, sizeof(pi));	//очистка памяти структуры PROCESS_INFORMATION

	//запускаем фунцию создания дочернего процесса
	if (!CreateProcess(NULL,		//имя исполняемого модуля (нет имени, используется консоль)
					   path,		//имя исполняемого файла, которым будет пользоваться новый процесс
					   NULL,		//указатель на структуру SECURITY_ATRIBUTES
					   NULL,		//указатель на структуру SECURITY_ATRIBUTES
					   TRUE,		//флаг наследования дескрипторов текущего процесса		
					   NULL,		//флаги способов создания процесса
					   NULL,		//указатель на блок среды
					   NULL,		//текущий диск или каталог
					   &si,			//указатель на структуру STARTUPINFO
					   &pi			//указатель на структуру PROCESS_INFORMATION
	))
	{
		//выводим сообщение об ошибке с кодом завершения, если создание процесса не удалось
		std::cerr << "Process creation error. Error code: " << GetLastError() << std::endl;
		return false;
	}
	else
	{
		std::cout << "Process created successfully" << std::endl; //выводим сообщение об успешном создании процесса
		WaitForSingleObject(pi.hProcess, INFINITE);			      //ожидание, пока потоки завершатся

		//_getch();	//команда паузы (считывает один символ с клавиатуры, но на экран он не выводится) 

		hProcess = pi.hProcess;	//сохраняем идентификатор процесса
		hThread = pi.hThread;	//сохраняем идентификатор потока

		return true;			//успешное завершение работы функции
	}
}

// Метод для эмуляции нажатия клавиши Enter в запущенном процессе.
void ProcessManager::emulationEnter()
{
	//создаем структуру для отправки клавиатурных событий.
	INPUT input;
	input.type = INPUT_KEYBOARD; //указываем тип события (клавиатурное)

	//нажатие клавиши Enter
	input.ki.wVk = VK_RETURN;   //указываем виртуальный код клавиши Enter.
	input.ki.dwFlags = 0;       //указываем флаг, означающий нажатие клавиши.

	//отправляем событие ввода (нажатие клавиши)
	SendInput(1, &input, sizeof(INPUT));

	//ожидание перед отправкой события отпускания клавиши.
	Sleep(10); //может потребоваться настройка времени ожидания

	//отпускание клавиши Enter.
	input.ki.dwFlags = KEYEVENTF_KEYUP; //указываем флаг, означающий отпускание клавиши

	//отправляем событие ввода (отпускание клавиши)
	SendInput(1, &input, sizeof(INPUT));
}

//реализация метода для создания отдельного потока для данного процесса
void ProcessManager::createThread()
{
	//проверяем что процесс успешно создался
	if (сreateChildProcess())
	{
		//создаем отдельный поток для данного процесса
		hThread = CreateThread(NULL,									//дескриптор защиты
							   0,										//размер стека (по-умолчанию 1 МБ)
							   threadFunction,							//указатель на потоковую функцию
							   NULL,									//параметр потока (NULL)
							   0,									    //флаги создания потока
							   &threadID							    //идентификатор потока
		);
		//проверяем поток на успешность создания
		if (hThread)
		{
			std::cout << "Thread creating successfully!" << std::endl;
			//вызываем функцию эмуляции нажатия клавиши Enter в созданном процессе
			emulationEnter();
		}
	}
}

DWORD WINAPI ProcessManager::threadFunction(LPVOID lpParam)
{
	//приводим параметр обратно к типу ProcessManager
	ProcessManager* pManager = static_cast<ProcessManager*>(lpParam);

	//выводим сообщение что поток выполняется
	std::cout << "Thread is executing..." << std::endl;

	//здесь можно добавить любой код, который нужно выполнить внутри потока

	// Возвращаем код завершения потока
	return 0;
}

//реализация метода по завершению процесса
void ProcessManager::exitProcess()
{
	if (hProcess != NULL)
	{
		TerminateProcess(hProcess, 0);									//функция для завершения процесса и всех его потоков
		CloseHandle(hProcess);											//закрываем дескриптор процесса
		CloseHandle(hThread);											//закрываем дескриптор потока
		std::cout << "Process completed successfully!" << std::endl;	//выводим сообщение об успешном завершении процесса
	}
}

//реализация метода по получению информации о процессе
//void ProcessManager::getInfoProcess(){}