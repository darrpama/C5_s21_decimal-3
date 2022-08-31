#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int flag = 0;
    setNullBit(result);
    s21_long longDec1 = fromDecTLong(value_1);
    s21_long longDec2 = fromDecTLong(value_2);
    s21_long longRes = {{0, 0, 0, 0, 0, 0, 0}};
    s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};
    if (testNa0(value_2)) {
        int znak = getBit(value_1, 127) ^ getBit(value_2, 127);
        longScaleVyrov(&longDec1, &longDec2, getScale(value_1), getScale(value_2));
        longDivGetWholeAndRem(&longDec1, longDec2, &longRes);
        int i = 0;
        for (; i < 29 && longtestNa0(longDec1); i++) {
            setLongNullBit(&temp);
            funcLongUmn(longDec1, _LONGDEC10, &longDec1);
            longDivGetWholeAndRem(&longDec1, longDec2, &temp);
            funcLongUmn(longRes, _LONGDEC10, &longRes);
            longAdder(longRes, temp, &longRes, 0);
        }
        *result = funcResultToDecimal(longRes, i, znak);
        flag = errorRead(result);
    } else {
        flag = 3;
    }
    return flag;
}
