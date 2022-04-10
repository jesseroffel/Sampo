#include "sampo_pch.hpp"
#include "callocator.hpp"

#include <stdlib.h>

namespace Sampo
{
    CAllocator::CAllocator()
        : Allocator(0) {}

    void CAllocator::Init() {};

    void* CAllocator::Allocate(const std::size_t size, const std::size_t alignment)
    {
        UNUSED(alignment);
        return malloc(size);
    }

    void CAllocator::Free(void* ptr)
    {
        free(ptr);
    }
}