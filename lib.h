#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <deque>
#include <iterator>
#include <numeric>
#include <string>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <random>
#include <chrono>
using namespace std;

// Compile with -DUSE_LIST to use std::list, otherwise std::deque is used.
#ifdef USE_LIST
template <class T> using Container = list<T>;
#else
template <class T> using Container = deque<T>;
#endif

// std::sort needs random access, so list uses its own member sort().
template <class T, class Cmp>
void sortContainer(Container<T>& c, Cmp cmp) {
#ifdef USE_LIST
    c.sort(cmp);
#else
    std::sort(c.begin(), c.end(), cmp);
#endif
}
