# optisearch

This is an implementation of the A\* Search Algorithm. Specifically to solve an
[8-puzzle](http://en.wikipedia.org/wiki/15_puzzle) - which is a variant on the
15-puzzle.

# Installation

The `CMakeLists.txt` file requires CMake version `>= 3.1`, but presumably you
could just drop that down to the *actual* minimum required version.

To download & build:

```bash
$ git clone http://github.com/crockeo/optisearch
$ cd optisearch
$ cmake .
$ make
```

That should create the following files:

```
# The main exectuable.
build/bin/optisearch

# The test suite.
build/bin/optisearch-test

# The common library between the two.
build/lib/optisearch-common.a
```

# Licensing

Check the `LICENSE` file in this directory.
