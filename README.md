Algorithms and data structures for C
====================================

C library for algorithms and data structures.  
For more information about API you can see:
 * tests (in the same folder as it sounds)
 * source code
 * *examples* (not ready)
 * API docs (in the `docs` folder)

## Tests

To run tests you need to execute shell comands:
 * `cd tests/build`
 * `cmake ..`
 * `make`
 * `../bin/tests`

If some tests is failed, then libadsc is not ready to use in your project.

## Installation

**Attention:**  
Before install you should run tests. Otherwise, all the things happend is only on your own responsibility.

To install adsc you need to execute shell comands:
 * `cd build`
 * `cmake .. -DCMAKE_BUILD_TYPE=Release`
 * `make -j4`
 * `sudo make install`

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