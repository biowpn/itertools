
#include <itertools/cycle.hpp>

#include <iostream>
#include <vector>

void test_cycle()
{
    std::vector<int> nums{1, 2, 3};
    auto cycler = itertools::cycle_iterator(nums.begin(), nums.end());
    for (int i = 0; i < 7; ++i, ++cycler)
    {
        std::cout << *cycler << " ";
    }
    std::cout << std::endl;
}

int main()
{
    return 0;
}
