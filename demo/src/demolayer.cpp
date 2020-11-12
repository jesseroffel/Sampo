#include "demolayer.hpp"
#include <string>
#include <sampo/io/file_system.hpp>
#include <sampo/debugging/new_tracker.hpp>

void DemoLayer::OnAttach()
{
    const std::string exectuablepath{ Sampo::FileSystem::GetExectuablePath() };

    Sampo::FileSystem::FileExists(exectuablepath);
    Sampo::FileSystem::FileExists("D:/SideProjects/Sampo/CMakeLists.txt");
    Sampo::FileSystem::CreateDirectory("Hello");
    Sampo::FileSystem::CreateDirectory("D:/SideProjects/Sampo/newfolder");
    Sampo::FileSystem::SetCurrentPath("D:/SideProjects/Sampo/newfolder");
    Sampo::FileSystem::CreateDirectory("anotherfolder");
    Sampo::FileSystem::CreateDirectory("sampo/anotherfolder");

}
