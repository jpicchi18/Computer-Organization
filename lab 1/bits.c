/* 
 * CS:APP Data Lab 
 * 
 * <NAME: Joseph Picchi><UID: 605124511>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /* implementation details:
   * If there's an even number of 1's (and thus an even number of 0's), then if we xor together
   * every bit in x, all of the 1's will cancel to produce an end result of 0. If there is an odd
   * number of 1's (and thus an odd number of 0's), xor'ing together every bit will cancel every 1
   * except for one. The final remaining 1 or 0 ends up in the least significant bit place by the
   * procedures of this function, and it is returned at the very end, thus signifying whether
   * there was an odd number of 1's (ie an odd number of 0's) or an even number.
   */

  int shiftingMask, leftHalfShifted;

  //set the mask to extract the left half of x
  shiftingMask = (0x01 << 31) >> 15;

  //extract the left half of x and shift it to the right side
  leftHalfShifted = (x & shiftingMask) >> 16;

  //cancel any corresponding 1's in the two halves
  x ^= leftHalfShifted;

  //repeat the process by xor'ing the first 8 bits with the last 8 bits of the 16-bit result
  shiftingMask >>= 8;
  leftHalfShifted = (x & shiftingMask) >> 8;
  x ^= leftHalfShifted;

  //repeat the process by xor'ing the first 4 bits with the last 4 bits of the 8 bit-result
  leftHalfShifted = (x & 0xF0) >> 4;
  x ^= leftHalfShifted;

  //repeat by xor'ing the first 2 bits with the last 2 bits
  leftHalfShifted = (x & 0x0C) >> 2;
  x ^= leftHalfShifted;

  //repeat by xor'ing the first bit with the last bit of the 2-bit result
  leftHalfShifted = (x & 0x02) >> 1;
  x ^= leftHalfShifted;

  //return the last remaining bit
  return x & 0x01;
}




/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x18765432
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  /* Implmenetation details
   * this function creates a mask to extract the last n bits, then shifts x right by n,
   * then creates a mask to cancel the first n bits of x to 0, then adds back the n extracted
   * bits shifted to the proper location at the front of x. It deals with the case n = 0 by
   * creating a mask that is 0...0 for n = 0 and 1...1 for all non-negative n, thus preventing
   * the use of undefined behavior (ie shifting by a negative number).
   */

  int checkfor0, endmask,  endbits, result, frontmask;

  //create a mask for n=0 case --> 0...0 for n=0, 1...1 for n=nonzero
  checkfor0 = ~(!!n) + 1;
  
  //create a mask and extract the last n bits
  endmask = ~((~0x00) << n);

  //extract the last n bits
  endbits = x & endmask;
  
  //shift x to right by n
  x = x >> n;

  frontmask = ~(( (0x01 << 31) >> ((n + ~0x00) & checkfor0) ) & checkfor0 );
  
  //make a mask and cancel the first n bits
  //cancelmask = ~((~0x00) << (32-n));
  x = x & frontmask;

  result = 0x00 + x + ( endbits << ( (32 + ~n + 1) & checkfor0 ) );
  
  return result;
}



/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /* Implementation description:
   * 1) extracts bytes n and m and puts them in separate ints
   * 2) creates masks and uses them to mask out bytes n and m in x
   * 3) adds back n, shifted to m's place, and vice versa
   */   

  // extract bytes n and m --> desired bytes are located in
  // the least significant position for each variable
  int byte_n = (x >> (n << 3)) & 0xFF;
  int byte_m = (x >> (m << 3)) & 0XFF;

  // create masks for bytes n and m in x
  int mask_n = ~( 0xFF << (n << 3) );
  int mask_m = ~( 0xFF << (m << 3) );
  
  // shift byte n into m's position, and vice versa
  byte_n <<= (m << 3);
  byte_m <<= (n << 3);

  // mask out n and replace it with m
  x = (x & mask_n);
  x += byte_m;

  // mask out m and replace it with n
  x = x & mask_m;
  x += byte_n;

  return x;
}



/* 
 * fitsshort - return 1 if x can be represented as a 
 *   16-bit, two's complement integer.
 *   Examples: fitsShort(33000) = 0, fitsShort(-32768) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int fitsShort(int x) {
  /* Implementation Description
   * extract the top 17 bits and test to see whether all 17 are 1's or all 17 0's, as
   * these are the only conditions by which x could possibly fall in the range of a
   * valid 16-bit tc number
   */
  int top17mask, top17;

  //extract top 17 bits
  top17mask = ~0x00 << 15;
  top17 = (top17mask & x);

  //return 1 if top17 is either all 0's or all 1's
  return (!top17) | !(top17 ^ top17mask);
}



