#pragma once
#include <string_view>
#include <string>
namespace Sampo
{
    // Generic file system class that handles common file requests
    class FileSystem
    {
    public:
        // Checks
        static bool                                             FileExists(const std::string_view& pPathToCheck) noexcept;
        // Creation

        // Navigation 
        static const std::string&                               GetExectuablePath() noexcept;
    private:

        inline static std::string                               s_ExecutablePath;
        static void                                             CreateExectuablePath(std::string& ExecutionPath) noexcept;
    };
}
