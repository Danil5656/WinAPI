#pragma once
#include "BaseProcessManager.h"

class GatewayApp : public BaseProcessManager
{
public:
	//����������� �������������
	GatewayApp(const std::wstring& path_);
	//����� ��� �������� ������� ������� Enter
	void EmulationEnter();
};
