#pragma once
#include "sampo/network/socket_address.hpp"

namespace Sampo
{
    class Socket
    {
    public:
        virtual ~Socket() = default;

        const SOCKET& GetSocket() const { return m_Socket; }
    protected:
        Socket(SOCKET inSocket) : m_Socket(inSocket) {}
        SOCKET m_Socket{ 0 };
    };
}