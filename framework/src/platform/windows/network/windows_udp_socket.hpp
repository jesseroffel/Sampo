#pragma once
#include "sampo/network/udp_socket.hpp"
#include "platform/windows/network/windows_socket_address.hpp"

namespace Sampo
{
    class WindowsUDPSocket : public UDPSocket
    {
    public:
        WindowsUDPSocket(SOCKET inSocket) : UDPSocket(inSocket) {}
        virtual ~WindowsUDPSocket() override;

        virtual int Bind(const SocketAddress& inBindAddress) override;
        virtual int SentTo(const void* inData, int inLength, const SocketAddress& inToAddress) override;
        virtual int ReceiveFrom(void* inBuffer, int inLength, SocketAddress& outFromAddress) override;

        virtual int SetNonBlockingMode(bool inShouldBeNonBlocking) override;
    private:
        friend class WindowsSocketUtil;

    };

    using WindowsUDPSocketPtr = std::shared_ptr<WindowsUDPSocket>;
}