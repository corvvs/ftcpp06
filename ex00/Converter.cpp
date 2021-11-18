#include "Converter.hpp"

bool    Converter::IsChar(const std::string str) {
    if (str.length() != 1) { return false; }
    return !!std::isprint(str[0]);
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
    return IsCommonFloat(str.substr(0, len - 1));
}

bool    Converter::IsDouble(const std::string str) {
    return IsCommonFloat(str);
}

bool    Converter::IsCommonFloat(const std::string str) {
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

float   Converter::ToFloat(const std::string floatstr) {
    const std::string str = floatstr.substr(0, floatstr.length() - 1);
    if (str == "+nan") { return std::numeric_limits<float>::quiet_NaN(); }
    if (str == "nan") { return std::numeric_limits<float>::quiet_NaN(); }
    if (str == "-nan") { return -std::numeric_limits<float>::quiet_NaN(); }
    if (str == "inf") { return std::numeric_limits<float>::infinity(); }
    if (str == "+inf") { return std::numeric_limits<float>::infinity(); }
    if (str == "-inf") { return -std::numeric_limits<float>::infinity(); }
    std::stringstream transformer;
    transformer << str;
    float val;
    transformer >> val;
    return val;
}

double  Converter::ToDouble(const std::string doublestr) {
    const std::string str = doublestr;
    if (str == "+nan") { return std::numeric_limits<double>::quiet_NaN(); }
    if (str == "nan") { return std::numeric_limits<double>::quiet_NaN(); }
    if (str == "-nan") { return -std::numeric_limits<double>::quiet_NaN(); }
    if (str == "inf") { return std::numeric_limits<double>::infinity(); }
    if (str == "+inf") { return std::numeric_limits<double>::infinity(); }
    if (str == "-inf") { return -std::numeric_limits<double>::infinity(); }
    std::stringstream transformer;
    transformer << str;
    double val;
    transformer >> val;
    return val;
}

template<>
void    Converter::PrintAsChar(const int val) {
    if (!isascii(val)) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsChar(static_cast<char>(val));
    }
}
template<>
void    Converter::PrintAsChar(const float val) {
    if (isnan(val) || isinf(val) || val < 0 || 128 <= val) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsChar(static_cast<char>(val));
    }
}

template<>
void    Converter::PrintAsChar(const double val) {
    if (isnan(val) || isinf(val) || val < 0 || 128 <= val) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsChar(static_cast<char>(val));
    }
}

template<typename T>
void    Converter::PrintAsChar(const T val) {
    if (std::isprint(static_cast<int>(val))) {
        std::cout << "'" << static_cast<char>(val) << "'" << std::endl;
    } else {
        std::cout << "Non displayable" << std::endl;
    }
}

template<>
void    Converter::PrintAsInt(const float val) {
    if (isnan(val) || isinf(val) || val < INT_MIN || INT_MAX <= val - 1) {
        std::cout << "impossible" << std::endl;
    } else {
        PrintAsInt(static_cast<int>(val));
    }
}

template<>
void    Converter::PrintAsInt(const double val) {
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

template<>
void    Converter::PrintAsFloat(const char val) {
    std::cout.precision(1);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<float>(val) << "f"
        << std::defaultfloat
        << std::endl;
}

template<>
void    Converter::PrintAsFloat(const int val) {
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
    std::cout.precision(6);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<float>(val) << "f"
        << std::defaultfloat
        << std::endl;
}

template<>
void    Converter::PrintAsDouble(const char val) {
    std::cout.precision(1);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<double>(val)
        << std::defaultfloat
        << std::endl;
}

template<>
void    Converter::PrintAsDouble(const int val) {
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
    std::cout.precision(6);
    std::cout
        << std::showpoint
        << std::fixed
        << static_cast<double>(val)
        << std::defaultfloat
        << std::endl;
}

template<>
void    Converter::PrintValues(const char val) {
    std::cout << Constants::kTextInfo;
    std::cout << "char: "; PrintAsChar(val);
    std::cout << Constants::kTextReset;
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << "double: "; PrintAsDouble(val);
}

template<>
void    Converter::PrintValues(const int val) {
    std::cout << "char: ";   PrintAsChar(val);
    std::cout << Constants::kTextInfo;
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << Constants::kTextReset;
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << "double: "; PrintAsDouble(val);
}

template<>
void    Converter::PrintValues(const float val) {
    std::cout << "char: ";   PrintAsChar(val);
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << Constants::kTextInfo;
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << Constants::kTextReset;
    std::cout << "double: "; PrintAsDouble(val);
}

template<>
void    Converter::PrintValues(const double val) {
    std::cout << "char: ";   PrintAsChar(val);
    std::cout << "int: ";    PrintAsInt(val);
    std::cout << "float: ";  PrintAsFloat(val);
    std::cout << Constants::kTextInfo;
    std::cout << "double: "; PrintAsDouble(val);
    std::cout << Constants::kTextReset;
}

void    Converter::VerdictAndPrint(const std::string str) {
    if (IsChar(str)) {
        PrintValues(str[0]);
    } else if (IsInt(str)) {
        PrintValues(ToInt(str));
    } else if (IsFloat(str)) {
        PrintValues(ToFloat(str));
    } else if (IsDouble(str)) {
        PrintValues(ToDouble(str));
    }
}
