#ifndef CPP06_EX00_CONVERTER_HPP_
# define CPP06_EX00_CONVERTER_HPP_

# include <string>
# include <sstream>
# include <cctype>
# include <limits>
# include <cmath>
# include "Utils.hpp"
# include "Constants.hpp"

class Converter {
    public:
        static void         VerdictAndPrint(const std::string str);

    private:
        Converter();
        Converter(const Converter& from);
        Converter&  operator=(const Converter &rhs);
        ~Converter();

        static bool         IsChar(const std::string str);
        static bool         IsInt(const std::string str);
        static bool         IsFloat(const std::string str);
        static bool         IsDouble(const std::string str);
        static bool         IsFloatLike(const std::string str);

        static int          ToInt(const std::string str);

        static float        ToFloat(const std::string str);
        template<typename T>
        static T            ToFloatLike(const std::string str);

        template<typename T>
        static void         PrintValues(const T val, bool determined = true);
        template<typename FLT>
        static void         PrintFloatLikeAsChar(const FLT val);
        template<typename T>
        static void         PrintAsChar(const T val);
        template<typename FLT>
        static void         PrintFloatLikeAsInt(const FLT val);
        template<typename T>
        static void         PrintAsInt(const T val);
        template<typename INT>
        static void         PrintIntLikeAsFloat(const INT val);
        template<typename T>
        static void         PrintAsFloat(const T val);
        template<typename INT>
        static void         PrintIntLikeAsDouble(const INT val);
        template<typename T>
        static void         PrintAsDouble(const T val);
};

#endif
