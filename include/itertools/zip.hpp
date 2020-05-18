
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
 * @file zip.hpp
 *
 * Return a zip object whose .__next__() method returns a tuple where
 * the i-th element comes from the i-th iterable argument.
 * 
 * The .__next__() method continues until the shortest iterable in the argument sequence
 * is exhausted and then it raises StopIteration.
 */

#pragma once

#include <tuple>
#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename... Iterator>
    class zip_iterator;

    template <typename Iterator>
    class zip_iterator<Iterator>
    {
    public:
        zip_iterator(Iterator first)
            : _M_it(first)
        {
        }

        decltype(auto) operator*() const
        {
            return std::make_tuple(*_M_it);
        }

        zip_iterator &operator++()
        {
            ++_M_it;
            return *this;
        }

        bool operator==(const zip_iterator &other) const
        {
            return _M_it == other._M_it;
        }

        bool operator!=(const zip_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
    };

    template <typename Iterator, typename... Iterators>
    class zip_iterator<Iterator, Iterators...>
    {
    public:
        zip_iterator(Iterator first, Iterators... rest)
            : _M_it(first), _M_sub_it(rest...)
        {
        }

        decltype(auto) operator*() const
        {
            return std::tuple_cat(std::make_tuple(*_M_it), *_M_sub_it);
        }

        zip_iterator &operator++()
        {
            ++_M_it;
            ++_M_sub_it;
            return *this;
        }

        bool operator==(const zip_iterator &other) const
        {
            return _M_it == other._M_it || _M_sub_it == other._M_sub_it;
        }

        bool operator!=(const zip_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
        zip_iterator<Iterators...> _M_sub_it;
    };

    template <typename... Iterables>
    auto zip(Iterables &&... iterables)
    {
        using it_t = zip_iterator<decltype(iterables.begin())...>;
        return range_view<it_t>(it_t(iterables.begin()...), it_t(iterables.end()...));
    }

} // namespace itertools
