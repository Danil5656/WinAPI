#pragma once
#include "BaseProcessManager.h"

class TestApp : public BaseProcessManager
{
public:
	TestApp(const std::wstring &path_);
};