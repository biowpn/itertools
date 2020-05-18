
#include <itertools/islice.hpp>

#include <iostream>
#include <list>
#include <string>

template <typename Items>
void test_islice(Items &&items, int start, int stop, int step)
{
    for (auto c : itertools::islice(items, start, stop, step))
    {
        std::cout << c;
    }
    std::cout << std::endl;
}

int main()
{
    test_islice(std::list<char>{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'}, 1, 16, 2);

    test_islice(std::string{"ABCDEFG"}, 0, 7, 1);  // "ABCDEFG"
    test_islice(std::string{"ABCDEFG"}, 0, 7, 2);  // "ACEG"
    test_islice(std::string{"ABCDEFG"}, 0, 7, 3);  // "ADG"
    test_islice(std::string{"ABCDEFG"}, 0, 7, 4);  // "AE"
    test_islice(std::string{"ABCDEFG"}, 0, 7, 7);  // "A"
    test_islice(std::string{"ABCDEFG"}, 7, 14, 1); // ""
    test_islice(std::string{""}, 0, 7, 1);         // ""

    return 0;
}
