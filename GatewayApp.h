#pragma once
#include "BaseProcessManager.h"

class GatewayApp : public BaseProcessManager
{
public:
	//конструктор инициализации
	GatewayApp(const std::wstring& path_);
	//метод для имитации нажатия клавиши Enter
	void EmulationEnter();
};
