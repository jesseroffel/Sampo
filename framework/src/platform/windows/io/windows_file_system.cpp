#include "sampo_pch.hpp"
#include "sampo/io/file_system.hpp"

#include <filesystem>

namespace fs = std::filesystem;

namespace Sampo
{
    FileState FileSystem::FileExists(const std::string_view& path)
    {
        fs::path fPath{ path };
        if (fPath.is_absolute())
        {
            fs::file_status fileStatus = fs::status(path);

            if (!fs::status_known(fileStatus))
                return FileState::FileNotFound;

            return (fs::is_regular_file(fileStatus)) ? FileState::OK : FileState::IsNotAFile;
        }
        return FileState::NotImplemented;
    }

    FileState FileSystem::DirectoryExists(const std::string_view& path) noexcept
    {
        fs::path fPath{ path };
        fs::file_status fileStatus = fs::status(path);

        if (!fs::status_known(fileStatus))
            return FileState::DirectoryFound;

        return (fs::is_directory(fileStatus)) ? FileState::OK : FileState::IsNotADirectory;
    }

    FileState FileSystem::CreateDirectory(const std::string_view& path) noexcept
    {
        fs::path fPath{ path };
        if (fPath.is_absolute())
        {
            if (DirectoryExists(path) == FileState::DirectoryFound)
                return FileState::CreatedDirectory;

            return (fs::create_directory(fPath)) ? FileState::CreatedDirectory : FileState::UnknownError;
        }
        
        if (fPath.is_relative())
        {
            fs::path combined{ fs::current_path() };
            combined /= path;

            fs::file_status fileStatus = fs::status(path);

            if(fs::exists(fileStatus))
                fs::create_directory(combined) ? FileState::CreatedDirectory : FileState::UnknownError;
        }
        return FileState::NotImplemented;
    }

    FileState FileSystem::SetCurrentPath(const std::string_view& path)
    {
        fs::path fPath{ path };
        fs::file_status fileStatus = fs::status(path);

        if (!fs::status_known(fileStatus))
            return FileState::DirectoryNotFound;
        if (!fs::is_directory(fileStatus))
            return FileState::IsNotADirectory;
        
        fs::current_path(fPath);
        s_CurrentPath = path;
        return FileState::OK;
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