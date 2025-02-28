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

template <typename T>
std::function<std::vector<T> (T)> scale(const std::vector<T>& v)
{
    return [&v] (T scale_factor)
    {
        std::function<std::vector<T> (size_t)> scale_vector =
        [&v, scale_factor, &scale_vector] (size_t row) -> std::vector<T>
        {
            if (row == v.size()) { return {}; }
            return std::vector<T>{scale_factor * v[row]} + scale_vector(row + 1);
        };
        return scale_vector(0);
    };
}

template <typename T>
std::function<std::vector<T> (const std::vector<T>&)> add(const std::vector<T>& left)
{
    return [&left] (const std::vector<T>& right)
    {
        if (right.size() != left.size())
        {
            throw std::invalid_argument("Both vectors must be the same size.");
        }
        std::function<std::vector<T> (size_t)> add_vectors =
        [&left, &right, &add_vectors] (size_t row) -> std::vector<T>
        {
            if (row == left.size()) { return {}; }
            return std::vector<T> {left[row] + right[row]} + add_vectors(row + 1);
        };
        return add_vectors(0);
    };
}

#endif