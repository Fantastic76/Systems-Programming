#pragma once
#include "Classroom.h"

// The four file sizes required by the task.
const Container<size_t> FILE_SIZES = {10000, 100000, 1000000, 10000000};

// Generates students_<N>.txt for every size in FILE_SIZES and prints the time taken.
void generateAllFiles();

// Reads students_<count>.txt, sorts it, divides it into "passed" (>= 5.0) and "failed" (< 5.0),
// writes passed_<count>.txt and failed_<count>.txt, and prints the time of every step.
void processFile(size_t count, Method m, SortOrder order);
