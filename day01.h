#ifndef DAY01_H
#define DAY01_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <map>

auto get_lines(const std::string& fname) -> std::vector<std::string>;
auto get_line_results(const std::vector<std::string>& lines, const std::vector<std::string>& good_chars) -> unsigned long;
auto get_line_result(const std::string& line, const std::vector<std::string>& good_chars) -> unsigned long;

void solve_day01(const std::string& fname);

#endif // DAY01_H
