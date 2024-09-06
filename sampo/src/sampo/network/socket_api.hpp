#pragma once

// Move in future to separate Sampo init (platform specific?)
int main(int, char**);

namespace Sampo
{
    class SocketAPI
    {
    public:
        enum class SocketLibrary
        {
            Undefined = 0, WinSock2 = 1, Posix = 2
        };
    public:
        virtual ~SocketAPI() = default;

        virtual void Init() = 0;
        virtual void Shutdown() = 0;

        static SocketLibrary GetAPI() { return s_SocketAPI; }
        static bool IsRunning() { return s_Running; }
    protected:
        static bool s_Running;
    private:
        friend int ::main(int argc, char** argv);
        static Scope<SocketAPI> Create();
        static SocketLibrary s_SocketAPI;
    };
}