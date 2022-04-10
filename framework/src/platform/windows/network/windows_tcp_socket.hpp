#pragma once
#include "sampo/network/tcp_socket.hpp"
#include "windows_socket_address.hpp"

namespace Sampo
{
    class WindowsTCPSocket : public TCPSocket
    {
    public:
        WindowsTCPSocket(SOCKET inSocket) : TCPSocket(inSocket) {}
        virtual ~WindowsTCPSocket() override;

        virtual int             Connect(const SocketAddress& inAddress) override;
        virtual int             Bind(const SocketAddress& inToAddress) override;
        virtual int             Listen(int inBacklog = 32) override;
        virtual Ref<TCPSocket>  Accept(SocketAddress& inFromAddress) override;
        virtual int             Send(const void* inData, int inLength) override;
        virtual int             Receive(void* inBuffer, int inLength) override;

    private:
        friend class WindowsSocketUtil;

    };

    using WindowsTCPSocketPtr = std::shared_ptr<WindowsTCPSocket>;
}