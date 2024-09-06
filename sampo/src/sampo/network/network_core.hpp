#pragma once
#include "sampo/core/platforms.hpp"

#ifdef SAMPO_PLATFORM_WINDOWS
    #include <WinSock2.h>
    #include <WS2tcpip.h>

    #pragma comment(lib, "Ws2_32.lib")
#else
    #error Sampo currently only supports networking using Windows
#endif //SAMPO_PLATFORM_WINDOWS

//POSIX
// sys/socket.h 
// netinet/in.h // ipv4 functionality
// apra/inet.h  // address conversion
// netdb.h      // name resolution

#include "network_definitions.hpp"