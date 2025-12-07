/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
 // return ~ ((~(x & ( ~y))) & ~(((~x) & y))); 第一次做的，结果是对的，但是是凑出来的，应该用得摩根率

 return ~((~((~x) & y)) & (~(x & (~y))));
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 1 << 31;
}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 2
 */
int isTmax(int x) {
  //return ! (x ^ (~ (1 << 31))); 这个结果正确，但是<<是非法字符
  //return !((~(x + 1)) ^ x); 这个也是错误的，只考虑了0111...111的情况，没有排除111...111的情况
  return (!((~(x + 1)) ^ x)) & (!!((~x) ^ 0));
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  //return !((x ^ 0xFFFFFFFF) & (x ^ 0xAAAAAAAA)); 这个是错误的，没有考虑A和F交替的情况
  //正确的方式是，将这个数与0xA（1010）与，相当于把偶数位给mask了，结果再和1010异或，看是否相同
  //生成32位AAA...AAA的方式是：先定义int A = 0xA，再定义int AA = A | (A << 4),以此类推
  int A = 0xA;
  int AA = A + (A << 4);
  int AAAA = AA + (AA << 8);
  int mask = AAAA + (AAAA << 16);
  return ! ((x & mask) ^ mask);
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~ x) + 1;
}
//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
    //return (!((x ^ 0x30) & 0xF8)) | (!(x ^ 0x38)) | (!(x ^ 0x39));
    // AI说了我上段代码正确，但是还是通不过btest
    //return !((x & 0xF8) ^ 0x30) | !((x & 0xFE) ^ 0x38);
	//上面一段还是不对，没有考虑32位的情况
	int cond1 = !(x >> 6);
	int cond2 = !((x & 0xF8) ^ 0x30);
	int cond3 = !((x & 0xFE) ^ 0x38);
	return cond1 & (cond2 | cond3);
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
    //return (((~!!x) + 1) & y) | (((~!x) + 1) & z);
	int mask1 = (~!!x) + 1;
	int mask2 = (~!x) + 1;
	return (mask1 & y) | (mask2 & z);
	//以上方法是我用我自己写的逻辑，用了中间表达式的方式重新表达
	//另一中生成mask的方式是，((!!x) <<31) >>31，生成要么全1，要么全0；另外也不必定义mask2，mask2实际上就是~mask1
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    //return ~((x + (~y) + 1) >> 31) + 1; 这条没通过，下面的也是我自己想出来的
	int result = x + (~y) + 1;
	//return (result >> 31) | (!result);//这个也不行，右移31位，前面会填充0，还需要&1
    //return ((result >> 31) & 1) | (!result);//还不行，没有考虑溢出情况
	int signX = (x >> 31) & 0b1;
	int signY = (y >> 31) & 0b1;
    //case1 x+ y-，返回0
	int case1 = signX & (!signY);
    //case2 x- y_，返回1
	int case2 = signX & (!signY);
    //case3 xy同号，返回case3的结果
    int case3_result = ((result >> 31) & 1) | (!result);
	int case3 = (!(signX ^ signY)) & case3_result;
	return case1 | case2 | case3;
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //return ~((x >> 31) | ((~x + 1) >> 31)) + 1; 这个没通过测试
  //下面的是自己想的
  int SignBit = (x >> 31) & 0b1;
  int minusOneSignBit = ((x - 1) >> 31) & 0b1;
  return ~SignBit & minusOneSignBit;
  //网上的结题思路是正数和它的相反数，signbit异或为1
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5  01100
 *            howManyBits(298) = 10  0100101010
 *            howManyBits(-5) = 4  1011
 *            howManyBits(0)  = 1  0
 *            howManyBits(-1) = 1  1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
    //没做出来
    //return !((x >> 1) | 0x0) + !((~(x >> 1)) | 0x0)
    //       + !((x >> 2) | 0x0) + !((~(x >> 2)) | 0x0)
    //       + !((x >> 3) | 0x0) + !((~(x >> 3)) | 0x0)
    //       + !((x >> 4) | 0x0) + !((~(x >> 4)) | 0x0)
    //       + !((x >> 5) | 0x0) + !((~(x >> 5)) | 0x0)
    //       + !((x >> 6) | 0x0) + !((~(x >> 6)) | 0x0)
    //       
	int signbit32 = (x >> 31) & 0b1;
    int signbit31 = (x >> 30) & 0b1;
    int signbit30 = (x >> 29) & 0b1;
    int signbit29 = (x >> 28) & 0b1;
    int signbit28 = (x >> 27) & 0b1;
    int signbit27 = (x >> 26) & 0b1;
    int signbit26 = (x >> 25) & 0b1;
	int signbit25 = (x >> 24) & 0b1;
    int signbit24 = (x >> 23) & 0b1;
    int signbit23 = (x >> 22) & 0b1;
    int signbit22 = (x >> 21) & 0b1;
    int signbit21 = (x >> 20) & 0b1;
    int signbit20 = (x >> 19) & 0b1;
    int signbit19 = (x >> 18) & 0b1;
	int signbit18 = (x >> 17) & 0b1;
    int signbit17 = (x >> 16) & 0b1;
    int signbit16 = (x >> 15) & 0b1;
    int signbit15 = (x >> 14) & 0b1;
    int signbit14 = (x >> 13) & 0b1;
    int signbit13 = (x >> 12) & 0b1;
    int signbit12 = (x >> 11) & 0b1;
	int signbit11 = (x >> 10) & 0b1;
    int signbit10 = (x >> 9) & 0b1;
    int signbit9 = (x >> 8) & 0b1;
    int signbit8 = (x >> 7) & 0b1;
    int signbit7 = (x >> 6) & 0b1;
    int signbit6 = (x >> 5) & 0b1;
    int signbit5 = (x >> 4) & 0b1;
	int signbit4 = (x >> 3) & 0b1;
    int signbit3 = (x >> 2) & 0b1;
    int signbit2 = (x >> 1) & 0b1;
    int signbit1 = x & 0b1;

	int res32 = !(signbit32 ^ signbit31);
	int res31 = !(signbit31 ^ signbit30);
	int res30 = !(signbit30 ^ signbit29);
	int res29 = !(signbit29 ^ signbit28);
	int res28 = !(signbit28 ^ signbit27);
	int res27 = !(signbit27 ^ signbit26);
	int res26 = !(signbit26 ^ signbit25);
	int res25 = !(signbit25 ^ signbit24);
	int res24 = !(signbit24 ^ signbit23);
	int res23 = !(signbit23 ^ signbit22);
	int res22 = !(signbit22 ^ signbit21);
	int res21 = !(signbit21 ^ signbit20);
	int res20 = !(signbit20 ^ signbit19);
	int res19 = !(signbit19 ^ signbit18);
	int res18 = !(signbit18 ^ signbit17);
	int res17 = !(signbit17 ^ signbit16);
	int res16 = !(signbit16 ^ signbit15);
	int res15 = !(signbit15 ^ signbit14);
	int res14 = !(signbit14 ^ signbit13);
	int res13 = !(signbit13 ^ signbit12);
	int res12 = !(signbit12 ^ signbit11);
	int res11 = !(signbit11 ^ signbit10);
	int res10 = !(signbit10 ^ signbit9);
	int res9 = !(signbit9 ^ signbit8);
	int res8 = !(signbit8 ^ signbit7);
	int res7 = !(signbit7 ^ signbit6);
	int res6 = !(signbit6 ^ signbit5);
	int res5 = !(signbit5 ^ signbit4);
	int res4 = !(signbit4 ^ signbit3);
	int res3 = !(signbit3 ^ signbit2);
	int res2 = !(signbit2 ^ signbit1);

    int res = res32
	+ res32 * (res31
	+ res31 * (res30
	+ res30 * (res29
	+ res29 * (res28
	+ res28 * (res27
	+ res27 * (res26
	+ res26 * (res25
	+ res25 * (res24
	+ res24 * (res23
	+ res23 * (res22
	+ res22 * (res21
	+ res21 * (res20
	+ res20 * (res19
	+ res19 * (res18
	+ res18 * (res17
	+ res17 * (res16
	+ res16 * (res15
	+ res15 * (res14
	+ res14 * (res13
	+ res13 * (res12
	+ res12 * (res11
	+ res11 * (res10
	+ res10 * (res9
	+ res9 * (res8
	+ res8 * (res7
	+ res7 * (res6
	+ res6 * (res5
	+ res5 * (res4
	+ res4 * (res3
	+ res3 * (res2
	))))))))))))))))))))))))))))));

	return 32 + (~res + 1);
	//以上是自己做的，但是可能超出规定的操作符了，这道题目看过了网上的解题方法，还有更巧妙的

}
//float
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
    //return uf + 0x00800000; // 这个好像只能是规格化的值才能这么弄，规格化的值只要阶码+1即可；规格化的要位数乘以2，即左移1位
                            //  规格化的数，&0x7F800000后为0，！后为1
                            //   非规格化的数，&0x7F800000后不为0，！后为0
	//以上不算数，以下重新自己做
	int s = (uf >> 31) & 0b1;
	int exp = (uf >> 23) & 0xFF;
	int frac = uf & 0b11111111111111111111111;
	//case1: 规格化，且exp未到最大值；也不是特殊值
	if ((exp != 0) & (exp != 0xfe) & (exp != 0xff))
	{
	exp = exp + 1;
	}
	//case2：规格化，且exp达到了最大值，返回inf
	if (exp == 0xfe)
	{
	exp = 0xff;
	frac = 0b00000000000000000000000;
	}
	//case3：非规格化，且frac未到最大值（frac未达到最大值的条件好像从来没用到）
	if (exp == 0)
	{
	frac = frac << 1;
	}
	//case4：特殊值
	if (exp == 0xff)
	{
	exp = exp;
	frac = frac;
	}
	//重新组装
	return (s << 31) | (exp <<23) | frac;

}
/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  return 2;
}
/* 
 * float_f2i - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int float_f2i(unsigned uf) {
  return 2;
}
