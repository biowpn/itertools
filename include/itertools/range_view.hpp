
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
 * @file range_view.hpp
 *
 * Wrap iterators [first, last) into an object that has begin() and end().
 */

#pragma once

namespace itertools
{
    template <typename Iterator>
    class range_view
    {
    public:
        range_view(Iterator first, Iterator last) : _M_first(first), _M_last(last) {}

        Iterator begin() const { return _M_first; }

        Iterator end() const { return _M_last; }

    private:
        Iterator _M_first;
        Iterator _M_last;
    };

} // namespace itertools
