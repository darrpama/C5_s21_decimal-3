#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//  |  core
//  V
#define FLOAT_MIN 3.3E-38
#define FLOAT_MAX 3.3E+38
#define INT_MAX 2147483647
#define S2_INF 1.0 / 0.0
#define S21_DEC_MAX pow(2, 96)

typedef struct {
    int bits[4];
} s21_decimal;

typedef struct {
    int bits[7];
} s21_long;

typedef enum { OK, S21_INF, S21_NEG_INF, S21_NAN } errors;

extern s21_long _LONGDEC10;

//  |  s21_binary_arithmetic
//  V
int halfAdder(int a, int b, int *c);
void adder(s21_decimal dec1, s21_decimal dec2, s21_decimal *res, int op);
void longAdder(s21_long dec1, s21_long dec2, s21_long *res, int op);
int funcLongUmn(s21_long dec1, s21_long dec2, s21_long *res);
void longDivGetWholeAndRem(s21_long *dec1, s21_long dec2, s21_long *res);

//  |  s21_add
//  V
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//  |  s21_div
//  V
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//  + нет проверки на макс мин

//  |  s21_mul
//  V
int s21_mul(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);
//+ нет проверки на макс мин

//  |  s21_sub
//  V
int s21_sub(s21_decimal dec1, s21_decimal dec2, s21_decimal *res);

//  |  s21_mod
//  V
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//  |  s21_shifts
//  V
int funcLongSdvig(s21_long *dec, int coll);

//  |  s21_comparison
//  V
int s21_is_less(s21_decimal x, s21_decimal y);
int s21_is_less_or_equal(s21_decimal x, s21_decimal y);
int s21_is_greater(s21_decimal x, s21_decimal y);
int s21_is_greater_or_equal(s21_decimal x, s21_decimal y);
int s21_is_equal(s21_decimal x, s21_decimal y);
int s21_is_not_equal(s21_decimal x, s21_decimal y);
int funcSrav(s21_decimal dec1, s21_decimal dec2);
int longFuncSrav(s21_long dec1, s21_long dec2);

//  |  s21_converters
//  V
s21_long fromDecTLong(s21_decimal dec1);
s21_decimal funcResultToDecimal(s21_long longRes, int scale, int znak);
int get_float_exp(float src);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int float_preparation(double src, float *temp, int *float_exp);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
long double from_decimal_to_double(s21_decimal src);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int scale_finder(s21_decimal dec);
long double fabsl(long double number);
int error_finder(s21_decimal dec);
int s21_nan(long double x);
int s21_inf(float src);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//  |  s21_scale
//  V
int getScale(s21_decimal dec);
void setScale(s21_decimal *dec, int scale);
void scaleVyrov(s21_decimal *dec1, s21_decimal *dec2);
int longScaleVyrov(s21_long *dec1, s21_long *dec2, int scale1, int scale2);

//  |  bit_operations
//  V
int sign_number(s21_decimal x);
void set_sign(s21_decimal *x, int sign);
int get_bit(s21_decimal x, int position);
int getBit(s21_decimal dec, int index);
int getLongBit(s21_long dec, int index);

void set_bit_1(s21_decimal *x, int position);
void setNullBit(s21_decimal *dec);
void setLongNullBit(s21_long *dec);

void set_zero(s21_decimal *x, int position);
void setBit(s21_decimal *dec, int index, int bit);
void setLongBit(s21_long *dec, int index, int bit);

int getFirstIndexBit(s21_decimal dec);
int getLongFirstIndexBit(s21_long dec);

int testNa0(s21_decimal dec);
int longtestNa0(s21_long dec);
int errorRead(s21_decimal *result);
//  |  support_materials
//  V
void converter(float x);
void print_decimal(s21_decimal x);
void printLong(s21_long res);
void print(s21_decimal res);

// |   another functions
// V
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

#endif  //  SRC_S21_DECIMAL_H_
