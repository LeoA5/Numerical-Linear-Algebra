#include"tensor_math.h"
#include<vector>
#include <iostream>

using namespace std;

int main()
{
    vector<int> v = {1, 2, 3};
    vector<int> w = {2, 5, 6};

    cout << "v dot w = " << dot_product(v)(w) << endl;

    vector<vector<int>> A = 
    {
        {1,2},
        {3,4},
        {5,6}
    };
    vector<vector<int>> B = 
    {
        {1,2,3},
        {4,5,6}
    };

    vector<vector<int>> AB = generate_nxn_identity(2);

    vector<int> A_one = get_matrix_column(A)(1);
    size_t A_size = A_one.size();

    for (size_t i = 0; i < AB.size(); ++i)
    {
        for (size_t j = 0; j < AB[0].size(); ++j)
        {
            cout << AB[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}