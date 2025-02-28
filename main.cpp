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
    cout << "Matrix I_2: " << endl;
    const matrix<int> I_2 = generate_nxn_identity(2);
    display_matrix(I_2);
    return 0;
}