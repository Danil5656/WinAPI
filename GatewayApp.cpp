#include "GatewayApp.h"

//���������� ������������ ������������� ��� ��������� ������
GatewayApp::GatewayApp(const std::wstring& path_) : BaseProcessManager{ path_ } {}

//����� ��� �������� ������� ������� Enter � ���������� ��������� ������
void GatewayApp::EmulationEnter()
{
	//���� 1 �������
	Sleep(1000);

	//�������� � ��������� ��������� input
	INPUT input;
	input.type = INPUT_KEYBOARD;
	input.ki.wVk = VK_RETURN;
	input.ki.dwFlags = 0;

	//���������� ������� ������� Enter
	SendInput(1, &input, sizeof(INPUT));
}