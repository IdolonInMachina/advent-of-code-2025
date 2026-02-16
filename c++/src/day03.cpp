#include "../solver.h"
#include <string>
#include <vector>
#include <iostream>


class BatterySolver {
public:
    
    int get_maximum_joltage(const std::string& battery) {
        // The maximum joltage is the largest two digit number that can be formed by concatenating any two numbers in order (left-to-right, but not necessarily consecutively) from the battery string. For example, if the battery is "1234", the maximum joltage is 34.
        // For this, find the largest digit in the string (apart from the last digit). Then, find the next largest digit that appears after the first largest digit.
        char max_digit = '0';
        for (size_t i = 0; i < battery.length() - 1; ++i) {
            if (battery[i] > max_digit) { // We can just compare ASCII values to find the largest digit, no need to convert to int
                max_digit = battery[i];
            }
        }
        // Now, from the index of the max_digit, find the largest digit that appears after it
        size_t max_digit_index = battery.find(max_digit);
        char second_max_digit = battery[max_digit_index + 1]; // Initialize to the next digit after max_digit
        for (size_t i = max_digit_index + 1; i < battery.length(); i++) {
            if (battery[i] >= second_max_digit) { // Use >= to get the rightmost occurrence of the second max digit, which will give the largest possible two digit number
                second_max_digit = battery[i];
            }  
        }
        const std::string concat_digits = std::string() + max_digit + second_max_digit;
        return std::atoi(concat_digits.c_str());
    }

};


static std::string solve_day3_part1(const std::vector<std::string>& lines) {
    BatterySolver solver;
    int total_output_joltage = 0;
    for (const std::string& battery_array : lines) {
        int max_joltage = solver.get_maximum_joltage(battery_array);
        std::cout << "Battery: " << battery_array << ", Max Joltage: " << max_joltage << "\n";
        total_output_joltage += max_joltage;
    }
    return std::to_string(total_output_joltage);
}

static std::string solve_day3_part2(const std::vector<std::string>& lines) {
    return "";
}

REGISTER_DAY(3, solve_day3_part1, solve_day3_part2);