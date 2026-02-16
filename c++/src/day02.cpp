#include "../solver.h"
#include <string>
#include <vector>
#include <iostream>


class GiftComputer {
public:
    std::vector<long> invalid_ids = {};

    bool is_valid_id(const std::string& id) {
        // An invalid ID is made of a sequence of numbers that is repeated twice, i.e. 55 or 123123
        // Check if the ID is made of an odd number of digits - if so, it must be invalid since it can't be a perfectly repeating sequence
        if (id.length() % 2 != 0) return true;
        
        // Check if the first half of the ID is identical to the second half
        long half_length = id.length() / 2;
        const std::string first_half = id.substr(0, half_length);
        const std::string second_half = id.substr(half_length);
        
        if (first_half == second_half) {
            return false;
        }
        return true;
    };

    std::vector<std::string> get_id_ranges(const std::vector<std::string>& lines) {
        // Split input longo ranges based on commas, then iterate over each ID in that range (i.e. "11-22" means IDs 11, 12, ..., 22)
        std::vector<std::string> id_ranges;
        for (const std::string& line : lines) {
            size_t start = 0;
            size_t end = line.find(',');
            while (end != std::string::npos) {
                id_ranges.push_back(line.substr(start, end - start));
                start = end + 1;
                end = line.find(',', start);
            }
            id_ranges.push_back(line.substr(start));
        }
        return id_ranges;
    }

    std::vector<long> split_range(const std::string& id_range) {
        // Split a range like "11-22" longo a vector of longs {11, 12, ..., 22}
        // NOTE: this will break if the range is reversed, i.e. 22-11, but we can assume the input is well-formed and won't have that case
        std::vector<long> ids;
        size_t dash_pos = id_range.find('-');
        if (dash_pos == std::string::npos) {
            // Not a range, just a single ID
            ids.push_back(std::stol(id_range));
            return ids;
        }
        long start = std::stol(id_range.substr(0, dash_pos));
        long end = std::stol(id_range.substr(dash_pos + 1));
        for (long i = start; i <= end; ++i) {
            ids.push_back(i);
        }
        return ids;
    }
};



static std::string solve_day2_part1(const std::vector<std::string>& lines) {
    GiftComputer computer;

    // Split input longo ranges based on commas, then iterate over each ID in that range (i.e. "11-22" means IDs 11, 12, ..., 22)
    auto id_ranges = computer.get_id_ranges(lines);
    for (const auto &id_range : id_ranges) {
        auto ids = computer.split_range(id_range);
        for (long id : ids) {
            if (!computer.is_valid_id(std::to_string(id))) {
                std::cout << "Invalid ID: " << id << std::endl;
                computer.invalid_ids.push_back(id);
            }
        }
    }

    long sum_invalid = 0;
    for (long id : computer.invalid_ids) {
        sum_invalid += id;
    }
    return std::to_string(sum_invalid);
    
}

static std::string solve_day2_part2(const std::vector<std::string>& lines) {
    GiftComputer computer;

    return "0";
}

REGISTER_DAY(2, solve_day2_part1, solve_day2_part2);
