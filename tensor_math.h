#ifndef TENSOR_MATH_H
#define TENSOR_MATH_H
#include<functional>
#include<vector>
#include<stdexcept>
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
std::function<T (const std::vector<T>&)> dot_product(const std::vector<T>& left)
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
        std::function<T (int)> dot_from_index = [&left, &right, &dot_from_index] (size_t n) -> T
        {
            if (n == left.size()) { return 0; }
            return left[n] * right[n] + dot_from_index(n + 1);
        };
        return dot_from_index(0);
    };
}

template <typename T>
std::function<std::vector<T> (size_t)> get_matrix_row(const std::vector<std::vector<T>>& matrix)
{
    return [&matrix] (size_t row) -> std::vector<T>
    {
        if (row >= matrix.size())
        {
            throw std::invalid_argument("Row index is larger than the number of rows.");
        }
        return matrix[row];
    };
}

template <typename T>
std::function<std::vector<T> (size_t)> get_matrix_column(const std::vector<std::vector<T>>& matrix)
{
    return [&matrix] (size_t column) -> std::vector<T>
    {
        std::function<std::vector<T> (size_t)> get_column_elements = [&matrix, column, &get_column_elements] (size_t row) -> std::vector<T>
        {
            if (row >= matrix.size()) { return std::vector<T>(); }
            return std::vector<T>(1,matrix[row][column]) + get_column_elements(row+1);
        };
        return get_column_elements(0);
    };
}

template <typename T>
std::function<std::vector<std::vector<T>> (std::vector<std::vector<T>>)> matrix_multiply(const std::vector<std::vector<T>>& left)
{
    if (!std::is_arithmetic_v<T>)
    {
        throw std::invalid_argument("Parameter is not an arithmetic type.");
    }
    return [&left] (const std::vector<std::vector<T>>& right)->std::vector<std::vector<T>>
    {
        if (left[0].size() != right.size())
        {
            throw std::invalid_argument("Matrices are not multipliable.");
        }
        std::function<std::vector<std::vector<T>> (size_t)> iterate_left_rows = [&left, &right, &iterate_left_rows] (size_t row) -> std::vector<std::vector<T>>
        {
            if (row == left.size()) { return {}; }
            std::function<std::vector<T> (size_t)> iterate_right_columns = [&left, &right, row, &iterate_right_columns] (size_t column) -> std::vector<T>
            {
                if (column == right[0].size()) { return {}; }
                return std::vector<T>(1,dot_product(get_matrix_row(left)(row))(get_matrix_column(right)(column))) + iterate_right_columns(column + 1);
            };
            return std::vector<std::vector<T>>(1,iterate_right_columns(0)) + iterate_left_rows(row+1);
        };
        return iterate_left_rows(0);
    };
}

#endif