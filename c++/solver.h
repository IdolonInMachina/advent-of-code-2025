// Interface for the solver class, which is responsible for solving the challenge using any overwriting method.

#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

// Each solver takes all input lines and returns answer as string.
using SolverFn = std::function<std::string(const std::vector<std::string>&)>;

struct DaySolver {
    SolverFn part1;
    SolverFn part2;
};

// Registry: day -> solver pair
class SolverRegistry {
public:
    static SolverRegistry& instance() {
        static SolverRegistry inst;
        return inst;
    }

    void register_day(int day, DaySolver solver) {
        solvers_[day] = std::move(solver);
    }

    const DaySolver* get_day(int day) const {
        auto it = solvers_.find(day);
        if (it == solvers_.end()) return nullptr;
        return &it->second;
    }

private:
    std::unordered_map<int, DaySolver> solvers_;
};

// Helper macro to register day solvers from each dayXX.cpp
#define REGISTER_DAY(DAY, PART1_FN, PART2_FN)                            \
    namespace {                                                           \
    struct Day##DAY##Registrar {                                          \
        Day##DAY##Registrar() {                                           \
            SolverRegistry::instance().register_day((DAY), {PART1_FN, PART2_FN}); \
        }                                                                 \
    };                                                                    \
    static Day##DAY##Registrar g_day##DAY##_registrar;                    \
    }
