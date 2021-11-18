#include "Utils.hpp"

std::string Utils::TrimString(
    const std::string str,
    const std::string charset
) {
    std::size_t start = 0;
    std::size_t end = str.length();
    while (start < end && charset.find(str[start]) != std::string::npos) {
        start += 1;
    }
    while (start < end && charset.find(str[end - 1]) != std::string::npos) {
        end -= 1;
    }
    return str.substr(start, end - start);
}

std::string Utils::TrimLeftRepeated(
    const std::string str,
    const std::string rep
) {
    std::size_t start = 0;
    std::size_t end = str.length();
    const std::size_t replen = rep.length();
    while (start < end && str.substr(start, replen) == rep) {
        start += replen;
    }
    return str.substr(start);
}

std::string Utils::DownCase(
    const std::string str
) {
    std::string ret(str);
    for (std::size_t i = 0; i < str.length(); i += 1) {
        if (std::isupper(str[i])) {
            ret[i] = std::tolower(str[i]);
        }
    }
    return ret;
}
