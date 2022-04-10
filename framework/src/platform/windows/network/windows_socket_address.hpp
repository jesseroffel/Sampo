#pragma once
#include "sampo/network/socket_address.hpp"
#include "platform/windows/io/windows_string_helper.hpp"

namespace Sampo
{
    class WindowsSocketAddress : public SocketAddress
    {
    public:
        WindowsSocketAddress() : SocketAddress() {}
        WindowsSocketAddress(const SocketAddress& address) : SocketAddress(address.GetSockAddr()) {}

        WindowsSocketAddress(uint32_t inAddress, uint16_t inPort)
            : SocketAddress() 
        {
            GetAsSockAddrIPv4()->sin_family = AF_INET;
            GetAsSockAddrIPv4()->sin_addr.S_un.S_addr = htonl(inAddress);
            GetAsSockAddrIPv4()->sin_port = htons(inPort);
        }

        WindowsSocketAddress(const sockaddr& inSockAddr)
            : SocketAddress(inSockAddr) {} 

        virtual std::size_t GetSize() const override { return sizeof(sockaddr); }

        virtual const std::string GetAddressToString() override
        {
            return WindowStringHelper::utf8_encode(GetAddressToWString());
        }

        virtual const std::string GetFullAddressToString() override
        {
            std::string address = WindowStringHelper::utf8_encode(GetAddressToWString());
            address.append(":");
            uint16_t port = (m_SockAddr.sa_family == AF_INET) ? ntohs(GetAsSockAddrIPv4()->sin_port) : ntohs(GetAsSockAddrIPv6()->sin6_port);
            address.append(std::to_string(port));
            return address;
        }

        const std::wstring GetAddressToWString()
        {
            wchar_t buffer[INET6_ADDRSTRLEN] = {};
            switch (m_SockAddr.sa_family)
            {
                case AF_INET:
                {
                    sockaddr_in* addr_in = GetAsSockAddrIPv4();
                    if(InetNtopW(addr_in->sin_family, &addr_in->sin_addr, buffer, INET_ADDRSTRLEN) == nullptr)
                        SAMPO_CORE_ERROR("GetAddressToWString: {0}", WSAGetLastError());

                    break;
                }
                case AF_INET6:
                {
                    sockaddr_in6* addr_in = GetAsSockAddrIPv6();
                    if (InetNtopW(addr_in->sin6_family, &addr_in->sin6_addr, buffer, INET6_ADDRSTRLEN) == nullptr)
                        SAMPO_CORE_ERROR("GetAddressToWString: {0}", WSAGetLastError());

                    break;
                }
            }

            return std::wstring{ buffer };
        }

    private:
        friend class WindowsUDPSocket;
        friend class WindowsTCPSocket;
        friend class WindowsSocketUtil;
    };
}