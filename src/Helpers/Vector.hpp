#ifndef HELPERS_VECTOR_HPP
#define HELPERS_VECTOR_HPP

#include <vector>
#include <iostream>

namespace Vector{

    template<class T>
    T sum(std::vector<T> x)
    {
        T accumulation;
        for (int i = 0; i < x.size(); ++i) {
            accumulation+=x[i];
        }
        return accumulation;
    }

    template <class T>
    T avg(std::vector<T> x)
    {
        return Vector::sum<T>(x) / x.size();
    }

    template<class T>
    std::vector< std::vector<T> > generateMask(int height, int width)
    {
        std::vector< std::vector<T> > mask = std::vector< std::vector<T> >();
        for (int i = 0; i < height; ++i) {
            std::vector<T> tmp;
            tmp.resize(width);
            mask.push_back(tmp);
        }
        return mask;
    }
}

#endif //HELPERS_VECTOR_HPP
