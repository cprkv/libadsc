# libadsc

C library for algorithms and data structures.  
For more information about API you can see:
 * tests (in the same folder as it sounds)
 * source code
 * *examples* (not ready)
 * *API docs* (not ready)

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