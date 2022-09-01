#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
    int znak = 0;
    s21_long longDec1 = fromDecTLong(value_1);
    s21_long longDec2 = fromDecTLong(value_2);
    s21_long longRes = {{0, 0, 0, 0, 0, 0, 0}};
    int scale = longScaleVyrov(&longDec1, &longDec2, getScale(value_1), getScale(value_2));
    int flagOne = longFuncSrav(longDec1, longDec2);
    if (getBit(value_1, 127) ^ getBit(value_2, 127)) {
        longAdder(longDec1, longDec2, &longRes, 0);
        znak = getBit(value_1, 127);
    } else {
        if (flagOne == 1) {
            longAdder(longDec1, longDec2, &longRes, 1);
            znak = getBit(value_1, 127);
        } else if (flagOne == 2) {
            longAdder(longDec2, longDec1, &longRes, 1);
            znak = !getBit(value_2, 127);
        }
    }
    setLongBit(&longRes, 223, 0);
    *result = funcResultToDecimal(longRes, scale, znak);
    return errorRead(result);
}
