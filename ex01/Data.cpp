#include "Data.hpp"

Data::Data():
    id1_(0), id2_(0), id3_(0), id4_(0) {}

Data::Data(const Data& from):
    id1_(from.id1_), id2_(from.id2_), id3_(from.id3_), id4_(from.id4_) {}

Data&   Data::operator=(const Data &rhs) {
    id1_ = rhs.id1_;
    id2_ = rhs.id2_;
    id3_ = rhs.id3_;
    id4_ = rhs.id4_;
    return *this;
}

Data::~Data() {}

typedef uint16_t rand_t;

Data*   Data::uuid4(void) {
    Data* mem = new Data();

    const std::size_t full_size = 128;
    unsigned char bits[full_size];
    rand_t *chunks = reinterpret_cast<rand_t *>(bits);
    memset(bits, 0, full_size);
    const std::size_t chunk_size = sizeof(rand_t);
    for (std::size_t i = 0; i < full_size / chunk_size / 8; i += 1) {
        rand_t u = (static_cast<rand_t>(rand()));
        rand_t *p = chunks + i;
        *p = *p | u;
    }
    mem->id1_ = (*(reinterpret_cast<uint32_t *>(bits + 4 * 0))) & HeadMask;
    mem->id2_ = (*(reinterpret_cast<uint32_t *>(bits + 4 * 1)));
    mem->id3_ = (*(reinterpret_cast<uint32_t *>(bits + 4 * 2)));
    mem->id4_ = (*(reinterpret_cast<uint32_t *>(bits + 4 * 3)));
    return mem;
}

uint32_t    Data::getId1(void) const {
    return id1_;
}

uint32_t    Data::getId2(void) const {
    return id2_;
}

uint32_t    Data::getId3(void) const {
    return id3_;
}

uint32_t    Data::getId4(void) const {
    return id4_;
}

std::ostream& operator<<(std::ostream& stream, const Data& value) {
    // 4*8 = 32bit = 26 + 6
    uint32_t chunk1 = (value.getId1() << 6) | (value.getId2() >> 26);
    // 4*4 = 16bit
    uint32_t chunk2 = (value.getId2() >> 10) & 0xffff;
    // 4*3 = 12bit = 10 + 2
    uint32_t chunk3 = (value.getId2() & 0x3ff) | (value.getId3() >> 30);
    // 4*3 + 2 = 14bit
    uint32_t chunk4 = ((value.getId3() >> 16) & 0x3fff) | 0x8000;
    // 4*4 = 16bit
    uint32_t chunk5 = (value.getId3()) & 0xffff;
    // 4*8 = 32bit
    uint32_t chunk6 = (value.getId4());
    return stream
        << std::setfill('0')
        << std::setw(8)
        << std::hex
        << std::showpoint
        << chunk1 << "-"
        << std::setw(4)
        << chunk2 << "-"
        << "4"
        << std::setw(3)
        << chunk3 << "-"
        << std::setw(4)
        << chunk4 << "-"
        << std::setw(4)
        << chunk5
        << std::setw(8)
        << chunk6;
}

