#include "sampo_pch.hpp"
#include "memory_benchmark.hpp"

namespace Sampo
{
    void Benchmark::SingleAllocation(Allocator* allocator, const std::size_t size, const std::size_t alignment)
    {
        std::cout << "Benchmark: allocation:" << "\n";
        std::cout << "Size:       \t" << size << "\n";
        std::cout << "Alignment: \t" << alignment << "\n";

        StartRound();

        allocator->Init();

        auto operations = 0u;
        while (operations < m_nOperations)
        {
            allocator->Allocate(size, alignment);
            ++operations;
        }

        FinishRound();
        
        BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_Peak);

        PrintResults(results);
    }

    void Benchmark::SingleFree(Allocator* allocator, const std::size_t size, const std::size_t alignment)
    {
        std::cout << "Benchmark: allocation:" << "\n";
        std::cout << "Size:       \t" << size << "\n";
        std::cout << "Alignment: \t" << alignment << "\n";

        void* addresses[OPERATIONS];

        StartRound();

        allocator->Init();

        auto operations = 0u;
        while (operations < m_nOperations)
        {
            addresses[operations] = allocator->Allocate(size, alignment);
            ++operations;
        }

        while (operations)
            allocator->Free(addresses[--operations]);

        FinishRound();

        BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_Peak);

        PrintResults(results);
    }

    void Benchmark::MultipleAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments)
    {
        assert(allocationSizes.size() == alignments.size() && "Allocation sizes and alignments must have same length");

        for (auto i = 0u; i < allocationSizes.size(); ++i)
            SingleAllocation(allocator, allocationSizes[i], alignments[i]);
    }

    void Benchmark::MultipleFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments)
    {
        assert(allocationSizes.size() == alignments.size() && "Allocation sizes and alignments must have same length");

        for (auto i = 0u; i < allocationSizes.size(); ++i)
            SingleFree(allocator, allocationSizes[i], alignments[i]);
    }
    void Benchmark::RandomAllocation(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments) {

        // NOTE: Is this actually initializing the RNG? Jose Fernando Lopez Fernandez 11/07/2018 @ 12:54am (UTC)
        srand(1);

        std::cout << "BENCHMARK: ALLOCATION\n";

        StartRound();

        std::size_t allocation_size;
        std::size_t alignment;

        allocator->Init();

        auto operations = 0u;

        while (operations < m_nOperations) {
            this->RandomAllocationAttr(allocationSizes, alignments, allocation_size, alignment);
            allocator->Allocate(allocation_size, alignment);
            ++operations;
        }

        FinishRound();

        BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_Peak);

        PrintResults(results);
    }

    void Benchmark::RandomFree(Allocator* allocator, const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments) {

        // NOTE: Is this actually initializing the RNG? Jose Fernando Lopez Fernandez 11/07/2018 @ 1:51am (UTC)
        srand(1);

        std::cout << "BENCHMARK: ALLOCATION/FREE\n";

        StartRound();

        void* addresses[OPERATIONS];

        std::size_t allocation_size;
        std::size_t alignment;

        allocator->Init();

        auto operations = 0u;

        while (operations < m_nOperations) {
            this->RandomAllocationAttr(allocationSizes, alignments, allocation_size, alignment);
            addresses[operations] = allocator->Allocate(allocation_size, alignment);
            ++operations;
        }

        while (operations) 
            allocator->Free(addresses[--operations]);

        FinishRound();

        BenchmarkResults results = buildResults(m_nOperations, std::move(TimeElapsed), allocator->m_Peak);

        PrintResults(results);

    }

    void Benchmark::PrintResults(const BenchmarkResults& results) const {
        std::cout << "RESULTS:\n";
        std::cout << "\tOperations:    \t" << results.Operations << "\n";
        std::cout << "\tTime elapsed: \t" << results.Milliseconds.count() << " ms" << "\n";
        std::cout << "\tOp per sec:    \t" << results.OperationsPerSec << " ops/ms" << "\n";
        std::cout << "\tTimer per op:  \t" << results.TimePerOperation << " ms/ops" << "\n";
        std::cout << "\tMemory peak:   \t" << results.MemoryPeak << " bytes" << "\n";
    }

    const BenchmarkResults Benchmark::buildResults(std::size_t nOperations, std::chrono::milliseconds&& elapsedTime, const std::size_t memoryPeak) const 
    {
        BenchmarkResults results;

        results.Operations = nOperations;
        results.Milliseconds = std::move(elapsedTime);
        results.OperationsPerSec = results.Operations / static_cast<double>(results.Milliseconds.count());
        results.TimePerOperation = static_cast<double>(results.Milliseconds.count()) / static_cast<double>(results.Operations);
        results.MemoryPeak = memoryPeak;

        return results;
    }

    void Benchmark::RandomAllocationAttr(const std::vector<std::size_t>& allocationSizes, const std::vector<std::size_t>& alignments, std::size_t& size, std::size_t& alignment) {
        const int r = rand() % allocationSizes.size();
        size = allocationSizes[r];
        alignment = alignments[r];
    }
}