
#include <itertools/takewhile.hpp>

#include <iostream>
#include <vector>

void test_takewhile()
{
    std::vector<int> nums{1, 2, 3, 4, 5};
    for (auto n : itertools::takewhile([](int n) { return n < 3; }, nums))
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_takewhile();

    return 0;
}
