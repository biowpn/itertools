
#include <itertools/repeat.hpp>

#include <iostream>
#include <vector>

void test_repeat()
{
    auto repeater = itertools::repeat("Hello there").begin();
    for (auto& msg : itertools::repeat("Knock, knock", 5))
    {
        std::cout << msg << std::endl;
        std::cout << *(++repeater) << std::endl;
    }
}

int main()
{
    test_repeat();

    return 0;
}
