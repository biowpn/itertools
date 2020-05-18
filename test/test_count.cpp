
#include <itertools/count.hpp>

#include <iostream>
#include <vector>

void test_count()
{
    auto counter = itertools::count_iterator(1, 2);
    for (int i = 0; i < 5; ++i, ++counter)
    {
        std::cout << *counter << std::endl;
    }
}

int main()
{
    test_count();

    return 0;
}
