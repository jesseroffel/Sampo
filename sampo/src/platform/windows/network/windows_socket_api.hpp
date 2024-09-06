#pragma once
#include "sampo/network/socket_api.hpp"

namespace Sampo {

    class WindowsSocketAPI : public SocketAPI
    {
    public:
        virtual void Init() override;
        virtual void Shutdown() override;
    };
}
