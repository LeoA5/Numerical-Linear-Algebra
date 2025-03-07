#include "matrix.h"
#include <iostream>

using namespace std;

template<typename T>
void display_matrix(const matrix<T>& A)
{
    for (size_t row = 0; row < A.shape[0]; ++row)
    {
        for (size_t col = 0; col < A.shape[1]; ++col)
        {
            cout << A.elements[row][col] << " ";
        }
        cout << endl;
    }
}

template<typename T>
void display_vector(const vector<T>& v)
{
    for (size_t i = 0; i < v.size(); ++i)
    {
        cout << v[i] << " ";
    }
    cout << endl;
}

int main()
{
    const matrix<int> A = {{2,3}, {{1,2,3}, {4,5,6}}};
    const matrix<int> B = {{3,2}, {{1,2}, {3,4}, {5,6}}};
    const matrix<int> AB = matrix_multiply(A)(B);
    cout << "Matrix A: " << endl;
    display_matrix(A);
    cout << "Matrix B: " << endl;
    display_matrix(B);
    cout << "Matrix AB: " << endl;
    display_matrix(AB);
    const matrix<int> AB_2 = scalar_multiply(AB)(2);
    cout << "2AB: " << endl;
    display_matrix(AB_2);
    cout << "Matrix I_2: " << endl;
    const matrix<int> I_2 = generate_nxn_identity(2);
    display_matrix(I_2);
    const matrix<int> E_1 = replace_row(I_2)({2, 0})(0);
    cout << "Matrix E_1: " << endl;
    display_matrix(E_1);
    const matrix<int> E_2 = add_scaled_row(I_2)(2)(1)(0);
    cout << "Matrix E_2: " << endl;
    display_matrix(E_2);
    vector<int> v = {1, 2, 3};
    cout << "Vector v: " << endl;
    display_vector(v);
    vector<int> v_2 = scale(v)(2);
    cout << "2v: " << endl;
    display_vector(v_2);
    vector<int> v_3 = add(v)(v_2);
    cout <<"v + 2v = " << endl;
    display_vector(v_3);
    return 0;
}