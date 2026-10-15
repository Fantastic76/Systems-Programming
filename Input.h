#pragma once
#include "lib.h"

// Asks the user until a number in [min, max] is entered.
// Throws std::runtime_error if the input stream is closed.
int readChoice(const string& prompt, int min, int max);
