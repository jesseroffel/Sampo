#include "demolayer.hpp"

#include "sampo/io/file_system.hpp"
#include "sampo/memory/allocator_pmr.hpp"
#include "sampo/memory/callocator.hpp"
#include "sampo/memory/linear_allocator.hpp"
#include "sampo/memory/memory_benchmark.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <memory_resource>

void DemoLayer::OnAttach()
{
    const std::string exectuablepath{ Sampo::FileSystem::GetExectuablePath() };
    
    Sampo::FileSystem::FileExists(exectuablepath);
    Sampo::FileSystem::FileExists("D:/SideProjects/Sampo/CMakeLists.txt");
    Sampo::FileSystem::CreateDirectory("Hello");
    Sampo::FileSystem::CreateDirectory("D:/SideProjects/Sampo/newfolder");
    Sampo::FileSystem::SetCurrentPath("D:/SideProjects/Sampo/newfolder");
    Sampo::FileSystem::CreateDirectory("anotherfolder");
    Sampo::FileSystem::CreateDirectory("sampo/anotherfolder");

    const std::size_t A = static_cast<std::size_t>(1e9);
    const std::size_t B = static_cast<std::size_t>(1e8);
    
    const std::vector<std::size_t> ALLOCATION_SIZES{ 32, 64, 256, 512, 1024, 2048, 4096 };
    const std::vector<std::size_t> ALIGNMENTS{ 8, 8, 8, 8, 8, 8, 8 };
    
    
    Sampo::CAllocator* cAllocator = new Sampo::CAllocator();
    Sampo::LinearAllocator* linearAllocator = new Sampo::LinearAllocator(A);
    
    Sampo::Benchmark benchmark(OPERATIONS);
    
    std::cout << "C malloc \n";
    benchmark.MultipleAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.MultipleFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomFree(cAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    
    std::cout << "LINEAR\n";
    benchmark.MultipleAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
    benchmark.RandomAllocation(linearAllocator, ALLOCATION_SIZES, ALIGNMENTS);
}
