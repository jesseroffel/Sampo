#include "sampo.hpp"
#include "sampo/network/socket_address_factory.hpp"
#include "sampo/network/socket_util.hpp"

#include <iostream>

#define GOOD_SEGMENT_SIZE 1500

class TCPClient : public Sampo::Layer
{
public:
    TCPClient() = default;
    ~TCPClient() = default;

    virtual void OnAttach() override
    {
        chatSocket = Sampo::SocketUtil::CreateTCPSocket(Sampo::ESocketAddressFamily::INET);
        Sampo::SocketAddressPtr serverAddress = Sampo::SocketAddressFactory::CreateIPv4FromString("192.168.2.138:48000"); //CreateIPv4(INADDR_ANY, 48000);
        SAMPO_TRACE("Attempt connect to server on search address: {0}", serverAddress->GetFullAddressToString());

        if (chatSocket->Connect(*serverAddress) != NO_ERROR)
        {
            SAMPO_ERROR("Couldn't get a connection going");
            return;
        }


        SAMPO_TRACE("Connected to server: {0}, waiting to get a response...", serverAddress->GetFullAddressToString());

        char receiveData[GOOD_SEGMENT_SIZE];
        int sizeReceived = chatSocket->Receive(receiveData, sizeof(receiveData));
        if (sizeReceived == -1)
        {
            SAMPO_ERROR("Unable to receive the data");
            return;
        }

        std::string messageReceived(&receiveData[0], sizeof(receiveData));
        SAMPO_TRACE("Received Server AKN message: '{0}', sending AKN response", receiveData);

        char sendData[24] = "Hello World, Server!\0";
        if (!chatSocket->Send(sendData, sizeof(sendData)))
            SAMPO_ERROR("Couldn't send the data!!");

        ZeroMemory(receiveData, sizeof(receiveData));
        sizeReceived = chatSocket->Receive(receiveData, sizeof(receiveData));
        if (sizeReceived == -1)
        {
            SAMPO_ERROR("Unable to receive the data");
            return;
        }

        chatSocket->Send(nullptr, 0);
    }
    virtual void OnUpdate(float ts) override
    {
    }

private:
    Sampo::TCPSocketPtr chatSocket;
    Sampo::SocketAddressPtr serverAddress;
    
    bool m_running = false;
};

class Client : public Sampo::Application
{
public:
    Client()
    {
        PushLayer(new TCPClient());
    }
    ~Client() = default;
};

// Client application creation //

Sampo::Application* Sampo::CreateApplication()
{
    return new Client();
}