#include "sampo_pch.hpp"
#include "allocator_pmr.hpp"

#include <cassert>

namespace Sampo
{
    // Keep track of the number of bytes that would be leaked by the allocator destructor
    std::size_t pmr_allocator::s_leaked_bytes = 0;
    // Keep track of the number of blocks that would be leaked by the allocator destructor
    std::size_t pmr_allocator::s_leaked_blocks = 0;

    pmr_allocator::pmr_allocator(std::pmr::memory_resource* parent)
        : m_Parent(parent)
        , m_Blocks(parent)  // vector memory uses parent too
    {
    }

    pmr_allocator::~pmr_allocator()
    {
        // if any blocks have not been released, report them as leaked
        s_leaked_blocks += blocks_outstanding();

        // Reclaim blocks that would have been leaked
        for (auto& alloc_rec : m_Blocks)
        {
            s_leaked_bytes += alloc_rec.m_bytes;
            m_Parent->deallocate(alloc_rec.m_ptr, alloc_rec.m_bytes, alloc_rec.m_alignment);
        }
    }

    void pmr_allocator::clear_leaked()
    {
        s_leaked_bytes = 0;
        s_leaked_blocks = 0;
    }

    void* pmr_allocator::do_allocate(std::size_t bytes, std::size_t alignment)
    {
        void* address = m_Parent->allocate(bytes, alignment);
        m_Blocks.push_back(allocation_rec{ address, bytes, alignment });
        m_bytes_allocated += bytes;
        m_bytes_highwater += bytes;
    
        if (m_bytes_outstanding > m_bytes_highwater)
            m_bytes_highwater = m_bytes_outstanding;

        return address;
    }

    void pmr_allocator::do_deallocate(void* p, std::size_t bytes, std::size_t alignment)
    {
        // check that deallocation args match allocation args
        auto i = std::find_if(m_Blocks.begin(), m_Blocks.end(), [p](allocation_rec& r) { return r.m_ptr == p; });

        if (i == m_Blocks.end())
            throw std::invalid_argument("Deallocate: invalid pointer!");
        else if (i->m_bytes != bytes)
            throw std::invalid_argument("Deallocate: Size mismatch!");
        else if (i->m_alignment != alignment)
            throw std::invalid_argument("Deallocate: Alignment mismatch");

        m_Parent->deallocate(p, i->m_bytes, i->m_alignment);
        m_Blocks.erase(i);
        m_bytes_outstanding -= bytes;
    }

    bool pmr_allocator::do_is_equal(const std::pmr::memory_resource& other) const noexcept
    {
        return this == &other;
    }
}
