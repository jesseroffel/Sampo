#pragma once
// Header only class based on Nicolai Josuttis's implementation to track new allocations when included
#include <iostream>
namespace Sampo
{
    class TrackNew
    {
    public:
        // Print current state
        static void Status()
        {
            std::cout << "Memory usage: " << (s_BytesAllocated - s_BytesFreed) << 
                         " bytes | Count new: " << s_NewAllocCalls << " | Count Free: " << s_NewDeallocCalls <<
                         " | Total new: " << s_TotalAllocCalls << " | Total delete: " << s_TotalFreeCalls << "\n";
            s_NewAllocCalls = 0;
            s_NewDeallocCalls = 0;
        }

        // Set the state of tracing
        static void Trace(bool state) { s_DoTrace = state; }

        // Implementation of tracked malloc
        static void* Allocate(std::size_t size)
        {
            ++s_TotalAllocCalls;
            ++s_NewAllocCalls;
            s_BytesAllocated += size;

            if (s_DoTrace)
            {
                std::cout << "Allocating " << size << " bytes\n";
            }

            return malloc(size);
        }

        static void Deallocate(void* memory, std::size_t size)
        {
            ++s_TotalFreeCalls;
            ++s_NewDeallocCalls;
            s_BytesFreed += size;

            if (s_DoTrace)
            {
                std::cout << "Deallocating " << size << " bytes\n";
            }

            free(memory);
        }

    private:
        inline static std::size_t s_TotalAllocCalls{ 0 };           // number of ::new or ::new[] calls
        inline static std::size_t s_NewAllocCalls{ 0 };             // alloc calls since last time calling status()
        inline static std::size_t s_TotalFreeCalls{ 0 };            // number of ::new or ::new[] calls
        inline static std::size_t s_NewDeallocCalls{ 0 };           // free calls since last time calling status()
        inline static std::size_t s_BytesAllocated{ 0 };            // bytes allocated so far
        inline static std::size_t s_BytesFreed{ 0 };                // bytes allocated so far
        inline static bool s_DoTrace = false;                       // print calls when called
    };
}

void* operator new (std::size_t size)
{
    return Sampo::TrackNew::Allocate(size);
}

void operator delete(void* memory, std::size_t size)
{
    Sampo::TrackNew::Deallocate(memory, size);
}