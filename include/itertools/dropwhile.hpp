
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
 * @file dropwhile.hpp
 *
 * Drop items from the iterable while predicate(item) is true.
 * Afterwards, return every element until the iterable is exhausted.
 */

#pragma once

#include <itertools/range_view.hpp>

namespace itertools
{
    template <typename Iterator>
    using dropwhile_iterator = Iterator; /// dummy

    template <typename Fn, typename Iterator>
    auto dropwhile(Fn predicate, Iterator first, Iterator last)
    {
        for (; first != last && predicate(*first); ++first)
            ;
        return range_view<Iterator>(first, last);
    }

    template <typename Fn, typename Iterable>
    auto dropwhile(Fn predicate, Iterable &&iterable)
    {
        return dropwhile(predicate, iterable.begin(), iterable.end());
    }

} // namespace itertools
