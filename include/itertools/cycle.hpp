
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
 * @file cycle.hpp
 *
 * Return elements from the iterable until it is exhausted.
 * Then repeat the sequence indefinitely.
 */

#pragma once

#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename Iterator>
    class cycle_iterator
    {
    public:
        cycle_iterator(Iterator first, Iterator last)
            : _M_it(first), _M_first(first), _M_last(last)
        {
        }

        decltype(auto) operator*() const
        {
            return *_M_it;
        }

        cycle_iterator &operator++()
        {
            if (++_M_it == _M_last)
            {
                _M_it = _M_first;
            }
            return *this;
        }

        bool operator==(const cycle_iterator &other) const
        {
            return false;
        }

        bool operator!=(const cycle_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
        Iterator _M_first;
        Iterator _M_last;
    };

    template <typename Iterator>
    auto cycle(Iterator first, Iterator last)
    {
        using c_it_t = cycle_iterator<Iterator>;
        return range_view<c_it_t>(c_it_t(first, last), c_it_t(last, last));
    }

    template <typename Iterable>
    auto cycle(Iterable &&iterable)
    {
        return cycle(iterable.begin(), iterable.end());
    }

} // namespace itertools
