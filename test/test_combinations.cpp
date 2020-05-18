
#include <itertools/combinations.hpp>
#include <itertools/range_view.hpp>

#include <iostream>
#include <vector>
#include <string>

void test_combinations_iterator()
{
    std::cout << __FUNCTION__ << std::endl;

    std::vector nums{1, 2, 3, 4, 5};

    std::cout << "5 choose 3: " << std::endl;

    itertools::combinations_iterator<3, decltype(nums.begin())> first(nums.begin(), nums.begin() + 3);
    itertools::combinations_iterator<3, decltype(nums.begin())> last(nums.begin() + 3, nums.begin() + 3);
    for (auto &&[a, b, c] : itertools::range_view(first, last))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }
}

void test_combinations()
{
    std::cout << __FUNCTION__ << std::endl;

    std::vector nums{1, 2, 3, 4, 5};

    std::cout << "5 choose 1: " << std::endl;
    for (auto &&[a] : itertools::combinations<1>(nums.begin(), nums.end()))
    {
        std::cout << a << std::endl;
    }

    std::cout << "5 choose 3: " << std::endl;
    for (auto &&[a, b, c] : itertools::combinations<3>(nums.begin(), nums.end()))
    {
        std::cout << a << " " << b << " " << c << std::endl;
    }

    std::cout << "5 choose 5: " << std::endl;
    for (auto &&[a, b, c, d, e] : itertools::combinations<5>(nums.begin(), nums.end()))
    {
        std::cout << a << " " << b << " " << c << " " << d << " " << e << std::endl;
    }

    std::cout << "5 choose 6: " << std::endl;
    for (auto &&[a, b, c, d, e, f] : itertools::combinations<6>(nums.begin(), nums.end()))
    {
        // shouldn't enter at all
        std::cout << a << " " << b << " " << c << " " << d << " " << e << " " << f << std::endl;
    }
}

int main()
{
    test_combinations_iterator();

    test_combinations();

    return 0;
}
