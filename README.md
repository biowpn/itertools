
# itertools

***itertools*** provides iterator building blocks for *fast* and *memory efficient* "iterator algebra" in C++ (17 or later).

***itertools*** is inspired by Python's [itertools](https://docs.python.org/3.7/library/itertools.html) module, each method of which has been recast in a form suitable for C++:

- [`accumulate`](#accumulate)
- [`chain`](#chain)
- [`combinations`](#combinations)
- [`combinations_with_replacement`](#combinations_with_replacement)
- [`compress`](#compress)
- [`count`](#count)
- [`cycle`](#cycle)
- [`dropwhile`](#dropwhile)
- [`filterfalse`](#filter-filterfalse)
- [`groupby`](#groupby)
- [`islice`](#islice)
- [`permutations`](#permutations)
- [`product`](#product)
- [`repeat`](#repeat)
- [`starmap`](#starmap)
- [`takewhile`](#takewhile)
- [`tee`](#tee)
- [`zip_longest`](#zip-zip_longest)

and the following Python built-in functions:

- [`filter`](#filter--filterfalse)
- [`zip`](#zip-zip_longest)

## Installation

***itertools*** is a header-only library, all the necessary files are in [include/itertools/](./include/itertools/).

The [itertools.hpp](./include/itertools/itertools.hpp) is the header file that includes all the others.

## Features

### 1. All Functions Work With `Iterable`

An `Iterable` is just an object with member functions `begin()` and `end()`, both of which return an iterator (to be specific, *ForwardIterator*; it needs only  `operator++()`, `operator*()`, and `operator!=()`). `Iterable` is analogous to Python's `iterable`. 

All ***itertools*** functions, where applicable, have overloads that accept one or more `Iterable`.

All ***itertools*** functions return new `Iterable` (view, no copying elements).

***itertools*** include a `range_view` class to wrap C arrays into an `Iterable`:

```
int a[4];
for (auto i in itertools::range_view(a, a + 4))
{
    //...
}
```

### 2. Most Functions Work with Iterators

Most ***itertools*** functions have overloads that accept iterators. For example:

```
std::vector<int> ints{1, 2, 3, 4};

itertools::cycle(ints);                     // works

itertools::cycle(ints.begin(), ints.end()); // also works
```

This is closer to the flavor of existing STL algorithms.

That some ***itertools*** functions lack such overloads is due to my incapability. Any help here is greatly appreciated! See the [Limitations](#limitations) section for the list of them.

### 3. Memory Efficient

***itertools*** operate iterators and **never** copy elements pointed to. The returned `Iterable` is merely a "view".

***itertools*** never allocate memory dynamically. Everything is done on a **lazy-evaluation** basis.

### 4. Fast

***itertools*** operate iterators. For most functions, all comparisions are done on iterators, **never** on the elements pointed to. This keeps dereferencing to a minimum.

## Usage

### `accumulate`

Returns accumulated sums or results of binary functions.

It differs from `std::accumulate` in that it provides intermediate results:

```
std::vector<int> numbers{1, 2, 3, 4};
for (auto s : itertools::accumulate(numbers, 0))
{ 
    std::cout << s << " ";
}
// will print:
// 1 3 6 10 
```


### `chain`

Returns elements from the first iterable until it is exhausted, then elements from the next iterable, until all of the iterables are exhausted.

```
std::vector<int> numbers_vec{1, 2, 3, 4};
std::list<int> numbers_list{5, 6, 7}
for (auto n : itertools::chain(numbers_vec, numbers_list))
{
    std::cout << s << " ";
}
// will print: 
// 1 2 3 4 5 6 7 
```

The requirement is that deferencing each iterable's `begin()` should yield the same type.


### `combinations`

Return successive fixed-length combinations of elements in the iterable.

```
std::vector<int> nums{1, 2, 3};
for (auto &&[a, b] : itertools::combinations<2>(nums))
{
    std::cout << a << " " << b << std::endl;
}
// will print:
// 1 2
// 1 3
// 2 3
```

Elements are treated as unique based on their position, not on their value.


### `combinations_with_replacement`

Return successive fixed-length combinations with replacement of elements in the iterable.

```
std::vector<int> nums{1, 2, 3};
for (auto &&[a, b] : itertools::combinations_with_replacement<2>(nums))
{
    std::cout << a << " " << b << std::endl;
}
// will print:
// 1 1
// 1 2
// 1 3
// 2 2
// 2 3
// 3 3
```


### `compress`

Filter an iterable using elements of another iterable.

```
std::vector<int> nums{1, 2, 3, 4};
std::vector<bool> selected{false, true, false, true};
for (auto n : itertools::compress(nums, selected))
{
    std::cout << n << " ";
}
// will print:
// 2 4 
```

Terminates when either iterable is exhausted.


### `count`

An infinite counter.

```
for (auto n : itertools::count(1, 2))
{
    std::cout << n << " ";
}
// will print 1 3 5 and so on, forever
```


### `cycle`

Cycle through an iterable, forever.

```
std::vector<int> nums{1, 2, 3};
for (auto n : itertools::cycle(nums))
{
    std::cout << n << " ";
}
// will print 1 2 3 1 2 3 1 2 3 and so on, forever
```


### `dropwhile`

Drop items from the iterable while predicate(item) is true.

```
std::vector<int> nums{0, 0, 0, 1, 2, 3};
for (auto n : itertools::dropwhile([](int n){ return n == 0; }, nums))
{
    std::cout << n << " ";
}
// will print:
// 1 2 3 
```


### `filter` , `filterfalse`

Return items for which function(item) is true (false for `filterfalse`).

If function is None, return the items that are true (false for `filterfalse`).

```
std::vector<int> nums{1, 0, -1, 0, 1};

for (auto n : itertools::filter(nums))
{
    std::cout << n << " ";
}
// will print:
// 1 -1 1

for (auto n : itertools::filterfalse(nums))
{
    std::cout << n << " ";
}
// will print:
// 0 0
```


### `groupby`

Returns consecutive (key, group) pairs from the iterable.

```
std::vector<int> nums{1, 2, 2, 3, 3, 3};
for (auto [k, g] : itertools::groupby(nums))
{
    std::cout << k << " : [";
    for (auto n : g)
    {
        std::cout << n << " ";
    }
    std::cout << "]" << std::endl;
}
// will print:
// 1 : [1 ]
// 2 : [2 2 ]
// 3 : [3 3 3 ]
```

Optional argument is a function to calculate key.


### `islice`

Slice an iterable by starting offset, stopping offset, and step.

```
std::string str{"ABCDEFG"};
for (auto c : itertools::islice(str, 1, 7, 2))
{
    std::cout << c << " ";
}
// will print:
// B D F
```

Limitations: only non-negative offsets and and positive steps are allowed.

But, in theory, they can always be converted to the above case:

- Get the length of the iterable, `N`;

- For negative offsets, take modulo of `N` to make them non-negative;

- For `step < 0`, convert calls like
    ```
    islice(x.begin(), x.end(), start, stop, step)
    ```
  to
    ```
    islice(x.rbegin(), x.rend(), N - 1 - start, N - 1 - stop, -step)
    ```
- `step = 0` causes infinite loop and it should be banned, which is the case in Python. 


### `permutations`

Return successive fixed-length permutations of elements in the iterable.

```
std::vector<int> nums{1, 2, 3};
for (auto &&[a, b] : itertools::permutations<2>(nums))
{
    std::cout << a << " " << b << std::endl;
}
// will print:
// 1 2
// 1 3
// 2 1
// 2 3
// 3 1
// 3 2
```

Elements are treated as unique based on their position, not on their value.


### `product`

Cartesian product of input iterables. Equivalent to nested for-loops.

```
std::vector<int> X = {1, 2, 3};
std::vector<char> Y = {'A', 'B'};
for (auto [x, y] : itertools::product(X, Y))
{
    cout << x << " " << y << endl;
}
// will print:
// 1 A
// 1 B
// 2 A
// 2 B
// 3 A
// 3 B
```


### `repeat`

Returns object over and over again, or for a limited number of times.

```
for (auto&& message : itertools::repeat("Hello there"))
{
    std::cout << message << std::endl;
}
// will print "Hello there" forever
```


### `starmap`

Computes the function using arguments obtained from the iterable as tuples.

```
std::vector<std::tuple<int, int>> args{{2, 5}, {3, 2}, {10, 3}};
for (auto res : itertools::starmap(my_pow /* pow(a, b) */, args))
{
    std::cout << res << " ";
}
// will print: 32 9 1000 
```


### `takewhile`

Opposite of `dropwhile`: take items from the iterable while predicate(item) is true.

```
std::vector<int> nums{0, 0, 0, 1, 2, 3};
for (auto n : itertools::takewhile([](int n){ return n == 0; }, nums))
{
    std::cout << n << " ";
}
// will print:
// 0 0 0
```

### `tee`

Clone iterable.

```
std::vector<int> nums{1, 2, 3};

auto [nums1, nums2] = itertools::tee<2>(nums);

std::equal(nums1.begin(), nums1.end(), nums.begin()); // true
std::equal(nums2.begin(), nums2.end(), nums.begin()); // true
```

This is trivial in C++ since you can call `begin()` as many times as you like, but actually quite challenging in Python! In fact, in a discussion with my friend Romic, we found out that, of all itertools functions, `tee` is the easiest to implement in C++, but the hardest in Python.

I include it for the sake of completeness.


### `zip`, `zip_longest`

Combine multiple iterables by glueing their iterators, so that they advance together.

For `zip`, it terminates when one of the iterables is exhausted. 

For `zip_longest`, it terminates when all iterables are exhausted. Those that terminate earlier will be filled-in with default value of their respective value type.

```
std::vector<int> ints{1, 2, 3};
std::string letters{"ABCD"};

for (auto [n, c] : itertools::zip(ints, letters))
{
    std::cout << n << " " << c << std::endl;
}
// will print:
// 1 A
// 2 B
// 3 C

for (auto [n, c] : itertools::zip_longest(ints, letters))
{
    std::cout << n << " " << c << std::endl;
}
// will print:
// 1 A
// 2 B
// 3 C
// 0 D
```


## Limitations

- These functions do not have overloads that accept iterators:

  - `chain`
  - `combinations`
  - `combinations_with_replacement`
  - `permutations`
  - `product`
  - `zip`
  - `zip_longest`

- `islice` accepts only non-negative offsets and positive steps.

- `zip_longest` cannot specify `fillvalue`, unlike Python's counterpart. The `fillvalue` argument in Python applies to any iterable. In C++ you can't do it if the input iterables' elements can't be converted to one another. To be really generic, it needs `fillvalue` for each iterable. In the end I didn't implement such feature because it is out of my ability.
