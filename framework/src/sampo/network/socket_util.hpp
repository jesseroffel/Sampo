#pragma once
#include "network_definitions.hpp"
#include "socket_api.hpp"

// TODO add platform check
#include "platform/windows/network/windows_socket_util.hpp"

#include <vector>

namespace Sampo
{
    class SocketUtil
    {
    public:
        static bool IsRunning()
        {
            if (!Sampo::SocketAPI::IsRunning())
            {
                SAMPO_ERROR("Unable to process SocketAPI call as no valid Socket API instance is running");
                return false;
            }

            return true;
        }

        // Creation
        static UDPSocketPtr CreateUDPSocket(ESocketAddressFamily inFamily)
        {
            if (!IsRunning())
                return nullptr;

            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketUtil::CreateUDPSocket(inFamily);
            }
            return nullptr;
        }

        static TCPSocketPtr CreateTCPSocket(ESocketAddressFamily inFamily)
        {
            if (!IsRunning())
                return nullptr;

            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketUtil::CreateTCPSocket(inFamily);
            }
            return nullptr;
        }

        // Sets
        static fd_set* FillSetFromVector(fd_set& outSet, const TCPSocketVector* inSockets)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketUtil::FillSetFromVector(outSet, inSockets);
            }
            return nullptr;
        };

        static void FillVectorFromSet(TCPSocketVector* outSockets, const TCPSocketVector* inSockets, const fd_set& inSet)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: WindowsSocketUtil::FillVectorFromSet(outSockets, inSockets, inSet);
            }

        }

        static int Select(const TCPSocketVector* inReadSet, TCPSocketVector* outReadSet,
                          const TCPSocketVector* inWriteSet, TCPSocketVector* outWriteSet,
                          const TCPSocketVector* inExceptSet, TCPSocketVector* outExceptSet)
        {
            if (!IsRunning())
                return SOCKET_ERROR;

            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2:
                    return WindowsSocketUtil::Select(inReadSet, outReadSet, inWriteSet, outWriteSet, inExceptSet, outExceptSet);
            }
            return SOCKET_ERROR;
        }

        // TODO: Move to socket 
        static int GetSocketName(const Socket& inSocket, SocketAddress& outAddress, int inAddressSize = -1)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketUtil::GetSocketName(inSocket, outAddress, inAddressSize);
            }

            return SOCKET_ERROR;
        }

        // TODO: Move to socket, cleanup setting handling with safety check
        static int SetSocketOption(const Socket& inSocket, int inOptionLevel, int inOptionName, const char* inOptionValue, int inOptionLength)
        {
            switch (SocketAPI::GetAPI())
            {
                case SocketAPI::SocketLibrary::WinSock2: return WindowsSocketUtil::SetSocketOption(inSocket, inOptionLevel, inOptionName, inOptionValue, inOptionLength);
            }
            return SOCKET_ERROR;
        }
    };
}