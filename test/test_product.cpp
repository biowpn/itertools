
#include <itertools/product.hpp>
#include <itertools/range_view.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void test_product_iterator()
{
    int X[3] = {1, 2, 3};
    char Y[2] = {'A', 'B'};
    double Z[2] = {0.5, 0.6};

    // construct from most inner
    itertools::product_iterator<double *> it_z_begin(begin(Z), end(Z));
    itertools::product_iterator<double *> it_z_end(end(Z), end(Z));

    itertools::product_iterator<char *, double *> it_yz_begin(begin(Y), end(Y), it_z_begin, it_z_begin, it_z_end);
    itertools::product_iterator<char *, double *> it_yz_end(end(Y), end(Y), it_z_end, it_z_begin, it_z_end);

    itertools::product_iterator<int *, char *, double *> it_xyz_begin(begin(X), end(X), it_yz_begin, it_yz_begin, it_yz_end);
    itertools::product_iterator<int *, char *, double *> it_xyz_end(end(X), end(X), it_yz_end, it_yz_begin, it_yz_end);

    for (auto [x, y, z] : itertools::range_view(it_xyz_begin, it_xyz_end))
    {
        cout << x << " " << y << " " << z << endl;
    }
}

void test_product()
{
    std::vector<int> X = {1, 2, 3};
    std::vector<char> Y = {'A', 'B'};
    std::vector<double> Z = {0.5, 100.0};

    for (auto [x, y, z] : itertools::product(X, Y, Z))
    {
        cout << x << " " << y << " " << z << endl;
    }
}

int main()
{
    test_product_iterator();

    test_product();

    return 0;
}
