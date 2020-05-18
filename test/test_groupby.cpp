
#include <itertools/groupby.hpp>

#include <iostream>
#include <iterator>
#include <vector>

void test_groupby(std::vector<int> &&nums)
{
    std::cout << "groupby ([";
    std::copy(nums.begin(), nums.end(), std::ostream_iterator<int>(std::cout, ", "));
    std::cout << "]):" << std::endl;

    for (auto [k, g] : itertools::groupby(nums))
    {
        std::cout << k << " : [";
        std::copy(g.begin(), g.end(), std::ostream_iterator<int>(std::cout, ", "));
        std::cout << "]" << std::endl;
    }
}

int main()
{
    test_groupby({});
    test_groupby({1});
    test_groupby({3, 3, 3});
    test_groupby({1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5});
    test_groupby({1, 2, 2, 3, 3, 3, 2, 2, 1});

    return 0;
}
