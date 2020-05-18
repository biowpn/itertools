
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
 * @file groupby.hpp
 *
 * Make an iterator that returns consecutive keys and groups from the iterable.
 * 
 * groupby(["AAABBBBCCD"]) -> ("A", "AAA"), ("B", "BBBB"), ("C", "CC"), ("D", "D")
 * 
 * The key is a function computing a key value for each element. 
 * If not specified or is None, key defaults to an identity function and returns the element unchanged. 
 * Generally, the iterable needs to already be sorted on the same key function.
 * 
 * The operation of groupby() is similar to the uniq filter in Unix. It generates a break or new group 
 * every time the value of the key function changes (which is why it is usually necessary 
 * to have sorted the data using the same key function). 
 * That behavior differs from SQL’s GROUP BY which aggregates common elements regardless of their input order.
 *
 * The returned group is itself an iterator that shares the underlying iterable with groupby().
 * Because the source is shared, when the groupby() object is advanced, the previous group is no longer visible. 
 */

#pragma once

#include <itertools/range_view.hpp>

#include <tuple>
#include <type_traits>

namespace itertools
{
    template <typename Iterator, typename Fn>
    class groupby_iterator
    {
        // return type of Fn
        using key_t = typename std::remove_reference<typename std::invoke_result<Fn, decltype(*Iterator())>::type>::type;

    public:
        groupby_iterator(Iterator first, Iterator last, Fn key_fn)
            : _M_it(first), _M_it_last(last), _M_group_it_first(first), _M_key_fn(key_fn)
        {
            // compute initial key and group
            if (_M_it != _M_it_last)
            {
                _M_key = _M_key_fn(*_M_it);
                ++_M_it; // so don't repeat computing key on the same element (first)
                next_group();
            }
        }

        /// \brief Advance _M_it until _M_key_fn(*_M_it) yields a different key, or _M_it reaches last.
        void next_group()
        {
            for (; _M_it != _M_it_last && (_M_next_key = _M_key_fn(*_M_it)) == _M_key; ++_M_it)
                ;
        }

        decltype(auto) operator*() const
        {
            return std::make_tuple(_M_key, range_view(_M_group_it_first, _M_it));
        }

        groupby_iterator &operator++()
        {
            _M_group_it_first = _M_it;
            _M_key = _M_next_key;
            ++_M_it; // so don't repeat computing key on the same element
            next_group();
            return *this;
        }

        bool operator==(const groupby_iterator &other) const
        {
            return _M_group_it_first == other._M_group_it_first;
        }

        bool operator!=(const groupby_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it; ///< _M_group_it_last
        Iterator _M_it_last;
        Iterator _M_group_it_first;
        Fn _M_key_fn;
        key_t _M_key;
        key_t _M_next_key; ///< should always equal to _M_key_fn(*_M_it)
    };

    template <typename T>
    struct arg_returner
    {
        const T &operator()(const T &arg) const { return arg; }
    };

    template <typename Iterator, typename Fn>
    auto groupby(Iterator first, Iterator last, Fn fn)
    {
        using it_t = groupby_iterator<Iterator, Fn>;
        return range_view<it_t>(it_t(first, last, fn), it_t(last, last, fn));
    }

    template <typename Iterator>
    auto groupby(Iterator first, Iterator last)
    {
        using Fn = arg_returner<decltype(*first)>;
        return groupby(first, last, Fn());
    }

    template <typename Iterable, typename Fn>
    auto groupby(Iterable &&iterable, Fn fn)
    {
        return groupby(iterable.begin(), iterable.end(), fn);
    }

    template <typename Iterable>
    auto groupby(Iterable &&iterable)
    {
        return groupby(iterable.begin(), iterable.end());
    }

} // namespace itertools
