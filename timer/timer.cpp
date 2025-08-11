#include "timer.h"
#include <iostream>
timer::timer(const std::string &name):m_Name(name)
{
    m_Start = std::chrono::high_resolution_clock::now();
}

timer::~timer()
{
    m_End = std::chrono::high_resolution_clock::now();

    std::cout << "Timer::<" << m_Name << "> taken " << std::chrono::duration_cast<std::chrono::milliseconds>(m_End - m_Start).count() << "ms" << std::endl;
}
