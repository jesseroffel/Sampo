#include "networktest.hpp"

#include "sampo/network/socket_address_factory.hpp"
#include "sampo/network/socket_util.hpp"

#include <iostream>

void NetworkTest::OnAttach()
{
    // Test IP gathering
    const std::string testDNS = "www.google.com";
    Sampo::SocketAddressPtr IPv4Test = Sampo::SocketAddressFactory::CreateIPv4FromString(testDNS);
    if (IPv4Test)
    {
        std::cout << "IP: " << IPv4Test->GetAddressToString() << std::endl;
    }
    Sampo::SocketAddressPtr IPv6Test = Sampo::SocketAddressFactory::CreateIPv6FromString(testDNS);
    if (IPv6Test)
    {
        std::cout << "IP: " << IPv6Test->GetAddressToString() << std::endl;
    }
}
