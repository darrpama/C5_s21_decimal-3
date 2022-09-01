#include "../s21_decimal.h"

s21_long fromDecTLong(s21_decimal dec1) {
    s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};
    for (int i = 0; i < 3; i++) {
        temp.bits[i] = dec1.bits[i];
    }
    return temp;
}

int s21_inf(float src) { return (src == 1.0 / 0.0 || src == -1.0 / 0.0); }

s21_decimal funcResultToDecimal(s21_long longRes, int scale, int znak) {
    int codeError = 0;
    s21_decimal result = {{0, 0, 0, 0}};
    int testInt = 0;
    s21_long temp1 = {{0, 0, 0, 0, 0, 0, 0}};
    while (((getLongFirstIndexBit(longRes) > 95) | (scale > 28)) && scale > 0) {
        temp1 = longRes;
        longDivGetWholeAndRem(&temp1, _LONGDEC10, &longRes);
        testInt = temp1.bits[0];
        scale--;
        codeError = 2;
    }
    if (getLongFirstIndexBit(longRes) > 95) {
        codeError = 1;
        setNullBit(&result);
    }
    for (int i = 0; i < 3; i++) {
        result.bits[i] = longRes.bits[i];
    }
    s21_decimal DEC1 = {{1, 0, 0, 0}};
    if (testInt > 4 && testInt < 10) {
        adder(result, DEC1, &result, 0);
    }
    setScale(&result, scale);
    setBit(&result, 127, znak);
    if (codeError == 1) {
        setBit(&result, 100, 1);
    } else if (codeError == 2 && !testNa0(result)) {
        setBit(&result, 101, 1);
    }
    return result;
}

int float_preparation(double src, float* temp, int* float_exp) {
    int scale = 0;
    for (; scale <= 28 && !((int)src / 100000000) && (int)src != src; src *= 10, scale++) {
    }
    *temp = (float)round(src);
    for (; scale > 0 && !((int)(*temp) % 10); (*temp) /= 10, scale--) {
    }
    *float_exp = get_float_exp(*temp);
    return scale;
}

int s21_from_float_to_decimal(float src, s21_decimal* dst) {
    setNullBit(dst);
    int error_code = 0;
    if (s21_nan(src) || s21_inf(src) || fabs(src) > S21_DEC_MAX || fabs(src) < 1e-28f) {
        error_code = 1;
    } else {
        int float_exp = 0, neg_flag = src < 0;
        double double_src = (double)fabs(src);
        float float_temp = 0;
        int scale = float_preparation(double_src, &float_temp, &float_exp);
        unsigned int int_src = *((unsigned int*)&float_temp);
        if (src != 0) set_bit_1(dst, float_exp);
        float_exp--;
        for (int i = 22; i >= 0; float_exp--, i--) {
            if ((int_src >> i) & 1) set_bit_1(dst, float_exp);
        }
        setScale(dst, scale);
        if (neg_flag) set_bit_1(dst, 127);
    }
    return error_code;
}

// возвращает экспоненту float-числа
int get_float_exp(float src) {
    int res = 0, beat = 0;
    int mask = 1;
    unsigned int int_src = *((unsigned int*)&src);
    mask <<= 23;
    for (int i = 0; i < 8; i++) {
        beat = !!(int_src & mask);
        mask <<= 1;
        if (beat == 1) res += pow(2, i);
    }
    res -= 127;
    return res;
}

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
    int error = 0;
    if (dst == NULL) {
        error = 1;
    } else {
        setNullBit(dst);
        if (src < 0) {
            set_bit_1(dst, 127);
            src *= -1;
        }
        dst->bits[0] = src;
    }
    return error;
}

int s21_from_decimal_to_int(s21_decimal src, int* dst) {
    int error = 0;
    if (error_finder(src)) {
        error = 1;
    } else {
        long double temp = from_decimal_to_double(src);
        if (fabsl(temp) >= INT_MAX) {
            error = 1;
        } else {
            *dst = (int)temp;
        }
    }
    return error;
}

long double fabsl(long double number) {
    if (number < 0) number *= -1;
    return number;
}

// вспомогательная функция, переводящая децимал-число в формат double
long double from_decimal_to_double(s21_decimal src) {
    long double dst = 0;
    int mask = 1, beat = 0;
    for (int i = 0; i < 3; i++) {
        for (int y = 0; y < 32; y++) {
            beat = !!(src.bits[i] & mask);
            mask <<= 1;
            if (beat == 1) dst += pow(2, y + (i * 32));
        }
        mask = 1;
    }
    int exp = scale_finder(src);
    for (int i = 0; i < exp; i++) dst /= 10;
    if (sign_number(src)) dst *= -1;
    return dst;
}

int s21_from_decimal_to_float(s21_decimal src, float* dst) {
    int error = 0;
    if (error_finder(src) || dst == NULL) {
        error = 1;
        if (scale_finder(src) > 28) *dst = 0;
    } else {
        *dst = 0;
        long double temp = 0;
        int scale = scale_finder(src);
        for (int i = 0; i < 96; i++) {
            if (get_bit(src, i)) {
                temp += pow(2, i);
            }
        }
        temp *= powl(10.f, -scale);
        *dst = temp;
        if (sign_number(src)) *dst = -(*dst);
    }
    return error;
}

// возвращает 1, если с decimal-структурой что-то не так:
// scale > 28, n/a значение etc.
int error_finder(s21_decimal dec) {
    int error = 0, dec1 = 0;
    for (int i = 0; i < 4; i++) {
        dec1 = dec.bits[i];
        if (dec1 == S2_INF || s21_nan(dec1) || scale_finder(dec) > 28 || dec1 == -S2_INF) error = 1;
    }
    return error;
}

int s21_nan(long double x) { return x != x ? 1 : 0; }

// возвращает scale-значение структуры decimal
int scale_finder(s21_decimal dec) {
    int scale = 0;
    for (int i = 112; i < 120; i++) {
        if (get_bit(dec, i)) scale += pow(2, i - 112);
    }
    return scale;
}
