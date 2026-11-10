#include "Memory.h"
#include <cstdlib>
#include <new>

namespace {
    size_t g_current = 0, g_peak = 0;
    constexpr size_t HEADER = 16;          // keeps 16-byte alignment, stores the block size
}

namespace memtrack {
    size_t current()   { return g_current; }
    size_t peak()      { return g_peak; }
    void   resetPeak() { g_peak = g_current; }
}

void* operator new(size_t n) {
    void* raw = std::malloc(n + HEADER);
    if (!raw) throw std::bad_alloc();
    *static_cast<size_t*>(raw) = n;
    g_current += n;
    if (g_current > g_peak) g_peak = g_current;
    return static_cast<char*>(raw) + HEADER;
}

void operator delete(void* p) noexcept {
    if (!p) return;
    void* raw = static_cast<char*>(p) - HEADER;
    g_current -= *static_cast<size_t*>(raw);
    std::free(raw);
}

void operator delete(void* p, size_t) noexcept { operator delete(p); }
