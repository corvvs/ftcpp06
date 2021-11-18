#include "Converter.hpp"

bool    Converter::IsChar(const std::string str) {
    if (str.length() != 3) { return false; }
    return str[0] == '\'' && !!std::isprint(str[1]) && str[2] == '\'';
}

bool    Converter::IsInt(const std::string str) {
    const std::string ltrimmed = str.substr(0, 2) == "+-"
            ? Utils::TrimLeftRepeated(str, "+-")
            : Utils::TrimLeftRepeated(str, "-+");
    if (ltrimmed.length() < 1) { return false; }
    if (ltrimmed == "0") { return true; }
    // character check
    std::size_t i = 0;
    if (ltrimmed[0] == '-' || ltrimmed[0] == '+') { i += 1; }
    for (; i < ltrimmed.length(); i += 1) {
        if (std::isdigit(ltrimmed[i])) { continue; }
        return false;
    }
    // range check
    std::stringstream transformer;
    transformer << ltrimmed;
    int converted;
    transformer >> converted;
    transformer.clear();
    transformer << converted;
    std::string reverse_converted;
    transformer >> reverse_converted;
    return ltrimmed == reverse_converted;
}

bool    Converter::IsFloat(const std::string str) {
    const std::size_t len = str.length();
    if (len < 2) { return false; }
    if (str[len - 1] != 'f') { return false; }
    return IsFloatLike(str.substr(0, len - 1));
}

bool    Converter::IsDouble(const std::string str) {
    return IsFloatLike(str);
}

bool    Converter::IsFloatLike(const std::string str) {
    if (str == "+nan") { return true; }
    if (str == "+inf") { return true; }
    if (str == "-nan") { return true; }
    if (str == "-inf") { return true; }
    if (str == "nan") { return true; }
    if (str == "inf") { return true; }
    const std::string ltrimmed = str.substr(0, 2) == "+-"
        ? Utils::TrimLeftRepeated(str, "+-")
        : Utils::TrimLeftRepeated(str, "-+");
    std::size_t i = 0;
    bool dot = false;
    if (ltrimmed[0] == '-' || ltrimmed[0] == '+') { i += 1; }
    for (; i < ltrimmed.length(); i += 1) {
        if (std::isdigit(ltrimmed[i])) { continue; }
        if (ltrimmed[i] == '.') {
            if (dot) { return false; }
            dot = true;
            continue;
        }
        return false;
    }
    return true;
}

int     Converter::ToInt(const std::string intstr) {
    std::stringstream transformer;
    transformer << intstr;
    int val;
    transformer >> val;
    return val;
}

template<typename T>
T       Converter::ToFloatLike(const std::string str) {
    if (str == "+nan") { return std::numeric_limits<T>::quiet_NaN(); }
    if (str == "nan") { return std::numeric_limits<T>::quiet_NaN(); }
    if (str == "-nan") { return -std::numeric_limits<T>::quiet_NaN(); }
    if (str == "inf") { return std::numeric_limits<T>::infinity(); }
    if (str == "+inf") { return std::numeric_limits<T>::infinity(); }
    if (str == "-inf") { return -std::numeric_limits<T>::infinity(); }
    std::stringstream transformer;
    transformer << str;
    T val;
    transformer >> val;
    return val;
}

template<>
void    Converter::PrintAsChar(const char val) {
    if (std::isprint(val)) {
        std::cout << "'" << val << "'" << std::endl;
    } else {
        std::cout << "Non displayable" << std::endl;
    }
}

template<>
void    Converter::PrintAsChar(const int val) {
    if (val < -128 || 128 <= val) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsChar(static_cast<char>(val));
    }
}

template<typename FLT>
void    Converter::PrintFloatLikeAsChar(const FLT val) {
    if (isnan(val) || isinf(val) || val < -128 || 128 <= val) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsChar(static_cast<char>(val));
    }
}

template<typename FLT>
void    Converter::PrintFloatLikeAsInt(const FLT val) {
    if (isnan(val) || isinf(val) || val < INT_MIN || INT_MAX <= val - 1) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsInt(static_cast<int>(val));
    }
}

template<typename T>
void    Converter::PrintAsInt(const T val) {
    std::cout << static_cast<int>(val) << std::endl;
}

template<typename INT>
void    Converter::PrintIntLikeAsFloat(const INT val) {
    std::cout.precision(1);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<float>(val) << "f"
        << std::defaultfloat
        << std::endl;
}

template<typename T>
void    Converter::PrintAsFloat(const T val) {
    std::cout.precision(8);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<float>(val) << "f"
        << std::defaultfloat
        << std::endl;
}

template<typename INT>
void    Converter::PrintIntLikeAsDouble(const INT val) {
    std::cout.precision(1);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<double>(val)
        << std::defaultfloat
        << std::endl;
}

template<typename T>
void    Converter::PrintAsDouble(const T val) {
    std::cout.precision(15);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<double>(val)
        << std::defaultfloat
        << std::endl;
}

template<>
void    Converter::PrintValues(const char val, bool determined) {
    std::cout << (determined ? Constants::kTextInfo : Constants::kTextWarning);
    std::cout << "char: "; PrintAsChar(val);
    std::cout << Constants::kTextReset;
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << "float: ";  PrintIntLikeAsFloat(val);
    std::cout << "double: "; PrintIntLikeAsDouble(val);
}

template<>
void    Converter::PrintValues(const int val, bool determined) {
    std::cout << "char: ";   PrintAsChar(val);
    std::cout << (determined ? Constants::kTextInfo : Constants::kTextWarning);
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << Constants::kTextReset;
    std::cout << "float: ";  PrintIntLikeAsFloat(val);
    std::cout << "double: "; PrintIntLikeAsDouble(val);
}

template<>
void    Converter::PrintValues(const float val, bool determined) {
    std::cout << "char: ";   PrintFloatLikeAsChar(val);
    std::cout << "int: ";    PrintFloatLikeAsInt(val);
    std::cout << (determined ? Constants::kTextInfo : Constants::kTextWarning);
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << Constants::kTextReset;
    std::cout << "double: "; PrintAsDouble(val);
}

template<>
void    Converter::PrintValues(const double val, bool determined) {
    std::cout << "char: ";   PrintFloatLikeAsChar(val);
    std::cout << "int: ";    PrintFloatLikeAsInt(val);
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << (determined ? Constants::kTextInfo : Constants::kTextWarning);
    std::cout << "double: "; PrintAsDouble(val);
    std::cout << Constants::kTextReset;
}

void    Converter::VerdictAndPrint(const std::string str) {
    if (IsChar(str)) {
        PrintValues(str[1]);
    } else if (IsInt(str)) {
        PrintValues(ToInt(str));
    } else if (IsFloat(str)) {
        PrintValues(ToFloatLike<float>(str));
    } else if (IsDouble(str)) {
        PrintValues(ToFloatLike<double>(str));
    } else {
        PrintValues(ToFloatLike<double>(str), false);
    }
}
