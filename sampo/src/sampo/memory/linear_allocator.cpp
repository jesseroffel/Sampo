#include "sampo_pch.hpp"
#include "linear_allocator.hpp"

#include <stdlib.h>
#include <algorithm>

namespace Sampo
{
    LinearAllocator::LinearAllocator(const std::size_t totalSize)
        : Allocator(totalSize)
    {
    }

    LinearAllocator::~LinearAllocator()
    {
        free(m_StartPtr);
        m_StartPtr = nullptr;
    }

    void LinearAllocator::Init()
    {
        if (m_StartPtr != nullptr)
            free(m_StartPtr);

        m_StartPtr = malloc(m_TotalSize);
        m_Offset = 0;
    }

    void* LinearAllocator::Allocate(const std::size_t size, const std::size_t alignment)
    {
        std::size_t padding = 0;

        const std::size_t currentAddress = (std::size_t)m_StartPtr + m_Offset;

        if (alignment != 0 && (m_Offset % alignment != 0))
            padding = CalculatePadding(currentAddress, alignment);

        if (m_Offset + padding + size > m_TotalSize)
            return nullptr;

        m_Offset += padding;
        const std::size_t nextAddress = currentAddress + padding;
        m_Offset += size;

    #ifdef _DEBUG
        std::cout << "A" << "\t@C " << (void*)currentAddress << "\t@R " << (void*)nextAddress
            << "\tO " << m_Offset << "\tP " << padding << "\n";
    #endif

        m_UsedMemory = m_Offset;
        m_Peak = std::max(m_Peak, m_UsedMemory);

        return (void*)nextAddress;
    }

    void LinearAllocator::Free(void* ptr)
    {
        UNUSED(ptr);
        assert(false && "Use Reset() method");
    }

    void LinearAllocator::Reset()
    {
        m_Offset = 0;
        m_UsedMemory = 0;
        m_Peak = 0;
    }
}