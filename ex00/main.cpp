#include <iostream>
#include <sstream>
#include "Converter.hpp"
#include "Constants.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout
            << Constants::kTextWarning
            << "least 1 argument needed"
            << Constants::kTextReset << std::endl;
        return 1;
    }
    const std::string s(argv[1]);
    Converter::VerdictAndPrint(s);
    return 0;
}
