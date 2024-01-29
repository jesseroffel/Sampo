// Detect platform and set defines
#ifdef _WIN32
    #ifndef SAMPO_PLATFORM_WINDOWS
        #define SAMPO_PLATFORM_WINDOWS (1)
    #endif // SAMPO_PLATFORM_WINDOWS

    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif //WIN32_LEAN_AND_MEAN

    #ifdef _WIN64
        #define SAMPO_PLATFORM_WIN64 (1)
    #else 
        #error "Window x86 (32bit) is not supported!"
    #endif // _WIN64
#else
    #error "Specified platform not supported!"
#endif // _WIN32

#ifdef NDEBUG   // replace with CMAKE included argument
    #define SAMPO_ASSERT_ENABLED (0)
#else
    #define SAMPO_ASSERT_ENABLED (1)
#endif //NDEBUG

#if _MSC_VER
    #define SAMPO_COMPILER_VISUALSTUDIO (1)
#else 
    #define SAMPO_COMPILER_VISUALSTUDIO (0)
#endif //_MSC_VER