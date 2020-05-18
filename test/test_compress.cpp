
#include <itertools/compress.hpp>

#include <iostream>
#include <vector>

void test_compress(std::vector<int> &&ints, std::vector<bool> &&selectors)
{
    std::cout << "[";
    for (auto &e : itertools::compress(ints.begin(), ints.end(), selectors.begin(), selectors.end()))
    {
        std::cout << e << " ";
    }
    std::cout << "]" << std::endl;
}

int main()
{
    test_compress({}, {});
    test_compress({1, 2}, {});
    test_compress({}, {true, true});
    test_compress({1, 2, 3, 4}, {false, true, false, true});
    test_compress({1, 2, 3, 4}, {false, true, false});
    test_compress({1, 2, 3,}, {false, true, false, true});

    return 0;
}
