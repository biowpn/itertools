
#include <itertools/permutations.hpp>

#include <iostream>
#include <vector>

void test_permutations()
{
    std::cout << __FUNCTION__ << std::endl;

    std::vector nums{1, 2, 3, 4, 5};

    std::cout << "5 arrange 1: " << std::endl;
    for (auto &&[a] : itertools::permutations<1>(nums))
    {
        std::cout << a << std::endl;
    }

    std::cout << "5 arrange 3: " << std::endl;
    for (auto &&[a, b, c] : itertools::permutations<3>(nums))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }
}

int main()
{
    test_permutations();

    return 0;
}
