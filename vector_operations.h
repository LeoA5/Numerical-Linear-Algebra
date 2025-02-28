#ifndef VECTOR_OPERATIONS_H
#define VECTOR_OPERATIONS_H

#include<vector>
#include<stdexcept>
#include<functional>
#include<type_traits>

template<typename T>
// Not functional pattern and a hack fix because c++ hates me.
std::vector<T> operator+(const std::vector<T>& v, const std::vector<T>& w)
{
    std::vector<T> result(v);
    result.insert(result.end(), w.begin(), w.end());
    return result;
}

template<typename T>
std::function<T (const std::vector<T>&)> dot_product(
    const std::vector<T>& left
)
{
    if (!std::is_arithmetic_v<T>)
    {
        throw std::invalid_argument("Parameter is not an arithmetic type.");
    }
    return [left] (const std::vector<T>& right) -> T
    {
        if (left.size() != right.size())
        {
            throw std::length_error("Vectors are not equidimensional.");
        }
        if (left.size() == 0)
        {
            throw std::length_error("Vectors are 0-dimensional.");
        }
        std::function<T (int)> dot_from_index = 
        [&left, &right, &dot_from_index] (size_t n) -> T
        {
            if (n == left.size()) { return 0; }
            return left[n] * right[n] + dot_from_index(n + 1);
        };
        return dot_from_index(0);
    };
}

#endif