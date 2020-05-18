
#include <itertools/chain.hpp>
#include <itertools/range_view.hpp>

#include <iostream>
#include <vector>
#include <list>

using namespace std;

void test_chain_iterator()
{
    vector<int> ints_vec{1, 2, 3, 4};
    list<int> ints_list{5, 6, 7};

    auto first = itertools::chain_iterator<int, decltype(ints_vec.begin()), decltype(ints_list.begin())>(ints_vec.begin(), ints_vec.end(), ints_list.begin(), ints_list.end());
    auto last = itertools::chain_iterator<int, decltype(ints_vec.begin()), decltype(ints_list.begin())>(ints_vec.end(), ints_vec.end(), ints_list.end(), ints_list.end());

    for (auto i : itertools::range_view(first, last))
    {
        std::cout << i << std::endl;
    }
}

void test_chain()
{
    vector<int> ints_vec{1, 2, 3, 4};
    list<int> ints_list{5, 6, 7};

    for (auto i : itertools::chain(ints_vec, ints_list))
    {
        std::cout << i << std::endl;
    }
}

int main()
{
    test_chain_iterator();

    test_chain();

    return 0;
}
