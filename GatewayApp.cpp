#include "GatewayApp.h"

//реализаци€ конструктора инициализации дл€ дочернего класса
GatewayApp::GatewayApp(const std::wstring& path_) : BaseProcessManager{ path_ } {}

//метод дл€ эмул€ции нажати€ клавиши Enter в запущенной командной строке
void GatewayApp::EmulationEnter()
{
	//ждем 1 секунду
	Sleep(1000);

	//объвл€ем и заполн€ем структуру input
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_RETURN;
	input.ki.dwFlags = 0;

	//отправл€ем нажатие клавиши Enter
	SendInput(1, &input, sizeof(INPUT));
}