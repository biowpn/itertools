
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
 * @file filterfalse.hpp
 *
 * Return those items of sequence for which function(item) is false.
 * If function is None, return the items that are false.
 */

#pragma once

#include <itertools/filter.hpp>

namespace itertools
{
    template <typename Fn, typename Iterator>
    auto filterfalse(Fn predicate, Iterator first, Iterator last)
    {
        using value_type = decltype(*first);
        auto reverse_predicate = [&predicate](const value_type &arg) { return predicate(arg) ? false : true; };
        using it_t = filter_iterator<decltype(reverse_predicate), Iterator>;
        return range_view<it_t>(it_t(reverse_predicate, first, last), it_t(reverse_predicate, last, last));
    }

    template <typename Fn, typename Iterable>
    auto filterfalse(Fn predicate, Iterable &&iterable)
    {
        return filterfalse(predicate, iterable.begin(), iterable.end());
    }

    template <typename Iterator>
    auto filterfalse(Iterator first, Iterator last)
    {
        return filterfalse(boolean_transformer<decltype(*first)>(), first, last);
    }

    template <typename Iterable>
    auto filterfalse(Iterable &&iterable)
    {
        return filterfalse(iterable.begin(), iterable.end());
    }
} // namespace itertools
