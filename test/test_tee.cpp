
#include <itertools/tee.hpp>

#include <algorithm>
#include <stdexcept>
#include <vector>

void test_tee()
{
    std::vector<int> nums{1, 2, 3, 4, 5};
    auto [X, Y] = itertools::tee<2>(nums);
    if (!std::equal(X.begin(), X.end(), Y.begin(), Y.end()))
    {
        throw std::runtime_error("not equal");
    }
}

int main()
{
    test_tee();

    return 0;
}
