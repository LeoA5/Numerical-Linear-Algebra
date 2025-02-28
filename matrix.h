#ifndef MATRIX_H
#define MATRIX_H

#include "vector_operations.h"
#include <array>
#include <utility>

template<typename T>
struct matrix
{
    // [rows, columns]
    const std::array<size_t, 2> shape;
    const std::vector<std::vector<T>> elements;
};

template <typename T>
std::function<std::vector<T> (size_t)> get_matrix_row(const matrix<T>& A)
{
    return [&A] (size_t row) -> std::vector<T>
    {
        if (row >= A.shape[0])
        {
            throw std::invalid_argument(
                "Row index is larger than the number of rows."
            );
        }
        return A.elements[row];
    };
}

template <typename T>
std::function<std::vector<T> (size_t)> get_matrix_column(const matrix<T>& A)
{
    return [&A] (size_t column) -> std::vector<T>
    {
        std::function<std::vector<T> (size_t)> get_column_elements = 
        [&A, column, &get_column_elements] (size_t row) -> 
        std::vector<T>
        {
            if (row >= A.shape[0]) { return {}; }
            return std::vector<T>(1,A.elements[row][column]) + get_column_elements(row+1);
        };
        return get_column_elements(0);
    };
}

template <typename T>
std::function<const matrix<T> (const matrix<T>&)> 
matrix_multiply(const matrix<T>& left)
{
    if (!std::is_arithmetic_v<T>)
    {
        throw std::invalid_argument("Parameter is not an arithmetic type.");
    }
    return [&left] (const matrix<T>& right) -> const matrix<T>
    {
        if (left.shape[1] != right.shape[0])
        {
            throw std::invalid_argument("Matrices are not multipliable.");
        }
        std::function<const std::vector<std::vector<T>> (size_t)> 
        iterate_left_rows = [&left, &right, &iterate_left_rows] (size_t row) ->
        std::vector<std::vector<T>>
        {
            if (row == left.shape[0]) { return {}; }
            std::function<std::vector<T> (size_t)> iterate_right_columns = 
            [&left, &right, row, &iterate_right_columns] (size_t column) -> 
            std::vector<T>
            {
                if (column == right.shape[1]) { return {}; }
                return std::vector<T>(1,dot_product(
                    get_matrix_row(left)(row)
                )(
                    get_matrix_column(right)(column)
                )) + 
                iterate_right_columns(column + 1);
            };
            return std::vector<std::vector<T>>(1,iterate_right_columns(0)) +
            iterate_left_rows(row+1);
        };

        return {{left.shape[0], right.shape[1]}, iterate_left_rows(0)};
    };
}

const matrix<int> generate_nxn_identity(size_t n)
{
    std::function<std::vector<std::vector<int>> (size_t)> generate_rows =
    [n, &generate_rows] (size_t row) -> std::vector<std::vector<int>>
    {
        if (row == n) { return {}; }

        std::function<std::vector<int> (size_t)> generate_row =
        [n, row, &generate_row] (size_t i) -> std::vector<int>
        {
            if (i == n) { return {}; }
            return std::vector<int>(1, (i == row) ? 1 : 0) + 
            generate_row(i + 1);
        };
        return std::vector<std::vector<int>>(1, generate_row(0)) + 
        generate_rows(row + 1);
    };
    return {{n, n}, {generate_rows(0)}};
}



template <typename T>
std::vector<std::vector<T>> add_multiple_of_row()
{

}

template <typename T>
std::vector<std::vector<T>> get_row_echelon_form(
    const std::vector<std::vector<T>>& matrix
)
{

}
#endif