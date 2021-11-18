#ifndef CPP06_EX01_SERIALIZER_HPP_
# define CPP06_EX01_SERIALIZER_HPP_

# include <cstdlib>
# include "Data.hpp"

class Seriaizer {
    public:
        static uintptr_t    serialize(Data* data);
        static Data*        deserialize(uintptr_t ptr);

    private:
        Seriaizer();
        Seriaizer(const Seriaizer& from);
        Seriaizer&  operator=(const Seriaizer &rhs);
        ~Seriaizer();
};

#endif
