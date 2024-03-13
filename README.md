# mem-stress-test
A stress test for computer memory that polls the average read and write speeds of memory. 

This test is made to see the effect of swapping on memory latency 

## Building

- There are no dependencies

run `make`, and the program will be built in the main directory

`make debug` to build and launch the program with arguments in gdb

`make test` to build and do a test run of the program with simple arguments

## Usage

`mem-stress-test [TYPE] [SIZE] [TESTS]`

_TYPE_: The available units for managing size taken up:
- `-b` for bytes
- `-k` for 1000 bytes
- `-m` for 1000000 bytes
- `-g` for 1000000000

_SIZE_: The amount of units to calculate size

_TESTS_: The amount of test memory operations to run
 > if _TESTS_ is too high, it is possible that the average could be misreported due to long overflows
