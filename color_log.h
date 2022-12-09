#ifndef KSO_LAB_3_COLOR_LOG_H
#define KSO_LAB_3_COLOR_LOG_H

#include <string>
#include <iostream>

enum Color {
    RED = 31,
    GREEN = 32,
    WHITE = 37
};

void log(Color color, std::string* message) {
    std::cout << "\033[" << color << "m" << message << "\033[0m" << std::endl;
}

#endif //KSO_LAB_3_COLOR_LOG_H
