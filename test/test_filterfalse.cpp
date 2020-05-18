
#include <itertools/filterfalse.hpp>

#include <iostream>
#include <vector>

void test_filterfalse()
{
    std::vector<int> nums{1, 0, -1, 0, 1};
    for (auto n : itertools::filterfalse(nums))
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_filterfalse();

    return 0;
}
    