
# itertools

Iterator building blocks for *fast* and *memory efficient* "iterator algebra". Requires C++17.

Inspired by Python's [itertools](https://docs.python.org/3.7/library/itertools.html) module, each method of which has been recast in a form suitable for C++:

- `accumulate`
- `chain`
- `combinations`
- `combinations_with_replacement`
- `compress`
- `count`
- `cycle`
- `dropwhile`
- `filterfalse`
- `groupby`
- `islice`
- `permutations`
- `product`
- `repeat`
- `starmap`
- `takewhile`
- `tee`
- `zip_longest`

As well as the following Python built-in functions:

- `filter`
- `zip`

Note that some flexibility has been sacrificed since Python is a real dynamic programming language while C++ is not. For example:

```
itertools.product(*iterables, repeat=1)
```

can decide the length of `iterables` at run-time, while this library's counterpart `itertools::product()` must decide it at compile-time. This is due to the nature of C++'s variadic function.

Some other sacrifices are due to choices of design. For example, the combinatoric itertools like `itertools::combinations()` must fix its subsequences' length `r` at compile-time:

```
for (auto&& [a1, a2] : itertools::combinations<2>(ints))
```

## Example

*to be added*
