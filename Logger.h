#pragma once
#define LOG(X) Logger::GetInstance().Log([&](std::ostream& o) { o << X; })

#include <string_view>
#include <fstream>
#include <ostream>
#include <iostream>
#include <thread>
#include <minwinbase.h>
#include <sysinfoapi.h>
#include <mutex>

using namespace std::literals;

class Logger
{
    static std::string GetTimeStamp()
    {
        SYSTEMTIME st;
        GetSystemTime(&st);
        char currentTime[84] = "";

        sprintf_s(currentTime, "%d/%d/%dT%02d:%02d:%02d.%03dZ", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);

        return std::string(currentTime);
    }

    Logger() = default;

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    static Logger& GetInstance()
    {
        static Logger obj;
        return obj;
    }

    template<typename Func>
    void Log(Func&& cb)
    {
        m_.lock();

        log_file_ << GetTimeStamp() << ": ";
        cb(log_file_);
        log_file_ << std::endl;

        m_.unlock();
    }

private:
    std::ofstream log_file_{ "sample.log", std::ios::app };
    mutable std::mutex m_;
};