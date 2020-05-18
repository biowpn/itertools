
#include <itertools/zip_longest.hpp>

#include <iostream>
#include <vector>
#include <list>
#include <string>

void test_zip_longest()
{
    std::vector<int> ints{1, 2, 3, 4, 5};
    std::list<double> doubles{0.1, 0.2, 0.3};
    std::string letters{"ABCDEFG"};
    for (auto [x, y, z] : itertools::zip_longest(ints, doubles, letters))
    {
        std::cout << x << " " << y << " " << z << std::endl;
    }
}

int main()
{
    test_zip_longest();

    return 0;
}
