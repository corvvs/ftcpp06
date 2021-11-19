#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Constants.hpp"

// that randomly instanciates A, B or C and returns the instance as a Base pointer.
// Feel free to use anything you like for the randomness.
Base*   generate(void) {
    Base *p = NULL;
    switch (std::rand() % 3) {
        case 0:
            p = new A();
            std::cout
                << Constants::kTextInfo
                << "[" << p << "] "
                << "generated:\t\tA"
                << Constants::kTextReset << std::endl;
            break;
        case 1:
            p = new B();
            std::cout
                << Constants::kTextInfo
                << "[" << p << "] "
                << "generated:\t\tB"
                << Constants::kTextReset << std::endl;
            break;
        case 2:
            p = new C();
            std::cout
                << Constants::kTextInfo
                << "[" << p << "] "
                << "generated:\t\tC"
                << Constants::kTextReset << std::endl;
            break;
    }
    return p;
}

// that displays "A", "B" or "C" according to the real type of p.
void    identify(Base* p) {
    if (dynamic_cast<A *>(p)) {
        std::cout << "A" << std::endl;
        return;
    }
    if (dynamic_cast<B *>(p)) {
        std::cout << "B" << std::endl;
        return;
    }
    if (dynamic_cast<C *>(p)) {
        std::cout << "C" << std::endl;
        return;
    }
    throw std::string("Unexpected Pointer is given");
}

// You should never use a pointer inside
// this function. that displays "A", "B" or "C" according to the real type of p.
void    identify(Base& p) {
    try {
        A& q = dynamic_cast<A &>(p);
        static_cast<void>(q);
        std::cout << "A" << std::endl;
        return;
    } catch (std::bad_cast& e) {

    }
    try {
        B& q = dynamic_cast<B &>(p);
        static_cast<void>(q);
        std::cout << "B" << std::endl;
        return;
    } catch (std::bad_cast& e) {

    }
    try {
        C& q = dynamic_cast<C &>(p);
        static_cast<void>(q);
        std::cout << "C" << std::endl;
        return;
    } catch (std::bad_cast& e) {

    }
    throw std::string("Unexpected Reference is given");
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    for (int i = 0; i < 100; i += 1) {
        std::cout
            << "Trial #" << i
            << std::endl;
        Base* b = NULL;
        try {
            b = generate();
            std::cout
                << Constants::kTextInfo
                << "[" << b << "] "
                << "id by pointer:\t\t"
                << Constants::kTextReset;
            identify(b);
            std::cout
                << Constants::kTextInfo
                << "[" << b << "] "
                << "id by reference:\t"
                << Constants::kTextReset;
            identify(*b);
        } catch(...) {
            std::cout
                << Constants::kTextError
                << "** some unexpected exception detected **"
                << Constants::kTextReset << std::endl;
        }
        delete b;
    }
}


