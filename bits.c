/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~((~x) | (~y));
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return (~(x & y)) & (~((~x) & (~y))); 
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(x && y) return !((x>>31) ^ (y>>31));
    return !(x ^ y); 
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int pd=(v>0x0000FFFF)<<4, ans=0;
    ans|=pd; v>>=pd;
    pd=(v>0x000000FF)<<3; 
    ans|=pd; v>>=pd; 
    pd=(v>0x0000000F)<<2; 
    ans|=pd; v>>=pd;
    pd=(v>0x00000003)<<1; 
    ans|=pd; v>>=pd;
    return ans|(v>1);
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) { 
    n<<=3; m<<=3; int val1=(x>>n)&0xFF, val2=(x>>m)&0xFF;
    return x ^ (val1<<n) ^ (val1<<m) ^ (val2<<n) ^ (val2<<m);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    v=((v&0xAAAAAAAA)>>1)|((v&0x55555555)<<1);
    v=((v&0xCCCCCCCC)>>2)|((v&0x33333333)<<2);
    v=((v&0xF0F0F0F0)>>4)|((v&0x0F0F0F0F)<<4);
    v=((v&0xFF00FF00)>>8)|((v&0x00FF00FF)<<8);
    v=((v&0xFFFF0000)>>16)|((v&0x0000FFFF)<<16);
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    return (x>>n)&(0xFFFFFFFF>>n);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int pd=!((x&0xFFFF0000)^0xFFFF0000), ans=0; 
    ans|=pd<<4; x>>=(!pd)<<4;
    pd=!((x&0x0000FF00)^0x0000FF00);
    ans|=pd<<3; x>>=(!pd)<<3;
    pd=!((x&0x000000F0)^0x000000F0);
    ans|=pd<<2; x>>=(!pd)<<2;
    pd=!((x&0x0000000C)^0x0000000C);
    ans|=pd<<1; x>>=(!pd)<<1;
    ans+=(x>>1&1)+(!((x&3)^3));
    return ans;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if(!x) return 0; unsigned k=0, s=0, rx=x;
    if(x<0) s=2147483648, rx=-rx; 
    for(;k<32;k++) { if(rx>>k) ; else break ; } 
    k--; s+=((k+127)<<23);
    if(k<24) return s + ((rx&((1<<k)-1))<<(23-k));
    else {
        k-=23;
        unsigned mask=1<<k, val1=rx&(mask-1), val2=(rx>>k)&0x007FFFFF, p=0;
        mask>>=1; if(val1>mask) p=1; if((val1==mask) & val2) p=1; 
        return s + val2 + p;
    } return 0; 
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned val=uf&0x7F800000;
    if(val==0x7F800000) return uf;
    if(val) return uf+0x00800000;
    return uf+(uf&0x007FFFFF);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    unsigned s=uf2>>31, A=uf2&0x000FFFFFF, B=uf1;
    int e=((uf2>>20)&0x000007FF); e-=1023;
    if(e<0) return 0; 
    if(e>=31) {
        if(s) return -2147483648;
        return 0x80000000;
    }
    int val=1<<e;
    if(e<=20) val|=(A>>(20-e))&((1<<e)-1);
    else {
        val|=A<<(e-20);
        val|=(B>>(52-e))&((1<<(e-20))-1);
    }
    if(s) return -val;
    return val; 
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if(x>=128) return 0x7F800000;
    if(x<-149) return 0; 
    if(x>=-126) return (x+127)<<23;
    return 1<<(149+x);
}
