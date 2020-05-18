
#include <itertools/dropwhile.hpp>

#include <iostream>
#include <vector>

void test_dropwhile()
{
    std::vector<int> nums{1, 2, 3, 4, 5};
    for (auto n : itertools::dropwhile([](int n) { return n < 3; }, nums))
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_dropwhile();

    return 0;
}
