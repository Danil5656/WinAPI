#include "TestApp.h"

//реализация конструктора инициализации для дочернего класса
TestApp::TestApp(const std::wstring & path_) : BaseProcessManager{ path_ } {}