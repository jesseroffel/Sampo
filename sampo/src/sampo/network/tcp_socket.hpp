#pragma once
#include "sampo/network/socket.hpp"
#include "sampo/core/log.hpp"

namespace Sampo
{
    class TCPSocket : public Socket
    {
    public:
        virtual ~TCPSocket()  = default;

        virtual int             Connect(const SocketAddress& inAddress) = 0;
        virtual int             Bind(const SocketAddress& inToAddress) = 0;
        virtual int             Listen(int inBacklog = 32) = 0;
        virtual Ref<TCPSocket>  Accept(SocketAddress& inFromAddress) = 0;
        virtual int             Send(const void* inData, int inLength) = 0;
        virtual int             Receive(void* inBuffer, int inLength) = 0;
    protected:
        TCPSocket(SOCKET inSocket) : Socket(inSocket) {}
    private:
    };

    using TCPSocketPtr = std::shared_ptr<TCPSocket>;
    using TCPSocketVector = std::vector<TCPSocketPtr>;
}