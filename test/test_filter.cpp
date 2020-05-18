
#include <itertools/filter.hpp>

#include <iostream>
#include <vector>

void test_filter()
{
    std::vector<int> nums{1, 0, -1, 0, 1};
    for (auto n : itertools::filter(nums))
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_filter();

    return 0;
}
