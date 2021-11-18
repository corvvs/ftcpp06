#include "Serializer.hpp"

Seriaizer::Seriaizer() {}

Seriaizer::Seriaizer(const Seriaizer& from) {
    (void)from;
}

Seriaizer&  Seriaizer::operator=(const Seriaizer &rhs) {
    (void)rhs;
    return *this;
}

Seriaizer::~Seriaizer() {}

uintptr_t   Seriaizer::serialize(Data* data) {
    void *vp = data;
    return reinterpret_cast<uintptr_t>(vp);
}

Data*       Seriaizer::deserialize(uintptr_t ptr) {
    void *vp = reinterpret_cast<void *>(ptr);
    return reinterpret_cast<Data *>(vp);
}
