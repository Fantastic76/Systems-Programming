#pragma once
#include "lib.h"

// Simple stopwatch for measuring how long each step takes.
class Timer {
private:
    chrono::steady_clock::time_point start;
public:
    Timer() { reset(); }
    void reset() { start = chrono::steady_clock::now(); }
    double elapsed() const {   // seconds
        return chrono::duration<double>(chrono::steady_clock::now() - start).count();
    }
};
