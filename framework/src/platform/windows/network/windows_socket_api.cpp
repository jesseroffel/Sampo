#include "sampo_pch.hpp"

#include "platform/windows/network/windows_socket_api.hpp"

#include <WinSock2.h>

namespace Sampo
{
    void WindowsSocketAPI::Init()
    {
        WSADATA startupResultData;
        int error = WSAStartup(MAKEWORD(2, 2), &startupResultData);
        if (error != 0)
        {
            SAMPO_CORE_CRITICAL("WSAStartup error: ({0})", WSAGetLastError());
        }
        s_Running = true;
    }

    void WindowsSocketAPI::Shutdown()
    {
        if (s_Running)
        {
            s_Running = false;

            int error = WSACleanup();
            if (error != 0)
            {
                SAMPO_CORE_ERROR("WSACleanup error: ({0})", WSAGetLastError());
            }
        }
    }
}