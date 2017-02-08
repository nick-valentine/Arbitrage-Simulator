#ifndef HELPERS_STRING_HPP
#define HELPERS_STRING_HPP

#include <string>
#include <boost/array.hpp>

namespace String {
    
    std::string boostArrToString(boost::array<char, 128> buffer);

};

#endif //HELPERS_STRING_HPP

