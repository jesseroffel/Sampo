#pragma once
#include "network_definitions.hpp"

#include <memory>

namespace Sampo
{
    class SocketAddress
    {
    public:
        virtual std::size_t GetSize() const = 0;
        virtual const std::string GetAddressToString() = 0;
        virtual const std::string GetFullAddressToString() = 0;
        const sockaddr& GetSockAddr() const { return m_SockAddr; }
    protected:
        // IPv4
        SocketAddress() { memset(&m_SockAddr, 0, sizeof(sockaddr)); }

        // Wrap sockaddr
        SocketAddress(const sockaddr& inSockAddr)
        {
            memcpy(&m_SockAddr, &inSockAddr, sizeof(sockaddr));
        }

        sockaddr_in*  GetAsSockAddrIPv4() { return reinterpret_cast<sockaddr_in*>(&m_SockAddr); }
        sockaddr_in6* GetAsSockAddrIPv6() { return reinterpret_cast<sockaddr_in6*>(&m_SockAddr); }

        sockaddr m_SockAddr{};

    private:
        friend class SocketUtil;
    };

    using SocketAddressPtr = std::shared_ptr<SocketAddress>;
}