#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal* result) {
    int error = 0;
    if (error_finder(value)) {
        error = 1;
    } else {
        for (int i = 0; i < 4; i++) {
            result->bits[i] = value.bits[i];
        }
    }
    if (sign_number(value))
        set_zero(result, 127);
    else
        set_bit_1(result, 127);
    return error;
}

int s21_floor(s21_decimal value, s21_decimal* result) {
    int error = 0;
    s21_decimal ostatok = {{0}};
    s21_decimal delitel = {{10, 0, 0, 0}};
    s21_decimal temp_mnoj = {{10, 0, 0, 0}};
    if (error_finder(value)) {
        error = 1;
    } else {
        setNullBit(result);
        int scale = scale_finder(value);
        int sign = sign_number(value);
        value.bits[3] = 0;
        for (int i = 0; i < scale - 1; i++) s21_mul(delitel, temp_mnoj, &delitel);
        if (scale == 0) {
            delitel.bits[0] = delitel.bits[1] = delitel.bits[2] = delitel.bits[3] = 0;
        }
        if (!sign) {
            setScale(&ostatok, scale);
            ostatok.bits[0] = value.bits[0];
            ostatok.bits[1] = value.bits[1];
            ostatok.bits[2] = value.bits[2];
            s21_truncate(ostatok, result);
        } else {
            if (scale) {
                s21_add(value, delitel, &ostatok);
                setScale(&ostatok, scale);
                set_bit_1(&ostatok, 127);
                s21_truncate(ostatok, result);
            } else {
                result->bits[0] = value.bits[0];
                result->bits[1] = value.bits[1];
                result->bits[2] = value.bits[2];
                setScale(result, scale);
                set_bit_1(result, 127);
            }
        }
    }
    return error;
}

int s21_truncate(s21_decimal value, s21_decimal* result) {
    int error = 0;
    s21_decimal delitel = {{10, 0, 0, 0}};
    s21_decimal temp_mnoj = {{10, 0, 0, 0}};
    s21_decimal ostatok = {0};
    int scale = scale_finder(value);
    int sign = sign_number(value);
    if (error_finder(value)) {
        error = 1;
    } else if (scale_finder(value)) {
        setNullBit(result);
        value.bits[3] = 0;
        for (int i = 0; i < scale - 1; i++) s21_mul(delitel, temp_mnoj, &delitel);
        s21_mod(value, delitel, &ostatok);
        s21_sub(value, ostatok, &ostatok);
        s21_div(ostatok, delitel, result);
    } else {
        result->bits[0] = value.bits[0];
        result->bits[1] = value.bits[1];
        result->bits[2] = value.bits[2];
    }
    if (sign) set_bit_1(result, 127);
    return error;
}

int s21_round(s21_decimal value, s21_decimal* result) {
    int error = 0;
    s21_decimal ostatok = {{0}};
    s21_decimal ostatok2 = {{0}};
    s21_decimal delitel = {{10, 0, 0, 0}};
    s21_decimal temp_mnoj = {{10, 0, 0, 0}};
    if (error_finder(value)) {
        error = 1;
    } else {
        setNullBit(result);
        int scale = scale_finder(value);
        int sign = sign_number(value);
        value.bits[3] = 0;
        for (int i = 0; i < scale - 1; i++) s21_mul(delitel, temp_mnoj, &delitel);
        s21_mod(value, delitel, &ostatok);
        s21_div(delitel, temp_mnoj, &delitel);
        s21_mod(ostatok, delitel, &ostatok2);
        s21_sub(ostatok, ostatok2, &ostatok);
        s21_div(ostatok, delitel, &ostatok);
        if (ostatok.bits[0] >= 5) {
            s21_mul(delitel, temp_mnoj, &delitel);
            s21_add(value, delitel, &ostatok);
            setScale(&ostatok, scale);
            s21_truncate(ostatok, result);
        } else if (scale) {
            s21_mul(delitel, temp_mnoj, &delitel);
            s21_mod(value, delitel, &ostatok);
            s21_sub(value, ostatok, &ostatok);
            s21_div(ostatok, delitel, result);
        } else {
            result->bits[0] = value.bits[0];
            result->bits[1] = value.bits[1];
            result->bits[2] = value.bits[2];
        }
        if (sign) set_bit_1(result, 127);
    }
    return error;
}
