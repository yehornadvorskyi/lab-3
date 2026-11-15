#include "action.h"

#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std;

void f(char x, int i)
{
    this_thread::sleep_for(1s);

    osyncstream(cout) << format("Set {}: action {} completed.\n", x, i);
}