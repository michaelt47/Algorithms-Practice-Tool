Written by Michael Timothy
Github: michaelt47


Algorithm Writing Practice Tool

Usage:

All algorithms are made using the base Algorithm class.
To build your own, follow these instructions:

1. Copy the Algorithm Template to create a new algorithm.

2. There are instructions marked "TODO" inside the AlgorithmTemplate.cpp file
which explain what you need to implement per algorithm.

3. Once you have your algorithm set up, you'll need to put 
"#include YourAlgorithm.cpp" at the top of testWrapper.cpp. 

4. Then you'll have to include a user input parser
inside of the getAlgorithm function. See the BinarySearch 
and Summation examples to see how to do so.

5. If you need custom test inputs, see the python scripts inside
the randInts or randSortedInts folder which generate test inputs
for algorithms.


Different testing modes:

Small - 12 numbers, 0-100
Medium - 100 numbers, 0-100000
Big - 1000000 numbers, 0-100000000


Building:

Build this program by going to the base directory and running
"cmake --build ./build"


Running:

Run with ./bin/AlgorithmPracticeTool [algorithm] [mode]