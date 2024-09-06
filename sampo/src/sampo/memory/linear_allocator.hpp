#pragma once
#include "allocator.hpp"

namespace Sampo
{
    class LinearAllocator : public Allocator
    {
    public:
        LinearAllocator(const std::size_t totalSize);

        virtual ~LinearAllocator();

        virtual void* Allocate(const std::size_t size, const std::size_t alignmnet = 0) override;

        virtual void Free(void* ptr) override;

        virtual void Init() override;

        virtual void Reset();

    protected:
        void* m_StartPtr = nullptr;
        std::size_t m_Offset{};

        static const std::size_t CalculatePadding(const std::size_t baseAddress, const std::size_t alignment)
        {
            const std::size_t multiplier = (baseAddress / alignment) + 1;
            const std::size_t alignedAddress = multiplier * alignment;
            const std::size_t padding = alignedAddress - baseAddress;
            return padding;
        }

    private:
        LinearAllocator(LinearAllocator& linearAllocator);
    };
}