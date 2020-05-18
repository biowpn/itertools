
/** 
 *  itertools : Iterator building blocks for fast and memory efficient "iterator algebra".
 *
 *  Copyright (C) 2020 Hank Meng (ymenghank@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file zip_longest.hpp
 *
 * Make an iterator that aggregates elements from each of the iterables.
 * If the iterables are of uneven length, missing values are filled-in with default value.
 * Iteration continues until the longest iterable is exhausted.
 */

#pragma once

#include <tuple>
#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename... Iterator>
    class zip_longest_iterator;

    template <typename Iterator>
    class zip_longest_iterator<Iterator>
    {
        using value_type = typename std::remove_reference<decltype(*Iterator())>::type;

    public:
        zip_longest_iterator(Iterator first, Iterator last)
            : _M_it(first), _M_it_last(last)
        {
        }

        decltype(auto) operator*() const
        {
            return _M_it != _M_it_last ? std::make_tuple(*_M_it) : value_type();
        }

        zip_longest_iterator &operator++()
        {
            if (_M_it != _M_it_last)
            {
                ++_M_it;
            }
            return *this;
        }

        bool operator==(const zip_longest_iterator &other) const
        {
            return _M_it == other._M_it;
        }

        bool operator!=(const zip_longest_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
        Iterator _M_it_last;
    };

    template <typename Iterator, typename... Iterators>
    class zip_longest_iterator<Iterator, Iterators...>
    {
        using value_type = typename std::remove_reference<decltype(*Iterator())>::type;

    public:
        template <typename... Args>
        zip_longest_iterator(Iterator first, Iterator last, Args... rest)
            : _M_it(first), _M_it_last(last), _M_sub_it(rest...)
        {
        }

        decltype(auto) operator*() const
        {
            return std::tuple_cat(_M_it != _M_it_last ? std::make_tuple(*_M_it) : value_type(), *_M_sub_it);
        }

        zip_longest_iterator &operator++()
        {
            if (_M_it != _M_it_last)
            {
                ++_M_it;
            }
            ++_M_sub_it;
            return *this;
        }

        bool operator==(const zip_longest_iterator &other) const
        {
            return _M_it == other._M_it && _M_sub_it == other._M_sub_it;
        }

        bool operator!=(const zip_longest_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
        Iterator _M_it_last;
        zip_longest_iterator<Iterators...> _M_sub_it;
    };

    template <typename... Iterables>
    auto zip_longest(Iterables &&... iterables)
    {
        using it_t = zip_longest_iterator<decltype(iterables.begin())...>;
        auto it_first = std::apply(
            [&iterables...](auto &&... args) {
                return it_t(std::forward<decltype(args)>(args)...);
            },
            std::tuple_cat(std::make_tuple(iterables.begin(), iterables.end())...));
        auto it_last = std::apply(
            [&iterables...](auto &&... args) {
                return it_t(std::forward<decltype(args)>(args)...);
            },
            std::tuple_cat(std::make_tuple(iterables.end(), iterables.end())...));
        return range_view<it_t>(it_first, it_last);
    }

} // namespace itertools
