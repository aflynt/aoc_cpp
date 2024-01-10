#ifndef DAY02_H
#define DAY02_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>


auto get_lines_d2(const std::string& fname) -> std::vector<std::string>;
std::vector<std::string> split_str(std::string s, const std::string& delimiter);

void solve_day02(const std::string& fname);


#endif // DAY02_H
