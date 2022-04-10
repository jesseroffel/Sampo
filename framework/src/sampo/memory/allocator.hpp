#pragma once
#include "sampo/core/core_definitions.hpp"

#include <cassert>
#include <cstddef>

namespace Sampo
{
    class Allocator
    {
        friend class Benchmark;
    public:
        Allocator(std::size_t size)
            : m_TotalSize(size)
            , m_UsedMemory(0)
            , m_NumAlllocations(0)
        {}

        virtual ~Allocator()
        {
            assert(m_NumAlllocations == 0 && m_UsedMemory == 0);
            m_Start = nullptr;
            m_TotalSize = 0;
        }

        virtual void* Allocate(const std::size_t size, std::size_t alignment = 0) = 0;

        virtual void Free(void* ptr) = 0;

        virtual void Init() = 0;

    protected:
        void* m_Start{ nullptr };
        std::size_t m_TotalSize{};
        std::size_t m_UsedMemory{};
        std::size_t m_NumAlllocations{};
        std::size_t m_Peak{};
    };
}