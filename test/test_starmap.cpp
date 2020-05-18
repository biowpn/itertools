
#include <itertools/starmap.hpp>

#include <iostream>
#include <vector>

int my_pow(int x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    int h = my_pow(x, n / 2);
    return h * h * (n % 2 ? x : 1);
}

void test_starmap()
{
    std::vector<std::tuple<int, int>> args{{2, 5}, {3, 2}, {10, 3}};
    for (auto res : itertools::starmap(my_pow, args))
    {
        std::cout << res << " ";
    }
    std::cout << std::endl;
}

int main()
{
    test_starmap();

    return 0;
}
