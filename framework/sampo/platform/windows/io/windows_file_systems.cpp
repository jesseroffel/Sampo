#include "sampo/io/file_system.hpp"
#include <filesystem>

namespace fs = std::filesystem;

namespace Sampo
{
    bool FileSystem::FileExists(const std::string_view& path) 
    {
        fs::path fPath{ path };
        if (fPath.is_absolute())
        {
            fs::file_status fileStatus = fs::status(path);

            if (!fs::status_known(fileStatus))
                return false;

            return (fs::is_regular_file(fileStatus));
        }

        return false;
    }

    bool FileSystem::DirectoryExists(const std::string_view& path) noexcept
    {
        fs::path fPath{ path };
        fs::file_status fileStatus = fs::status(path);

        if (!fs::status_known(fileStatus))
            return false;

        return (fs::is_directory(fileStatus));
    }

    bool FileSystem::CreateDirectory(const std::string_view& path) noexcept
    {
        fs::path fPath{ path };
        if (fPath.is_absolute())
        {
            if (DirectoryExists(path))
                return false;

            return fs::create_directory(fPath);
        }
        
        if (fPath.is_relative())
        {
            fs::path combined{ fs::current_path() };
            combined /= path;

            fs::file_status fileStatus = fs::status(path);

            return (fs::exists(fileStatus)) ? fs::create_directory(combined) : false;
        }
        return false;
    }

    bool FileSystem::SetCurrentPath(const std::string_view& path)
    {
        fs::path fPath{ path };
        fs::file_status fileStatus = fs::status(path);

        if (!fs::status_known(fileStatus) || !fs::is_directory(fileStatus))
            return false;
        
        fs::current_path(fPath);
        s_CurrentPath = path;
        return true;
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
        fs::current_path(ExecutionPath);
    }
}