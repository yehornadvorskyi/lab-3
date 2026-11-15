//#include "action.h"
#include "schedule.h"
#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

using namespace std;

int main() {
    osyncstream(cout) << "Computation started.\n";
    const auto start = chrono::steady_clock::now();

	// тут шось буде робитися, наприклад, обчислення
    //f('a', 3); //заглушка перевірки
    {
        vector<jthread> threads;
		threads.reserve(schedule::kThreads);
        for (int t = 0; t < schedule::kThreads; ++t)
			threads.emplace_back(schedule::runThread, t);   
    }

    const chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
    osyncstream(cout) << format("Computation finished. Duration: {:.3f} seconds.\n", elapsed.count());
}