#pragma once
#include "socket_address.hpp"
#include "socket_api.hpp"

#include "platform/windows/network/windows_socket_address_factory.hpp"

namespace Sampo
{
    class SocketAddressFactory
    {
    public:
        static SocketAddressPtr CreateEmptyAddress()
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketAddressFactory::CreateEmpty();
            }
            return nullptr;
        }

        static SocketAddressPtr CreateIPv4(uint32_t inAddress, uint16_t inPort = {})
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketAddressFactory::CreateIPv4(inAddress, inPort);
            }
            return nullptr;
        }


        static SocketAddressPtr CreateIPv4FromString(const std::string& inString)
        {
            switch(SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketAddressFactory::CreateIPv4FromString(inString);
            }
            return nullptr;
        }

        static SocketAddressPtr CreateIPv6FromString(const std::string& inString)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketAddressFactory::CreateIPv6FromString(inString);
            }
            return nullptr;
        }

        static SocketAddressPtr RetrieveAddressFromSocket(const Socket& inSocket)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketAddressFactory::RetrieveAddressFromSocket(inSocket);
            }
            return nullptr;
        }
    };
}