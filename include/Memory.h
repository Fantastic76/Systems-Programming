#pragma once
#include <cstddef>

// Tiny heap-usage tracker (replaces global operator new/delete, see Memory.cpp).
// It counts the bytes REQUESTED from operator new; the allocator's own bookkeeping
// (~8-16 bytes per allocation) is not included, so std::list is slightly under-reported.
namespace memtrack {
    size_t current();       // bytes currently allocated
    size_t peak();          // highest value of current() since the last resetPeak()
    void   resetPeak();     // peak := current
}
