#include "../s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    setNullBit(result);
    s21_long longDec1 = fromDecTLong(value_1);
    s21_long longDec2 = fromDecTLong(value_2);
    s21_long longRes = {{0, 0, 0, 0, 0, 0, 0}};
    s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};

    if (testNa0(value_2)) {
        int scale = longScaleVyrov(&longDec1, &longDec2, getScale(value_1), getScale(value_2));
        temp = longDec1;
        longDivGetWholeAndRem(&temp, longDec2, &longRes);
        *result = funcResultToDecimal(temp, scale, getBit(value_1, 127));
        flag = errorRead(result);
    } else {
        flag = 3;
    }
    return flag;
}
