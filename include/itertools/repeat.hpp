
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
 * @file repeat.hpp
 *
 * Make an iterator that returns object over and over again.
 * Runs indefinitely unless the times argument is specified.
 */

#pragma once

#include <itertools/range_view.hpp>

#include <utility>

namespace itertools
{
    template <typename Value>
    class repeat_inf_iterator
    {
    public:
        repeat_inf_iterator(Value &&value)
            : _M_value(std::forward<Value>(value))
        {
        }

        Value &operator*() const
        {
            return _M_value;
        }

        repeat_inf_iterator &operator++()
        {
            return *this;
        }

        bool operator==(const repeat_inf_iterator &other) const
        {
            return false;
        }

        bool operator!=(const repeat_inf_iterator &other) const
        {
            return true;
        }

    private:
        Value _M_value;
    };

    template <typename Value, typename N>
    class repeat_iterator
    {
    public:
        repeat_iterator(Value &&value, N times)
            : _M_value(std::forward<Value>(value)), _M_times(times)
        {
        }

        Value &operator*() const
        {
            return _M_value;
        }

        repeat_iterator &operator++()
        {
            ++_M_times;
            return *this;
        }

        bool operator==(const repeat_iterator &other) const
        {
            return _M_times == other._M_times;
        }

        bool operator!=(const repeat_iterator &other) const
        {
            return !(*this == other);
        }

    private:
        Value _M_value;
        N _M_times;
    };

    template <typename Value>
    auto repeat(Value &&value)
    {
        using it_t = repeat_inf_iterator<Value>;
        it_t it_first(std::forward<Value>(value));
        it_t it_last(std::forward<Value>(value));
        return range_view<it_t>(it_first, it_last);
    }

    template <typename Value, typename N>
    auto repeat(Value &&value, N times)
    {
        using it_t = repeat_iterator<Value, N>;
        it_t it_first(std::forward<Value>(value), 0);
        it_t it_last(std::forward<Value>(value), times);
        return range_view<it_t>(it_first, it_last);
    }

} // namespace itertools
