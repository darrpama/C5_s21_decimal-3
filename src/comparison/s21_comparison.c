#include "../s21_decimal.h"

int s21_is_less(s21_decimal x, s21_decimal y) {
    int result = 1;
    if (s21_is_equal(x, y)) {
        result = 0;
    }
    int signx = sign_number(x);
    int signy = sign_number(y);
    //  0 +; 1 -;
    if (!signx && signy) {  //  x > 0, y < 0
        result = 0;
    } else if (signx && !signy) {  //  x < 0, y > 0
        result = 1;
    } else if (signx && signy) {  //  x < 0, y < 0
        set_zero(&x, 127);
        set_zero(&y, 127);
        result = s21_is_greater(x, y);
    } else {
        s21_long x_long = fromDecTLong(x);
        s21_long y_long = fromDecTLong(y);
        longScaleVyrov(&x_long, &y_long, getScale(x), getScale(y));
        int tempres = longFuncSrav(x_long, y_long);
        if (tempres == 2) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal x, s21_decimal y) {
    int result = 1;
    if (s21_is_equal(x, y)) {
        result = 1;
    }
    int signx = sign_number(x);
    int signy = sign_number(y);
    //  0 +; 1 -;
    if (!signx && signy) {  //  x > 0, y < 0
        result = 0;
    } else if (signx && !signy) {  //  x < 0, y > 0
        result = 1;
    } else if (signx && signy) {  //  x < 0, y < 0
        set_zero(&x, 127);
        set_zero(&y, 127);
        result = s21_is_greater_or_equal(x, y);
    } else {
        s21_long x_long = fromDecTLong(x);
        s21_long y_long = fromDecTLong(y);
        longScaleVyrov(&x_long, &y_long, getScale(x), getScale(y));
        int tempres = longFuncSrav(x_long, y_long);
        if (tempres == 2 || s21_is_equal(x, y)) {
            result = 1;
        } else if (tempres == 0) {
            result = 1;
        } else {
            result = 0;
        }
    }
    return result;
}

int s21_is_greater(s21_decimal x, s21_decimal y) { return (s21_is_less(y, x)); }

int s21_is_greater_or_equal(s21_decimal x, s21_decimal y) { return (s21_is_less_or_equal(y, x)); }

int s21_is_equal(s21_decimal x, s21_decimal y) {
    int result = 1;
    for (int i = 0; i < 128; i++) {
        if (get_bit(x, i) != get_bit(y, i)) {
            result = 0;
        }
    }
    return result;
}

int s21_is_not_equal(s21_decimal x, s21_decimal y) {
    int result = 0;
    for (int i = 0; i < 128; i++) {
        if (get_bit(x, i) != get_bit(y, i)) {
            result = 1;
        }
    }
    return result;
}

/*
int funcSrav(s21_decimal dec1, s21_decimal dec2) {
    int firstIndexBit = 0;
    for (int i = 96; i >= 0 && firstIndexBit == 0; i--) {
        if (getBit(dec1, i) > getBit(dec2, i)) {
            firstIndexBit = 1;
        } else if (getBit(dec1, i) < getBit(dec2, i)) {
            firstIndexBit = 2;
        }
    }
    return firstIndexBit;
}
*/

int longFuncSrav(s21_long dec1, s21_long dec2) {
    int firstIndexBit = 0;
    for (int i = 222; i >= 0 && firstIndexBit == 0; i--) {
        if (getLongBit(dec1, i) > getLongBit(dec2, i)) {
            firstIndexBit = 1;
        } else if (getLongBit(dec1, i) < getLongBit(dec2, i)) {
            firstIndexBit = 2;
        }
    }
    return firstIndexBit;
}
