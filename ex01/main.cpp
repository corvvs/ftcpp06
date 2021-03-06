#include <iostream>
#include <exception>
# include <cstdlib>
#include "Data.hpp"
#include "Constants.hpp"

uintptr_t   serialize(Data* data) {
    return reinterpret_cast<uintptr_t>(data);
}

Data*       deserialize(uintptr_t ptr) {
    return reinterpret_cast<Data *>(ptr);
}

int main() {
    try {
        std::srand((unsigned int) std::time(NULL));
        Data *d1 = Data::uuid4();
        std::cout << "d1:\t\t" << d1 << std::endl;
        std::cout
            << "value:\t\t"
            << *d1 << std::endl;
        uintptr_t ptr = serialize(d1);
        std::cout << "uintptr_t:\t  " << ptr << std::endl;
        Data *d2 = deserialize(ptr);
        std::cout << "d2:\t\t" << d2 << std::endl;
        std::cout
            << "value:\t\t"
            << *d2 << std::endl;
        std::cout << "d1 == d2?:\t" << std::boolalpha << (d1 == d2) << std::endl;
        delete d2;
    } catch (std::exception& e) {
        std::cout
            << Constants::kTextWarning
            << e.what()
            << Constants::kTextReset << std::endl;
    }
}
