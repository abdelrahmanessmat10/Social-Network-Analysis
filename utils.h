#ifndef UTILS_H
#define UTILS_H

#include <string>

inline std::string trim(const std::string& s) {
    size_t first = s.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = s.find_last_not_of(' ');
    return s.substr(first, (last - first + 1));
}

#endif // UTILS_H