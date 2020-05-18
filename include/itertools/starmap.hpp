
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
 * @file starmap.hpp
 *
 * Make an iterator that computes the function using arguments obtained from the iterable.
 */

#pragma once

#include <itertools/range_view.hpp>

#include <tuple>
#include <utility>

namespace itertools
{
    template <typename Fn, typename Iterator>
    class starmap_iterator
    {
    public:
        starmap_iterator(Fn fn, Iterator it)
            : _M_fn(fn), _M_it(it)
        {
        }

        decltype(auto) operator*() const
        {
            return std::apply(_M_fn, *_M_it);
        }

        starmap_iterator &operator++()
        {
            ++_M_it;
            return *this;
        }

        bool operator==(const starmap_iterator &other) const
        {
            return _M_it == other._M_it;
        }

        bool operator!=(const starmap_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Fn _M_fn;
        Iterator _M_it;
    };

    template <typename Fn, typename Iterator>
    auto starmap(Fn fn, Iterator first, Iterator last)
    {
        using it_t = starmap_iterator<Fn, Iterator>;
        return range_view<it_t>(it_t(fn, first), it_t(fn, last));
    }

    template <typename Fn, typename Iterable>
    auto starmap(Fn fn, Iterable &&iterable)
    {
        return starmap(fn, iterable.begin(), iterable.end());
    }

} // namespace itertools
