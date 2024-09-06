#pragma once
#include "sampo/core/core_definitions.hpp"

// TODO add platform check/move to .cpp
#include "windows_udp_socket.hpp"
#include "windows_tcp_socket.hpp"

// TODO add platform check/move to .cpp
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <ws2def.h>

namespace Sampo
{
    class WindowsSocketUtil
    {
    public:
        static SOCKET CreateSocket(ESocketAddressFamily inFamily, int inSocketType, int inProtocol)
        {
            SOCKET soc = socket(static_cast<int>(inFamily), inSocketType, inProtocol);
            if (soc == INVALID_SOCKET)
            {
                SAMPO_CORE_ERROR("CreateSocket failed with error: {0}", WSAGetLastError());
                return INVALID_SOCKET;
            }

            return soc;
        }

        static WindowsUDPSocketPtr CreateUDPSocket(ESocketAddressFamily inFamily)
        {
            SOCKET socket = CreateSocket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
            if (socket == INVALID_SOCKET)
                return nullptr;

            return CreateRef<WindowsUDPSocket>(socket);
        }

        static WindowsTCPSocketPtr CreateTCPSocket(ESocketAddressFamily inFamily)
        {
            SOCKET socket = CreateSocket(inFamily, SOCK_STREAM, IPPROTO_TCP);
            if (socket == INVALID_SOCKET)
                return nullptr;

            return CreateRef<WindowsTCPSocket>(socket);
        }

        static fd_set* FillSetFromVector(fd_set& outSet, const TCPSocketVector* inSockets)
        {
            if (inSockets)
            {
                FD_ZERO(&outSet);
                for (const TCPSocketPtr& socket : *inSockets)
                {
                    const WindowsTCPSocket* wSocket = dynamic_cast<WindowsTCPSocket*>(socket.get());
                    FD_SET(wSocket->m_Socket, &outSet);
                }
                return &outSet;
            }
            return nullptr;
        };

        static void FillVectorFromSet(TCPSocketVector* outSockets, const TCPSocketVector* inSockets, const fd_set& inSet)
        {
            if (inSockets && outSockets)
            {
                outSockets->clear();
                for (const TCPSocketPtr& socket : *inSockets)
                {
                    const WindowsTCPSocket* wSocket = dynamic_cast<WindowsTCPSocket*>(socket.get());
                    if (FD_ISSET(wSocket->m_Socket, &inSet))
                    {
                        outSockets->push_back(socket);
                    }
                }
            }
        }

        static int Select(const TCPSocketVector* inReadSet, TCPSocketVector* outReadSet,
                          const TCPSocketVector* inWriteSet, TCPSocketVector* outWriteSet,
                          const TCPSocketVector* inExceptSet, TCPSocketVector* outExceptSet)
        {
            // build up some sets from our vectors
            fd_set read, write, except;

            fd_set* readPtr = FillSetFromVector(read, inReadSet);
            fd_set* writePtr = FillSetFromVector(read, inWriteSet);
            fd_set* exceptPtr = FillSetFromVector(read, inExceptSet);

            int toReturn = select(0, readPtr, writePtr, exceptPtr, nullptr);
            if (toReturn > 0)
            {
                FillVectorFromSet(outReadSet, inReadSet, read);
                FillVectorFromSet(outWriteSet, inWriteSet, write);
                FillVectorFromSet(outExceptSet, inExceptSet, except);
            }
            return toReturn;
        }

        static int GetSocketName(const Socket& socket, SocketAddress& outAddress, int addressSize = -1)
        {
            if (addressSize == -1)
                addressSize = sizeof(outAddress);

            auto& winSockAddr = static_cast<WindowsSocketAddress&>(outAddress);

            return getsockname(socket.GetSocket(), &winSockAddr.m_SockAddr, &addressSize);
        }

        static int SetSocketOption(const Socket& inSocket, int inOptionLevel, int inOptionName, const char* inOptionValue, int inOptionLength)
        {
            int resultCode = setsockopt(inSocket.GetSocket(), inOptionLevel, inOptionName, inOptionValue, inOptionLength);
            if (resultCode == SOCKET_ERROR)
                SAMPO_CORE_ERROR("SetSocketOption failed with error: {0}", WSAGetLastError());
        }
    };
}