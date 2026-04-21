Project 00 - Coin Change
===============================

Go [back to home page](../../index.html)

**NOTE THAT THIS IS JUST A TEMPLATE. THE LINKS BELOW DO NOT WORK UNTIL A PROJECT IS ACTUALLY SUBMITTED / PUSHED TO THIS REPOSITORY**

<a name="overview"></a>Executive Summary
---------------------------------------

- [Executive Summary](./executiveSummary.pdf)

<a name="overview"></a>Implementation
---------------------------------------

- Implementations:
	- [C++](./implementation/bloomFilter.cpp)
	- [Java](./implementation/BloomFilter.java)
	- [Python](./implementation/BloomFilter.py)
- I/O (three separate cases; first line of each test file is the case count, usually `1`)
	- Tests: [test_1.txt](./implementation/io/test_1.txt), [test_2.txt](./implementation/io/test_2.txt), [test_3.txt](./implementation/io/test_3.txt)
	- Python expected: [expected_output_python_1.txt](./implementation/io/expected_output_python_1.txt), [_2](./implementation/io/expected_output_python_2.txt), [_3](./implementation/io/expected_output_python_3.txt)
	- Java expected: [expected_output_java_1.txt](./implementation/io/expected_output_java_1.txt), [_2](./implementation/io/expected_output_java_2.txt), [_3](./implementation/io/expected_output_java_3.txt)
	- [expected_output_cpp.txt](./implementation/io/expected_output_cpp.txt) — C++ (placeholder)

**Implementation note.** Different hash schemes change false positives vs absent; compare each language to its own expected file. Example: `python3 BloomFilter.py implementation/io/test_1.txt` then diff against `expected_output_python_1.txt`.

<a name="overview"></a>Slides
---------------------------------------

- [Presentation Slides](./slides/presentation_coinChange.pptx)


<a name="overview"></a>Programming Challenge
---------------------------------------

- [Programming Challenge](./programmingChallenge/problemStatement.pdf)
	- Solutions:
		- [C++](./programmingChallenge/solutions.pcSol_cpp.cpp)
	- Test Cases:
		- [Case 1 input](./programmingChallenge/io/test.in.1)
		- [Case 1 output](./programmingChallenge/io/test.out.1)
		- ...add the others here as needed
	