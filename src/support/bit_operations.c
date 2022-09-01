#include "../s21_decimal.h"

//  |   Get sign of decimal
//  V
int sign_number(s21_decimal x) { return get_bit(x, 127); }

//  |   Get single bit and set single bit functions
//  V
int get_bit(s21_decimal dec, int index) { return (dec.bits[index / 32] >>= index % 32) & 1; }

void set_bit_1(s21_decimal *x, int position) { x->bits[position / 32] |= (1U << position % 32); }

void setNullBit(s21_decimal *dec) {
    s21_decimal clear = {{0, 0, 0, 0}};
    *dec = clear;
}

void setLongNullBit(s21_long *dec) {
    s21_long clear = {{0, 0, 0, 0, 0, 0, 0}};
    *dec = clear;
}

void set_zero(s21_decimal *x, int position) {
    int mask = 1;
    int y = x->bits[position / 32];
    for (int n = 0; n < position % 32; n++) mask <<= 1;
    mask = ~mask;
    x->bits[position / 32] = y & mask;
}

void setBit(s21_decimal *dec, int index, int bit) {
    dec->bits[index / 32] ^= (getBit(*dec, index) ^ bit) << index % 32;
}

void setLongBit(s21_long *dec, int index, int bit) {
    dec->bits[index / 32] ^= (getLongBit(*dec, index) ^ bit) << index % 32;
}

int getBit(s21_decimal dec, int index) { return (dec.bits[index / 32] >>= index % 32) & 1; }

int getLongBit(s21_long dec, int index) { return (dec.bits[index / 32] >>= index % 32) & 1; }

// поиск первой 1 в bits
int getFirstIndexBit(s21_decimal dec) {
    int firstIndexBit = 0;
    for (int i = 96; i >= 0 && firstIndexBit == 0; i--) {
        if (getBit(dec, i)) {
            firstIndexBit = i;
        }
    }
    return firstIndexBit;
}

int getLongFirstIndexBit(s21_long dec) {
    int firstIndexBit = 0;
    for (int i = 222; i >= 0 && firstIndexBit == 0; i--) {
        if (getLongBit(dec, i)) {
            firstIndexBit = i;
        }
    }
    return firstIndexBit;
}

// проверка на 0
int testNa0(s21_decimal dec) {
    int flag = 0;
    for (int i = 0; i < 3 && !flag; i++) {
        if (dec.bits[i] != 0) {
            flag = 1;
        }
    }
    return flag;
}

int longtestNa0(s21_long dec) {
    int flag = 0;
    for (int i = 0; i < 7 && !flag; i++) {
        if (dec.bits[0] != 0) {
            flag = 1;
        }
    }
    return flag;
}

int errorRead(s21_decimal *result) {
    int ret = 0;
    if (getBit(*result, 100) && !getBit(*result, 127)) {
        ret = 1;
    } else if (getBit(*result, 101) || (getBit(*result, 100) && getBit(*result, 127))) {
        ret = 2;
    }
    setBit(result, 100, 0);
    setBit(result, 101, 0);
    return ret;
}

void set_sign(s21_decimal *x, int sign) {
    unsigned int mask = 1u << 31;
    if (sign != 0) {
        x->bits[3] |= mask;
    } else {
        x->bits[3] &= ~mask;
    }
}
