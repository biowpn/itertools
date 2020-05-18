
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
 * @file islice.hpp
 *
 * Return an iterator whose next() method returns selected values from an iterable.
 * 
 * If start is specified, will skip all preceding elements; otherwise, start defaults to zero.
 * 
 * step defaults to one. If specified as another value, step determines how many values are
 * skipped between successive calls.
 */

#pragma once

#include <itertools/range_view.hpp>

#include <stdexcept>

namespace itertools
{
    template <typename Iterator, typename Index, typename Step>
    class islice_iterator
    {
    public:
        islice_iterator(Iterator first, Iterator last, Index idx, Index stop, Step step)
            : _M_it(first), _M_it_last(last), _M_idx(idx), _M_idx_stop(stop), _M_idx_step(step)
        {
        }

        decltype(auto) operator*() const
        {
            return *_M_it;
        }

        islice_iterator &operator++()
        {
            for (Step step = 0; step != _M_idx_step; ++step)
            {
                if (_M_it == _M_it_last)
                {
                    break;
                }
                if (_M_idx == _M_idx_stop)
                {
                    break;
                }
                ++_M_it;
                ++_M_idx;
            }
            return *this;
        }

        bool operator==(const islice_iterator &other) const
        {
            return _M_it == other._M_it;
        }

        bool operator!=(const islice_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Iterator _M_it;
        Iterator _M_it_last;
        Index _M_idx;
        Index _M_idx_stop;
        Step _M_idx_step;
    };

    template <typename Iterator, typename Index, typename Step>
    auto islice(Iterator first, Iterator last, Index start, Index stop, Step step)
    {
        using it_t = islice_iterator<Iterator, Index, Step>;
        it_t it_last(last, last, start, stop, step);
        if (0 < step)
        {
            if (start < stop)
            {
                for (Index i = 0; i < start && first != last; ++i, ++first)
                    ;
                return range_view<it_t>(it_t(first, last, start, stop, step), it_last);
            }
            else
            {
                // empty range
                return range_view<it_t>(it_last, it_last);
            }
        }
        else
        {
            // negative step not supported yet
            throw std::runtime_error("islice() step is non-positive");
        }
    }

    template <typename Iterable, typename Index, typename Step>
    auto islice(Iterable &&iterable, Index start, Index stop, Step step)
    {
        return islice(iterable.begin(), iterable.end(), start, stop, step);
    }

} // namespace itertools