/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* implementation details:
   * performs bitwise "or" on flipped x and flipped y, and flips the result. The logic here is
   * a bitwise implementation of De-morgan's Law
   */
  return ~(~x | ~y);
}



/* 
 * subOK - Determine if can compute x-y without overflow
 *   Example: subOK(0x80000000,0x80000000) = 1,
 *            subOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subOK(int x, int y) {
  /* Implementation Details:
   * This function creates a mask to extract the sign bits of x and y, from which it determins if
   * x and y have different signs. It then performs subtraction and extracts the sign bit of the
   * result. The last line returns 0 if and only if the signs of the parameters differ and the sign
   * of the subtraction result differs from x, as these are the conditions that must be
   * met for overflow to have occured.
   */

  int signMask, signX, signY, xySignDiff, subResult, resultSign;

  //extract sign bit of x and sign bit of y
  signMask = 0x01 << 31;
  signX = signMask & x;       // tmin if x < 0, 0 otherwise
  signY = signMask & y;       // tmin of y < 0, 0 otherwise

  //check if x and y are different signs
  xySignDiff = signX ^ signY;         // tmin if signs differ, 0 otherwise

  //perform subtraction and extract sign of the result
  subResult = x + (~y) + 1;
  resultSign = signMask & subResult;   // tmin if result < 0, 0 otherwise

  //return 0 iff (x and y have different signs) AND (x and the result have different signs)
  return !( (!!xySignDiff) & ( !!(signX ^ resultSign)) );
}



/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /* Implementation Details:
   * This function checks 3 conditions to see if x is greater than y
   * (1) if x is negative and y is positive, return 0
   * (2) if x is positive and y is negative, return 1
   * (3) strip off the sign bit of x and y to get x' and y'. If (x' - y') is positive and
   *     and nonzero, return 1. Otherwise, return 0.
   */

  int signBitMask, xNeg, yNeg, xPosyNeg, xNegyPos, subResult, subSign;

  //create a mask to extract the sign bit
  signBitMask = 0x01 << 31;

  //extract sign bits from x and y
  xNeg = (signBitMask & x) >> 31;    // 1 if true, 0 if false
  yNeg = (signBitMask & y) >> 31;    // 1 if true, 0 if false

  //check if x > 0 && y < 0
  xPosyNeg = (!xNeg) & yNeg;  // 1 if true, 0 if false

  // check if x < 0 && y > 0
  xNegyPos = xNeg & (!yNeg);  // 1 if true, 0 if false
  
  //remove sign bits from x and y
  x &= ~signBitMask;
  y &= ~signBitMask;

  //subtract y from x (with their sign bits removed), and extract the sign bit of the result
  subResult = x + (~y) + 1;
  subSign = subResult & signBitMask;     // tmin if subResult < 0, 0 otherwise

  //return 1 if x is positive and y is negative
  //return 0 if x is negative and y is positive
  //return 0 if subResult < 0 | subResult = 0
  return xPosyNeg | !( subSign | !subResult | xNegyPos )  ;
}



/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* Implementation Description:
   * creates and uses a mask to extract the first n+1 bits of x. It returns 1 if the top
   * n+1 bits are either all 0's or all 1's, one of which conditions x must satisfy in order
   * for it to be possible to represent x as an n-bit tc integer. It also checks if n = 0,
   * generating a mask that prevents undefined behaviors (eg shifting by a negative value) if n = 0.
   */
  
  int checkfor0, topNmask, topNbits;
  
  // check for 0
  checkfor0 = ~(!!n) + 1;

  // extract top n+1 bits
  topNmask = ~0x00 << ( (n + ~0x00) & checkfor0 );
  topNbits = topNmask & x;

  // return 1 if topNbits are either all 0's or all 1's
  return (!topNbits) | !(topNbits ^ topNmask);
}



/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
/* implementation details:
 * flips the bits of x and adds 1 to the result
 */
  return (~x)+1;
}



/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  /* implementation details:
   * This implementation tests 2 different conditions to see if x is tmax:.
   * Condition 1: flipping tmax's bits and subtracting 1 yeilds tmax again
   * Condition 2: (to make the test case (x = -1) invalid) flipping x's bits
   *              and performing ! twice yields 1
   */

  int tmin, cond1, cond2;

  tmin = ~x;
  cond1 = tmin + (~0x00);
  cond2 = !!tmin;

  // check if cond1 == x and if cond2 is satisfied
  return (!(x ^ cond1)) & cond2;
}
