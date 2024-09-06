#pragma once
#include <memory_resource>

namespace Sampo
{
    class pmr_allocator : public std::pmr::memory_resource
    {
    public:
        explicit pmr_allocator(std::pmr::memory_resource* parent = std::pmr::get_default_resource());

        ~pmr_allocator();

        std::pmr::memory_resource* parent() const { return m_Parent; }

        std::size_t bytes_allocated() const { return m_bytes_allocated; }
        std::size_t bytes_deallocated() const { return m_bytes_allocated - m_bytes_outstanding; }
        std::size_t bytes_outstanding() const { return m_bytes_outstanding; }
        std::size_t bytes_highwater() const { return m_bytes_highwater; }
        std::size_t blocks_outstanding() const { return m_Blocks.size(); }

        static std::size_t leaked_bytes() { return s_leaked_bytes; }
        static std::size_t leaked_blocks() { return s_leaked_blocks; }
        static void clear_leaked();

    protected:
        void* do_allocate(std::size_t bytes, std::size_t alignment) override;
        void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override;

        bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

    private:
        struct allocation_rec
        {
            void* m_ptr{ nullptr };
            std::size_t m_bytes{};
            std::size_t m_alignment{};
        };

        std::pmr::memory_resource* m_Parent{ nullptr };
        std::size_t m_bytes_allocated{};
        std::size_t m_bytes_outstanding{};
        std::size_t m_bytes_highwater{};
        std::pmr::vector<allocation_rec> m_Blocks;

        static std::size_t s_leaked_bytes;
        static std::size_t s_leaked_blocks;
    };
}
