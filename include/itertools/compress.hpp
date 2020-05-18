
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
 * @file compress.hpp
 *
 * Make an iterator that filters elements from data returning only those that have a 
 * corresponding element in selectors that evaluates to True. 
 * Stops when either the data or selectors iterables has been exhausted.
 */

#pragma once

#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename DIterator, typename SIterator>
    class compress_iterator
    {
    public:
        compress_iterator(DIterator d_it, DIterator d_it_last, SIterator s_it, SIterator s_it_last)
            : _M_d_it(d_it), _M_d_it_last(d_it_last), _M_s_it(s_it), _M_s_it_last(s_it_last)
        {
            next_selected();
        }

        void next_selected()
        {
            for (; _M_s_it != _M_s_it_last && _M_d_it != _M_d_it_last && !(*_M_s_it); ++_M_s_it, ++_M_d_it)
                ;
        }

        decltype(auto) operator*() const
        {
            return *_M_d_it;
        }

        compress_iterator &operator++()
        {
            ++_M_d_it;
            ++_M_s_it;
            next_selected();
            return *this;
        }

        bool operator==(const compress_iterator &other) const
        {
            return _M_d_it == other._M_d_it || _M_s_it == other._M_s_it;
        }

        bool operator!=(const compress_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        DIterator _M_d_it;
        DIterator _M_d_it_last;
        SIterator _M_s_it;
        SIterator _M_s_it_last;
    };

    template <typename DIterator, typename SIterator>
    auto compress(DIterator data_first, DIterator data_last,
                  SIterator selector_first, SIterator selector_last)
    {
        using it_t = compress_iterator<DIterator, SIterator>;
        it_t it_first(data_first, data_last, selector_first, selector_last);
        it_t it_last(data_last, data_last, selector_last, selector_last);
        return range_view<it_t>(it_first, it_last);
    }

    template <typename DIterable, typename SIterable>
    auto compress(DIterable &&data, SIterable &&selectors)
    {
        return compress(data.begin(), data.end(), selectors.begin(), selectors.end());
    }

} // namespace itertools
