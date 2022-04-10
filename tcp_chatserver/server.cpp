#include "sampo.hpp"
#include "sampo/network/socket_address_factory.hpp"
#include "sampo/network/socket_util.hpp"

#define GOOD_SEGMENT_SIZE 1500

class TCPServer : public Sampo::Layer
{
public:
    TCPServer() = default;
    ~TCPServer() = default;

    virtual void OnAttach() override
    {
        listenSocket = Sampo::SocketUtil::CreateTCPSocket(Sampo::ESocketAddressFamily::INET);
        Sampo::SocketAddressPtr receivingAddress = Sampo::SocketAddressFactory::CreateIPv4FromString("192.168.2.138:48000"); // INADDR_ANY
        if (listenSocket.get() && listenSocket->Bind(*receivingAddress.get()) != NO_ERROR)
        {
            SAMPO_ERROR("Cannot start due to no Socket API running");
            return;
        }
        
        readBlockSockets.push_back(listenSocket);

        listenSocket->Listen();

        m_running = true;
        SAMPO_TRACE("Completed setup Receiving Address: {0}", receivingAddress->GetFullAddressToString());
    }
    virtual void OnUpdate(float ts) override
    {
        if (Sampo::SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
        {
            // We got a packet-loop through the set ones
            for (const Sampo::TCPSocketPtr& socket : readableSockets)
            {
                if (socket == listenSocket)
                {
                    Sampo::SocketAddressPtr newClientAddress = Sampo::SocketAddressFactory::CreateEmptyAddress();
                    auto newSocket = listenSocket->Accept(*newClientAddress.get());
                    SAMPO_TRACE("Accept new client: {0}", newClientAddress->GetFullAddressToString());
                    readBlockSockets.push_back(newSocket);
                    ProcessNewClient(newSocket, newClientAddress);
                }
                else
                {
                    // It's a regular socket-process the data
                    char segment[GOOD_SEGMENT_SIZE];
                    int dataReceived = socket->Receive(segment, GOOD_SEGMENT_SIZE);
                    if (dataReceived > 0)
                    {
                        Sampo::SocketAddressPtr clientAddress = Sampo::SocketAddressFactory::RetrieveAddressFromSocket(*socket);
                        SAMPO_TRACE("Received packet of {0} bytes from {1}: message: '{2}', Sending response...", dataReceived, clientAddress->GetFullAddressToString(), segment);

                        char sendData[24] = "Hello again, client!\0";
                        socket->Send(sendData, sizeof(sendData));
                    }
                    else
                    {
                        // Close connection
                        socket->Send(nullptr, 0);
                    }
                }
            }

        }
    }
private:
    void ProcessNewClient(Sampo::TCPSocketPtr newSocket, Sampo::SocketAddressPtr newAddress)
    {
        char segment[25] = "Hello World, Client!\0";
        int bytesSend = newSocket->Send(segment, sizeof(segment));
        SAMPO_TRACE("Sending AKN message of {0} bytes to new client: {1}", bytesSend, newAddress->GetFullAddressToString());
    }
private:
    Sampo::TCPSocketPtr listenSocket;
    std::vector<Sampo::TCPSocketPtr> readBlockSockets;
    std::vector<Sampo::TCPSocketPtr> readableSockets;

    bool m_running = false;
};

class Server : public Sampo::Application
{
public:
    Server()
    {
        PushLayer(new TCPServer());
    }
    ~Server() = default;
};

// Client application creation //

Sampo::Application* Sampo::CreateApplication()
{
    return new Server();
}