#include "sampo_pch.hpp"
#include "sampo/network/socket_api.hpp"

#include "platform/windows/network/windows_socket_api.hpp"

namespace Sampo
{
    SocketAPI::SocketLibrary SocketAPI::s_SocketAPI = SocketAPI::SocketLibrary::WinSock2;
    bool SocketAPI::s_Running = false;

    Scope<SocketAPI> SocketAPI::Create()
    {
        switch (s_SocketAPI)
        {
            case SocketAPI::SocketLibrary::Undefined: SAMPO_CORE_CRITICAL("SocketAPI::Undefined is currently not supported!"); return nullptr;
            case SocketAPI::SocketLibrary::WinSock2:  return CreateScope<WindowsSocketAPI>();
        }

        SAMPO_CORE_CRITICAL("Unknown SocketAPI!");
        return nullptr;
    }
}