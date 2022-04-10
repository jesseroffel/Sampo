#pragma once
namespace Sampo
{
    enum class FileState : std::uint16_t
    {
        OK = 0,
        DirectoryFound,
        DirectoryNotFound,
        DirectoryNotAccessible,
        FileFound,
        FileNotFound,
        FileNotAccessible,
        IsNotAFile,
        IsNotADirectory,
        IsNotAbsolutePath,
        IsNotRelativePath,
        CreatedDirectory,
        CreatedFile,
        UnknownError,
        NotImplemented
    };
}