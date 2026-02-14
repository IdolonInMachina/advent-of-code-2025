#include "../solver.h"
#include <string>
#include <vector>
#include <iostream>

class SimSafe {
public:
    int dial = 50; // Initial dial position, always starts at 50 (per definiton)
    int zero_count = 0; // Count of the number of times the dial lands on zero
    int zero_click_count = 0; // Count of the number of times the dial passes through zero

    void follow_instructions(const std::vector<std::string>& instructions) {
        for (const std::string& inst : instructions) {
            const int turn_amount = std::stoi(inst.substr(1));
            const char turn_dir = inst.at(0);
            const int start = dial;

            int distance_to_zero = 100;
            if (turn_dir == 'L') {
                distance_to_zero = start;
                if (distance_to_zero == 0) distance_to_zero = 100;
            } else if (turn_dir == 'R') {
                distance_to_zero = (100 - start) % 100;
                if (distance_to_zero == 0) distance_to_zero = 100;
            }
            if (turn_amount >= distance_to_zero) {
                // First hit at distance_to_zero, then every 100 clicks after that
                zero_click_count += 1 + (turn_amount - distance_to_zero) / 100;
            }

            
            // Update dial position
            if (turn_dir == 'L') {
                dial = (start - (turn_amount % 100) + 100) % 100;
            } else if (turn_dir == 'R') {
                dial = (start + (turn_amount % 100)) % 100;
            }

            if (dial == 0) {
                zero_count++;
            }
        }


    }
};

static std::string solve_day1_part1(const std::vector<std::string>& lines) {
    SimSafe safe;
    safe.follow_instructions(lines);
    return std::to_string(safe.zero_count);
}

static std::string solve_day1_part2(const std::vector<std::string>& lines) {
    SimSafe safe;
    safe.follow_instructions(lines);
    return std::to_string(safe.zero_click_count);
}

REGISTER_DAY(1, solve_day1_part1, solve_day1_part2);
