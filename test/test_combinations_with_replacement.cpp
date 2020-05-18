
#include <itertools/combinations_with_replacement.hpp>

#include <iostream>
#include <vector>

void test_combinations_with_replacement()
{
    std::cout << __FUNCTION__ << std::endl;

    std::vector nums{1, 2, 3, 4, 5};

    std::cout << "5 choose 1: " << std::endl;
    for (auto &&[a] : itertools::combinations_with_replacement<1>(nums.begin(), nums.end()))
    {
        std::cout << a << std::endl;
    }

    std::cout << "5 choose 3: " << std::endl;
    for (auto &&[a, b, c] : itertools::combinations_with_replacement<3>(nums.begin(), nums.end()))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }

    std::cout << "5 choose 5: " << std::endl;
    for (auto &&[a, b, c, d, e] : itertools::combinations_with_replacement<5>(nums.begin(), nums.end()))
    {
        std::cout << a << " " << b << " " << c << " " << d << " " << e << std::endl;
    }

    std::cout << "5 choose 6: " << std::endl;
    for (auto &&[a, b, c, d, e, f] : itertools::combinations_with_replacement<6>(nums.begin(), nums.end()))
    {
        // shouldn't enter at all
        std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << std::endl;
    }
}

int main()
{
    test_combinations_with_replacement();

    return 0;
}
