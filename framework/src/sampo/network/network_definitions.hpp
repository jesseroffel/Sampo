#pragma once
#include "sampo/core/platforms.hpp"

// SOCKETS
#define SOCKET_NO_ERROR 0

#ifdef SAMPO_PLATFORM_WINDOWS
    #include <Ws2def.h>
    #include <ws2tcpip.h>
    #include <ws2ipdef.h>
#endif // SAMPO_PLATFORM_WINDOWS

namespace Sampo
{
    enum class ESocketAddressFamily
    {
        INET = AF_INET,
        INET6 = AF_INET6
    };
}