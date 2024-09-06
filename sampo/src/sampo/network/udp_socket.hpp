#pragma once
#include "sampo/network/socket.hpp"
#include "sampo/core/log.hpp"

namespace Sampo
{
    class UDPSocket : public Socket
    {
    public:
        virtual ~UDPSocket() = default;

        virtual int Bind(const SocketAddress& inToAddress) = 0;
        virtual int SentTo(const void* inData, int inLength, const SocketAddress& inTo) = 0;
        virtual int ReceiveFrom(void* inBuffer, int inLength, SocketAddress& outFromAddress) = 0;

        virtual int SetNonBlockingMode(bool inShouldBeNonBlocking) = 0;
    protected:
        UDPSocket(SOCKET inSocket) : Socket(inSocket) {}
    private:
    };
    
    using UDPSocketPtr = std::shared_ptr<UDPSocket>;
    using UDPSocketVector = std::vector<UDPSocketPtr>;
}