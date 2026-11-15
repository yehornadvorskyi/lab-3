#include "action.h"

#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std;

void f(char x, int i)
{
    //if (x == 'c' && i == 8) this_thread::sleep_for(2s);
    this_thread::sleep_for(1s);

    osyncstream(cout) << format("Set {}: action {} completed.\n", x, i);
}