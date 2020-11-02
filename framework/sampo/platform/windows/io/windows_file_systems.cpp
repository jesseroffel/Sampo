#include "sampo/io/file_system.hpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace Sampo
{
    bool FileSystem::FileExists(const std::string_view& path) noexcept
    {
        std::error_code ec;
        return fs::exists(path, ec);
    }

    const std::string& FileSystem::GetExectuablePath() noexcept
    {
        if (s_ExecutablePath.empty())
        {
            CreateExectuablePath(s_ExecutablePath);
        }
        return s_ExecutablePath;
    }

    void FileSystem::CreateExectuablePath(std::string& ExecutionPath) noexcept
    {
        ExecutionPath = fs::current_path().generic_u8string();
    }
}