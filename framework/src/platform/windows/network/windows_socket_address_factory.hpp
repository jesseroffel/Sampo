#pragma once
#include "sampo/core/log.hpp"

#include "windows_socket_util.hpp"
#include "windows_socket_address.hpp"

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>

namespace Sampo
{
    class WindowsSocketAddressFactory
    {
    public:
        static SocketAddressPtr CreateEmpty() { return CreateRef<WindowsSocketAddress>(); }

        static SocketAddressPtr CreateIPv4(const uint32_t inAddress, const uint16_t inPort)
        {
            return CreateRef<WindowsSocketAddress>(inAddress, inPort);
        }

        static SocketAddressPtr CreateIPv4FromString(const std::string& inString)
        {
            return CreateIPFromString(inString, AF_INET);
        }

        static SocketAddressPtr CreateIPv6FromString(const std::string& inString)
        {
            return CreateIPFromString(inString, AF_INET6);
        }


        static SocketAddressPtr RetrieveAddressFromSocket(const Socket& inSocket)
        {
            SocketAddressPtr address = CreateEmpty();
            WindowsSocketUtil::GetSocketName(inSocket, *address.get());

            return address;
        }
    private:
        static SocketAddressPtr CreateIPFromString(const std::string& inString, int inFamily)
        {
            auto pos = inString.find_last_of(':');
            std::string host, service;
            if (pos != std::string::npos)
            {
                host = inString.substr(0, pos);
                service = inString.substr(pos + 1);
            }
            else
            {
                host = inString;
                service = "0"; // use default port
            }
            addrinfo hints;
            memset(&hints, 0, sizeof(hints));
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_family = inFamily;

            // Retrieve all host responses
            addrinfo* result;
            if (getaddrinfo(host.c_str(), service.c_str(), &hints, &result) != 0)
            {
                SAMPO_CORE_ERROR("CreateIPFromString getaddrinfo: ({0})", WSAGetLastError());
                freeaddrinfo(result);
                return nullptr;
            }

            // Loop until no more addrinfo structures are found
            while (!result->ai_addr && result->ai_next)
            {
                result = result->ai_next;
            }

            if (!result->ai_addr)
            {
                freeaddrinfo(result);
                return nullptr;
            }

            auto addrToReturn = CreateRef<WindowsSocketAddress>(*result->ai_addr);
            freeaddrinfo(result);

            return addrToReturn;
        }
    };
}