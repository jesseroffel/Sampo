#pragma once
#include "sampo/io/file_states.hpp"

#include <string_view>
#include <string>

namespace Sampo
{
    // Generic file system class that handles common file requests
    class FileSystem
    {
    public:
        // Checks
        static FileState                                        FileExists(const std::string_view& path);
        static FileState                                        DirectoryExists(const std::string_view& path) noexcept;
        // Creation
        static FileState                                        CreateDirectory(const std::string_view& path) noexcept;

        // Navigation 
        static FileState                                        SetCurrentPath(const std::string_view& path);
        static const std::string&                               GetExectuablePath() noexcept;
    private:

        inline static std::string                               s_ExecutablePath;
        inline static std::string                               s_CurrentPath;
        static void                                             CreateExectuablePath(std::string& ExecutionPath) noexcept;
    };

}
