#include <chrono>
#include <format>
#include <iostream>
#include <syncstream>

using namespace std;

int main() {
    osyncstream(cout) << "Computation started.\n";
    const auto start = chrono::steady_clock::now();

	// тут шось буде робитися, наприклад, обчислення

    const chrono::duration<double> elapsed = chrono::steady_clock::now() - start;
    osyncstream(cout) << format("Computation finished. Duration: {:.3f} seconds.\n", elapsed.count());
}