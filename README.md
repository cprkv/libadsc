Algorithms and data structures for C
====================================

C library for algorithms and data structures.  
For more information about API you can see:
 * tests (in the same folder as it sounds)
 * source code
 * *examples* (not ready)
 * API docs (in the `docs` folder)

## Dependencies
 * Criterion
```
sudo add-apt-repository ppa:snaipewastaken/ppa
sudo apt-get update
sudo apt-get install criterion-dev
```
 * GCC (as compiler)

## Build

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

Output binary files are located in `<repository-root>/bin`.

## Tests

To run tests you need to:
 * build solution
 * run `./bin/tests`

If some tests is failed, then libadsc is not ready to use in your project.

## Installation

**Attention:**  
Before install you should run tests. Otherwise, all the things happend is only on your own responsibility.

To install adsc you need to:
 * build solution
 * run `cd build && sudo make install`
```

## Docs

To generate documentation for ADSC you need to install `doxygen`.
In example, you can do it on ubuntu: `sudo apt-get install doxygen`.

To generate documentation execute shell comands:
 * `cd docs`
 * `doxygen config.conf`

Then, you can see documentation by opening file `docs/html/index.html` in your web browser.  
In most cases you will need to open tab **Modules**. All usefull information will be defined here in groups.

## P.S.
 * Just for fun - you could count lines of library code using:  
    `cloc tests source include --force-lang=C,h --include-lang=C`  
   Or do it without tests:  
    `cloc source include --force-lang=C,h --include-lang=C`