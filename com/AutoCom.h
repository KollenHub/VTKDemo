
#pragma once
#include <objbase.h>
#include <stdexcept>
#include <iostream>
#include <string>

class AutoCOM
{
public:

    // 默认 STA 模式，可以自定义错误回调
    AutoCOM()
    {
        std::cout << "AutoCOM::AutoCOM()" << std::endl;
        HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
        if (FAILED(hr))
        {
            if (hr != RPC_E_CHANGED_MODE)
            { // 如果线程已经用不同模式初始化，忽略

                throw std::runtime_error("COM init failed: 0x" + std::to_string(hr));
            }
        }
        m_initialized = true;
    }

    ~AutoCOM()
    {
        if (m_initialized)
        {
            CoUninitialize();
        }
    }

    // 禁止拷贝（避免多次释放）
    AutoCOM(const AutoCOM &) = delete;
    AutoCOM &operator=(const AutoCOM &) = delete;

    static void Init();

private:
    bool m_initialized = false;
};
