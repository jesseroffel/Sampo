// Detect platform and set defines
#ifdef _WIN32
    #ifndef SAMPO_PLATFORM_WINDOWS
        #define SAMPO_PLATFORM_WINDOWS
    #endif // SAMPO_PLATFORM_WINDOWS

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif

    #ifdef _WIN64
        #define SAMPO_PLATFORM_WIN64
    #else 
        #error "Window x86 (32bit) is not supported!"
    #endif // _WIN64

    #ifndef SAMPO_PLATFORM_ISPCBUILD
        #define SAMPO_PLATFORM_ISPCBUILD
    #endif // SAMPO_PLATFORM_ISPCBUILD
#else
    #error "Specified platform not supported!"
#endif // _WIN32