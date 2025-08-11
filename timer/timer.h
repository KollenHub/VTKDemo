#pragma once
#include <string>
#include <chrono>
class timer
{
private:
    std::string m_Name;
    std::chrono::high_resolution_clock::time_point m_Start;
    std::chrono::high_resolution_clock::time_point m_End;
public:
    timer(const std::string& name);
    ~timer();
};