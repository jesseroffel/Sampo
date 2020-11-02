#include "demolayer.hpp"
#include <string>
#include <sampo/io/file_system.hpp>
#include <sampo/debugging/new_tracker.hpp>

void DemoLayer::OnAttach()
{
    Sampo::TrackNew::Trace(true);
    Sampo::TrackNew::Status();

    const std::string exectuablepath{ "D:/SideProjects/Sampo" };
    Sampo::TrackNew::Status();
    Sampo::FileSystem::FileExists(exectuablepath);
    Sampo::TrackNew::Status();
    std::string path{ Sampo::FileSystem::GetExectuablePath() };
    Sampo::TrackNew::Status();
    std::string executablePath = Sampo::FileSystem::GetExectuablePath();
    Sampo::TrackNew::Status();
}
