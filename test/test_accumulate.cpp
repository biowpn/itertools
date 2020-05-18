
#include <itertools/accumulate.hpp>

#include <vector>
#include <iostream>

void test_accumulate(std::vector<int> &&nums)
{
    std::cout << "[";
    for (auto &&s : itertools::accumulate(nums.begin(), nums.end(), 0))
    {
        std::cout << s << " ";
    }
    std::cout << "]" << std::endl;
}

int main()
{
    test_accumulate({1, 2, 3, 4, 5});
    test_accumulate({});
    test_accumulate({1});

    return 0;
}
