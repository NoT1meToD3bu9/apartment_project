#pragma once

#include <iostream>
#include <sstream>
#include <string>

class Input {
public:
    static std::string line(const std::string& prompt) {
        std::cout << prompt;
        std::string value;
        std::getline(std::cin, value);
        return value;
    }

    static int integer(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            int x;
            char c;
            if (ss >> x && !(ss >> c)) return x;
            std::cout << "Nhap so nguyen hop le!\n";
        }
    }

    static double realNumber(const std::string& prompt) {
        while (true) {
            std::cout << prompt;
            std::string s;
            std::getline(std::cin, s);
            std::stringstream ss(s);
            double x;
            char c;
            if (ss >> x && !(ss >> c)) return x;
            std::cout << "Nhap so thuc hop le!\n";
        }
    }
};

