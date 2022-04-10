#include "sampo_pch.hpp"

#include "platform/windows/network/windows_udp_socket.hpp"
#include "sampo/network/network_definitions.hpp"

#include <WinSock2.h>

namespace Sampo
{
    WindowsUDPSocket::~WindowsUDPSocket()
    {
        int error = closesocket(m_Socket);
        if (error != SOCKET_NO_ERROR)
        {
            SAMPO_CORE_ERROR("UDPSocket::closesocket {0}", WSAGetLastError());
        }
    }

    int WindowsUDPSocket::Bind(const SocketAddress& inBindAddress)
    {
        auto inLength = static_cast<int>(inBindAddress.GetSize());
        int error = bind(m_Socket, &inBindAddress.GetSockAddr(), inLength);
        if (error != 0)
        {
            SAMPO_CORE_ERROR("UDPSocket::Bind {0}", WSAGetLastError());
            return WSAGetLastError();
        }
        return SOCKET_NO_ERROR;
    }

    int WindowsUDPSocket::SentTo(const void* inData, int inLength, const SocketAddress& inToAddress)
    {
        auto ToLength = static_cast<int>(inToAddress.GetSize());
        int byteSentCount = sendto(m_Socket, static_cast<const char*>(inData), inLength, 0, &inToAddress.GetSockAddr(), ToLength);
        if (byteSentCount >= 0)
        {
            return byteSentCount;
        }
        else
        {
            SAMPO_CORE_ERROR("UDPSocket::SentTo {0}", -WSAGetLastError());
            return -WSAGetLastError();
        }
    }

    int WindowsUDPSocket::ReceiveFrom(void* inBuffer, int inLength, SocketAddress& outFromAddress)
    {
        WindowsSocketAddress WinSocketAddress{ outFromAddress.GetSockAddr() };

        auto fromLength = static_cast<int>(outFromAddress.GetSize());
        int readByteCount = recvfrom(m_Socket, static_cast<char*>(inBuffer), inLength, 0, &WinSocketAddress.m_SockAddr, &fromLength);
        if (readByteCount >= 0)
        {
            return readByteCount;
        }
        else
        {
            SAMPO_CORE_ERROR("UDPSocket::ReceiveFrom {0}", -WSAGetLastError());
            return -WSAGetLastError();
        }
    }

    int WindowsUDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
    {
        u_long arg = inShouldBeNonBlocking ? 1 : 0;
        int result = ioctlsocket(m_Socket, FIONBIO, &arg);
        if (result == SOCKET_ERROR)
        {
            SAMPO_CORE_ERROR("UDPSocket::SetNonBlockingMode {0}", WSAGetLastError());
            return WSAGetLastError();
        }
        return SOCKET_NO_ERROR;
    }
}

