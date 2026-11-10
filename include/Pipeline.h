#pragma once
#include "Classroom.h"

const vector<size_t> FILE_SIZES = {10000, 100000, 1000000, 10000000};

enum class ContainerKind { Vector = 1, List = 2, Deque = 3 };

// Generates students_<N>.txt for every size in FILE_SIZES and prints the time taken.
void generateAllFiles();

// Reads students_<count>.txt into the chosen container, sorts it, divides it with the chosen
// strategy/implementation, writes passed_<count>.txt and failed_<count>.txt and prints the
// time and memory of every step.
void processFile(size_t count, ContainerKind kind, Strategy st, Impl impl, Method m, SortOrder order);

// Runs every container x strategy x implementation combination on students_<count>.txt
// and prints a comparison table (no files are written).
void benchmarkFile(size_t count, Method m, SortOrder order);
