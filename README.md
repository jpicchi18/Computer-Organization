# Computer-Organization
Course projects for the UCLA course entitled "Introduction to Computer Organization". All projects were implemented in C or x86-64 Assembly.
Details of all projects can be seen by following the provided links and looking at the assignment specs (pdf file in each directory)

[Lab 0: Warmup](https://github.com/jpicchi18/computer_organization/tree/main/lab%200):
- Set up the class development and testing environment
- implemented function that performs ```x *= 3/4``` using bitwise operations

[Lab 1: Datalab (Bit Puzzles)](https://github.com/jpicchi18/computer_organization/tree/main/lab%201):
- implemented a series of functions that perform a range of functions using only a restricted number of bitwise operations:
  - ```int bitParity(int x)``` --> returns 1 if bit string x contains an odd number of 0's
  - ```int rotateRight(int x, int n)``` --> Rotates the bit string x to the right by n places
  - ```int byteSwap(int x, int n, int m)``` --> swaps the nth byte and the mth byte of the bitstring x
  - etc... (the complete list of puzzles and operation restrictions is found by clicking the link above and examining the "bits.c" file)
  
[Lab 2: Bomblab](https://github.com/jpicchi18/computer_organization/tree/main/lab%202):
- Analyzed assembly language instructions and an associated symbol table to figure out what string to input into the command line to defuse the "bomb" (i.e. executable that takes points off the project score when it "explodes")
  - 6 different phases of the bomb (i.e. 6 different input strings), each progressively more difficult
  
[Lab 3: Attack Lab](https://github.com/jpicchi18/computer_organization/tree/main/lab%203):
- Generated a total of 6 attacks on 2 programs with different security vulnerabilities
  - provides an introduction to "hacking methods"
  - attacks leveraged buffer overflow, code injection, stack and parameter-passing mechanisms of x86-64 machine code, gadget farms, and return-oriented programming.
  
[Lab 4: Parallel Lab & Intro to Multi-Threading](https://github.com/jpicchi18/computer_organization/tree/main/lab%204):
- accelerated poorly-written code by taking advantage of parallel computing and multi-threading techniques, all while protecting against race conditions
- used OpenMP to generate threads and execute sections of the code in parallel
