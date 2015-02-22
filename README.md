# bloomfilter

A simple bloom filter in C.

A bloom filter is a kind of probabilistic set. You can add elements to it, and query it for existence of elements. But if you add to many elements, the probability for an error becomes increasingly large. This can be countered by creating a larger bloom filter. The size of the filter is specified in terms of the number of bits in a bitfield. It is also possible to specify how many hash functions should be used. For a description of how it all works, see http://en.wikipedia.org/wiki/Bloom_filter.

Found some really old code lying around and thought I could just as well save it to Github if I or anyone else would ever need it. Run make, then execute test and it will all be clear.

Compiled and tested on FreeBSD 9.
