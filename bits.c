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
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
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
    if ((x ^ y) >> 31) {
        return 0;
    }
    if (x && y) {
        return 1;
    }
    if (!x && !y) {
        return 1;
    }
    return 0;
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
    int r = (v > 65535) << 4;
    r = r | (((v >> r) > 255) << 3);
    r = r | (((v >> r) > 15) << 2);
    r = r | (((v >> r) > 3) << 1);
    r = r | ((v >> r) > 1);
    return r;
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
    n = n << 3;
    m = m << 3;
    int c = (x >> n) & 255;
    int d = (x >> m) & 255;
    x = x ^ (c << n);
    x = x | (d << n);
    x = x ^ (d << m);
    x = x | (c << m);
    return x;
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
    unsigned r = 0;
    unsigned i = 32;

    while (i) {
        r = (r << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }

    return r;
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
    int y = x & (1 << 31);
    x = x >> n;
    y = y >> n;
    y = y << 1;
    x = y ^ x;
    return x;
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
    int y = ((1 << 31) & x) >> 31;
    x = ~x;
    int b16 = !!(x >> 15) << 4;
    x = x >> b16;
    int b8 = !!(x >> 7) << 3;
    x = x >> b8;
    int b4 = !!(x >> 3) << 2;
    x = x >> b4;
    int b2 = !!(x >> 1) << 1;
    x = x >> b2;
    int b1 = x;
    int b = b16 + b8 + b4 + b2 + b1;
    int an = 32 + (~b + 1);
    return an & y;
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
    int a, i, b, j;
    b = 1 << 31;
    a = b & x;
    if (a) {
        x = ~x + 1;
    }
    for (i = 1; i < 33; i = i + 1) {
        if (x & b) {
            j = ~b & x;
            a = a | ((159 - i) << 23);
            if (i > 8) {
                a = a | (j << (i - 9));
            } else {
                int s = 9 - i;
                int mask = (1 << s) + ~0;
                int rest = mask & j;
                int half = 1 << (s - 1);
                a = a | (j >> s);
                if (rest + (a & 1) > half) {
                    a = a + 1;
                }
            }
            break;
        }
        b = b >> 1;
    }
    return a;
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
    unsigned exp = (uf >> 23) & 0xFF;
    if (exp == 255) {
        return uf;
    }
    if (exp == 0) {
        return (uf & 0x80000000) |
               ((uf & 0x7FFFFFFF) << 1);
    }
    if (exp == 254) {
        return (uf & 0x80000000) | 0x7F800000;
    }
    return uf + (1 << 23);
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
    int sn = (1 << 31) & uf2;
    int a = (uf2 >> 20) & 0x000007FF;
    if (a < 1023) {
        return 0;
    }
    if (a > 1053) {
        return 0x80000000;
    }
    int n = a - 1023;
    int an = 1 << n;
    if (n <= 20) {
        an = an | ((uf2 >> (20 - n)) & (~0 + (1 << n)));
    } else {
        an = an | ((uf2 & (~0 + (1 << 20))) << (n - 20));
        an = an | ((uf1 >> (52 - n)) & (~0 + (1 << (n - 20))));
    }
    if (sn) {
        an = ~an + 1;
    }
    return an;
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
    if (x > 127) {
        return 0x7F800000;
    }
    if (x < -149) {
        return 0;
    }
    if (x >= -126) {
        return (127 + x) << 23;
    }
    return 1 << (x + 149);
}
