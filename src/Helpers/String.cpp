#include "Helpers/String.hpp"

std::string String::boostArrToString(boost::array<char, 128> buffer) 
{
    std::string data(buffer.begin(), buffer.end());
    return data;
}
