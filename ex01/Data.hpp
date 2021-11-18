#ifndef CPP06_EX01_DATA_HPP_
# define CPP06_EX01_DATA_HPP_

# include <iostream>
# include <iomanip>
# include <cstdlib>
# include <stdint.h>

class Data {
    public:
        Data(const Data& from);
        Data&  operator=(const Data &rhs);
        virtual ~Data();

        static Data*    uuid4(void);
        static const uint32_t HeadMask = (1u << 26) - 1;

        uint32_t    getId1(void) const;
        uint32_t    getId2(void) const;
        uint32_t    getId3(void) const;
        uint32_t    getId4(void) const;

    private:
        Data();

        uint32_t    id1_;
        uint32_t    id2_;
        uint32_t    id3_;
        uint32_t    id4_;
};

std::ostream& operator<<(std::ostream& stream, const Data& value);

#endif
