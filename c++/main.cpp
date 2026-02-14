#include "solver.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

struct CliOptions {
    int day = -1;              // required
    int part = 0;              // 0 = both, 1 or 2
    std::string input_path;    // required
    bool time = false;
};

static std::vector<std::string> read_lines(const std::string& path) {
    std::ifstream in(path);
    if (!in) {
        throw std::runtime_error("Failed to open input file: " + path);
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

static void print_usage(const char* prog) {
    std::cerr
        << "Usage:\n"
        << "  " << prog << " --day N --input path [--part 1|2] [--time]\n\n"
        << "Examples:\n"
        << "  " << prog << " --day 1 --input inputs/day01.txt\n"
        << "  " << prog << " --day 1 --part 2 --input inputs/day01.txt --time\n";
}

static CliOptions parse_args(int argc, char** argv) {
    CliOptions opts;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        auto need_value = [&](const std::string& name) -> std::string {
            if (i + 1 >= argc) {
                throw std::runtime_error("Missing value for " + name);
            }
            return argv[++i];
        };

        if (arg == "--day") {
            opts.day = std::stoi(need_value("--day"));
        } else if (arg == "--part") {
            opts.part = std::stoi(need_value("--part"));
            if (opts.part != 1 && opts.part != 2) {
                throw std::runtime_error("--part must be 1 or 2");
            }
        } else if (arg == "--input") {
            opts.input_path = need_value("--input");
        } else if (arg == "--time") {
            opts.time = true;
        } else if (arg == "--help" || arg == "-h") {
            print_usage(argv[0]);
            std::exit(0);
        } else {
            throw std::runtime_error("Unknown argument: " + arg);
        }
    }

    if (opts.day < 1) throw std::runtime_error("Missing or invalid --day");
    if (opts.input_path.empty()) throw std::runtime_error("Missing --input");
    return opts;
}

template <typename F>
static std::string run_with_optional_timing(F&& fn, bool timing, const std::string& label) {
    if (!timing) return fn();

    const auto t0 = std::chrono::high_resolution_clock::now();
    std::string result = fn();
    const auto t1 = std::chrono::high_resolution_clock::now();

    const auto us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
    std::cerr << label << " took " << us << " us\n";
    return result;
}

int main(int argc, char** argv) {
    try {
        const CliOptions opts = parse_args(argc, argv);
        const auto lines = read_lines(opts.input_path);

        const DaySolver* solver = SolverRegistry::instance().get_day(opts.day);
        if (!solver) {
            std::cerr << "No solver registered for day " << opts.day << "\n";
            return 2;
        }

        if (opts.part == 0 || opts.part == 1) {
            const std::string ans1 = run_with_optional_timing(
                [&]() { return solver->part1(lines); },
                opts.time,
                "Day " + std::to_string(opts.day) + " Part 1"
            );
            std::cout << "Part 1: " << ans1 << "\n";
        }

        if (opts.part == 0 || opts.part == 2) {
            const std::string ans2 = run_with_optional_timing(
                [&]() { return solver->part2(lines); },
                opts.time,
                "Day " + std::to_string(opts.day) + " Part 2"
            );
            std::cout << "Part 2: " << ans2 << "\n";
        }

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        print_usage(argv[0]);
        return 1;
    }
}
