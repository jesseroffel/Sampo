#include "sampo_pch.hpp"

#include "windows_tcp_socket.hpp"

namespace Sampo
{
    WindowsTCPSocket::~WindowsTCPSocket()
    {
        int error = closesocket(m_Socket);
        if (error != SOCKET_NO_ERROR)
        {
            SAMPO_CORE_ERROR("TCPSocket::closesocket {0}", WSAGetLastError());
        }
    }

    int WindowsTCPSocket::Connect(const SocketAddress& inAddress)
    {
        auto inAddrSize = static_cast<int>(inAddress.GetSize());
        int error = connect(m_Socket, &inAddress.GetSockAddr(), inAddrSize);
        if (error < 0)
        {
            SAMPO_CORE_ERROR("TCPSocket::connect {0}", WSAGetLastError());
            return -WSAGetLastError();
        }
        return SOCKET_NO_ERROR;
    }

    int WindowsTCPSocket::Bind(const SocketAddress& inToAddress)
    {
        auto inLength = static_cast<int>(inToAddress.GetSize());
        int error = bind(m_Socket, &inToAddress.GetSockAddr(), inLength);
        if (error != 0)
        {
            SAMPO_CORE_ERROR("TCPSocket::Bind {0}", WSAGetLastError());
            return WSAGetLastError();
        }
        return SOCKET_NO_ERROR;
    }

    int WindowsTCPSocket::Listen(int inBacklog)
    {
        int error = listen(m_Socket, inBacklog);
        if (error < 0)
        {
            SAMPO_CORE_ERROR("TCPSocket::Listen {0}", WSAGetLastError());
            return -WSAGetLastError();
        }
        return SOCKET_NO_ERROR;
    }

    Ref<TCPSocket> WindowsTCPSocket::Accept(SocketAddress& inFromAddress)
    {
        auto WinFromAddress = static_cast<WindowsSocketAddress*>(&inFromAddress);

        auto addrLength = static_cast<int>(inFromAddress.GetSize());
        SOCKET newSocket = accept(m_Socket, &WinFromAddress->m_SockAddr, &addrLength);
        
        if (newSocket != INVALID_SOCKET)
        {
            return CreateRef<WindowsTCPSocket>(newSocket);
        }
        SAMPO_CORE_ERROR("TCPSocket::Accept {0}", WSAGetLastError());
        return nullptr;
    }

    int WindowsTCPSocket::Send(const void* inData, int inLength)
    {
        int bytesSentCount = send(m_Socket, static_cast<const char*>(inData), inLength, 0);
        if (bytesSentCount < 0)
        {
            SAMPO_CORE_ERROR("TCPSocket::Send {0}", WSAGetLastError());
            return -WSAGetLastError();
        }
        return bytesSentCount;
    }

    int WindowsTCPSocket::Receive(void* inBuffer, int inLength)
    {
        int bytesReceivedCount = recv(m_Socket, static_cast<char*>(inBuffer), inLength, 0);
        if (bytesReceivedCount < 0)
        {
            SAMPO_CORE_ERROR("TCPSocket::Receive {0}", WSAGetLastError());
            return -WSAGetLastError();
        }
        return bytesReceivedCount;
    }
}

