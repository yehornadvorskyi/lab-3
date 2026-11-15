#include "schedule.h"
#include "action.h"

#include <array>
#include <vector>
#include <latch>
#include <stdexcept>
#include <string_view>

using namespace std;

namespace schedule
{
    namespace
    {

        string_view inputsOf(char set)
        {
            switch (set)
            {
            case 'a': case 'b': return "";
            case 'e': case 'g': return "a";
            case 'h': case 'i': return "b";
            case 'k':           return "e";
            case 'c':           return "gh";
            case 'd':           return "i";
            case 'f':           return "kcd";
            }
            throw logic_error("unknown set");
        }

        latch done_a{ 6 };
        latch done_b{ 5 };
        latch done_c{ 8 };
        latch done_d{ 5 };
        latch done_e{ 8 };
        latch done_f{ 9 };
        latch done_g{ 4 };
        latch done_h{ 5 };
        latch done_i{ 6 };
        latch done_k{ 4 };

        latch& done(char set)
        {
            switch (set)
            {
            case 'a': return done_a;
            case 'b': return done_b;
            case 'c': return done_c;
            case 'd': return done_d;
            case 'e': return done_e;
            case 'f': return done_f;
            case 'g': return done_g;
            case 'h': return done_h;
            case 'i': return done_i;
            case 'k': return done_k;
            }
            throw logic_error("unknown set");
        }

        struct Step
        {
            char set;
            int index;
        };

        const array<vector<Step>, kThreads> kPlan{ {
            {{'a', 1}, {'a', 6}, {'b', 5}, {'e', 5}, {'g', 2}, {'h', 3}, {'i', 3},{'k', 2}, {'d', 3}, {'c', 3}, {'c', 8}, {'f', 1}, {'f', 6}},
            {{'a', 2}, {'b', 1}, {'e', 1}, {'e', 6}, {'g', 3}, {'h', 4}, {'i', 4},{'k', 3}, {'d', 4}, {'c', 4}, {'f', 2}, {'f', 7}},
            {{'a', 3}, {'b', 2}, {'e', 2}, {'e', 7}, {'g', 4}, {'h', 5}, {'i', 5},{'k', 4}, {'d', 5}, {'c', 5}, {'f', 3}, {'f', 8}},
            {{'a', 4}, {'b', 3}, {'e', 3}, {'e', 8}, {'h', 1}, {'i', 1}, {'i', 6},{'d', 1}, {'c', 1}, {'c', 6}, {'f', 4}, {'f', 9}},
            {{'a', 5}, {'b', 4}, {'e', 4}, {'g', 1}, {'h', 2}, {'i', 2}, {'k', 1},{'d', 2}, {'c', 2}, {'c', 7}, {'f', 5}},
        } };
    }

    void runThread(int threadNo)
    {
        char current = 0;
        for (const auto [set, index] : kPlan.at(threadNo))
        {
            if (set != current)
            {
                for (char input : inputsOf(set))
                    done(input).wait();
                current = set;
            }

            f(set, index);
            done(set).count_down();
        }
    }
}