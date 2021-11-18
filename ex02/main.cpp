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
    {
        A* q = dynamic_cast<A *>(p);
        if (q) {
            std::cout << "A" << std::endl;
            return;
        }
    }
    {
        B* q = dynamic_cast<B *>(p);
        if (q) {
            std::cout << "B" << std::endl;
            return;
        }
    }
    {
        C* q = dynamic_cast<C *>(p);
        if (q) {
            std::cout << "C" << std::endl;
            return;
        }
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
    throw std::string("Unexpected Pointer is given");
}

int main() {
    std::srand((unsigned int) std::time(NULL));
    for (int i = 0; i < 100; i += 1) {
        try {
            Base* b = generate();
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
    }
}


