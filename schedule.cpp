#include "schedule.h"
#include "action.h"

#include <array>
#include <vector>

using namespace std;

namespace schedule
{
    namespace
    {
        struct Step
        {
            char set;
            int index;
        };

        const array<vector<Step>, kThreads> kPlan{ {
            {{'a', 1}, {'a', 6}, {'b', 5}, {'e', 5}, {'g', 2}, {'h', 3}, {'i', 3},
             {'k', 2}, {'c', 1}, {'c', 6}, {'d', 5}, {'f', 1}, {'f', 6}},
            {{'a', 2}, {'b', 1}, {'e', 1}, {'e', 6}, {'g', 3}, {'h', 4}, {'i', 4},
             {'k', 3}, {'c', 2}, {'c', 7}, {'f', 2}, {'f', 7}},
            {{'a', 3}, {'b', 2}, {'e', 2}, {'e', 7}, {'g', 4}, {'h', 5}, {'i', 5},
             {'k', 4}, {'c', 3}, {'c', 8}, {'f', 3}, {'f', 8}},
            {{'a', 4}, {'b', 3}, {'e', 3}, {'e', 8}, {'h', 1}, {'i', 1}, {'i', 6},
             {'d', 1}, {'c', 4}, {'d', 3}, {'f', 4}, {'f', 9}},
            {{'a', 5}, {'b', 4}, {'e', 4}, {'g', 1}, {'h', 2}, {'i', 2}, {'k', 1},
             {'d', 2}, {'c', 5}, {'d', 4}, {'f', 5}},
        } };
    }

    void runThread(int threadNo)
    {
        for (const auto [set, index] : kPlan.at(threadNo))
            f(set, index);
    }
}