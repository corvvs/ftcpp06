#ifndef CPP06_EX00_UTILS_HPP_
# define CPP06_EX00_UTILS_HPP_

# include <iostream>
# include <iomanip>
# include <string>
# include <sstream>
# include <cctype>

namespace Utils {
    std::string TrimString(
        const std::string str,
        const std::string charset = "\n\t\b\v\f "
    );

    std::string StripLeft(
        const std::string str,
        const std::string charset = "\n\t\b\v\f "
    );

    std::string TrimLeftRepeated(
        const std::string str,
        const std::string rep
    );

    std::string DownCase(
        const std::string str
    );
}

#endif
