
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
 * @file tee.hpp
 *
 * Return n independent iterators from a single iterable.
 */

#pragma once

#include <itertools/range_view.hpp>

#include <tuple>

namespace itertools
{
    template <unsigned N, typename T>
    struct duplicator;

    template <typename T>
    struct duplicator<0, T>
    {
        decltype(auto) get(T &&arg) const
        {
            return std::tuple<>();
        }
    };

    template <unsigned N, typename T>
    struct duplicator
    {
        decltype(auto) get(T &&arg) const
        {
            return std::tuple_cat(std::make_tuple(arg), duplicator<N - 1, T>().get(arg));
        }
    };

    template <unsigned N, typename Iterator>
    auto tee(Iterator first, Iterator last)
    {
        return duplicator<N, Iterator>().get(range_view<Iterator>(first, last));
    }

    template <unsigned N, typename Iterable>
    auto tee(Iterable &&iterable)
    {
        return duplicator<N, Iterable>().get(iterable);
    }

} // namespace itertools
