
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
 * @file count.hpp
 *
 * An infinite counter.
 */

#pragma once

#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename T, typename S>
    class count_iterator
    {
    public:
        count_iterator(T start, S step)
            : _M_start(start), _M_step(step)
        {
        }

        decltype(auto) operator*() const
        {
            return _M_start;
        }

        count_iterator &operator++()
        {
            _M_start += _M_step;
            return *this;
        }

        bool operator==(const count_iterator &other) const
        {
            return false;
        }

        bool operator!=(const count_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        T _M_start;
        S _M_step;
    };

    template <typename T, typename S>
    auto count(T start, S step)
    {
        using c_it_t = count_iterator<T, S>;
        return range_view<c_it_t>(c_it_t(start, step), c_it_t(start, step));
    }

} // namespace itertools
