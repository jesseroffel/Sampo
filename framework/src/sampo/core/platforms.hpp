// Detect platform and set defines
#ifdef _WIN32
    #ifdef _WIN64
        #ifndef SAMPO_PLATFORM_WINDOWS
            #define SAMPO_PLATFORM_WINDOWS
        #endif // SAMPO_PLATFORM_WINDOWS
    #else 
        #error "Window x86 (32bit) is not supported!"
    #endif // _WIN64
#else
    #error "Specified platform not supported!"
#endif // _WIN32