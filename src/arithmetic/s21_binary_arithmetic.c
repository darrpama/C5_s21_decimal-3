#include "../s21_decimal.h"

//  |   Summator and half-summator for all math functions
//  V

int halfAdder(int a, int b, int *c) {  //  полусумматор
    int flag = (a ^ b) ^ *c;
    *c = (a & b) | ((a ^ b) & *c);
    return flag;
}

//  op 0 = +
//  op 1 = -
void adder(s21_decimal dec1, s21_decimal dec2, s21_decimal *res, int op) {  //  суматор с функцией вычитания
    int c = op;
    for (int i = 0; i < 96; i++) {
        setBit(res, i, halfAdder(getBit(dec1, i), op ^ getBit(dec2, i), &c));
        setBit(res, i + 1, c);
    }
}

void longAdder(s21_long dec1, s21_long dec2, s21_long *res, int op) {  //  суматор с функцией вычитания
    int c = op;
    for (int i = 0; i < 223; i++) {
        setLongBit(res, i, halfAdder(getLongBit(dec1, i), op ^ getLongBit(dec2, i), &c));
        setLongBit(res, i + 1, c);
    }
}

// получение остатка dec1 получение результата при деление res
void longDivGetWholeAndRem(s21_long *dec1, s21_long dec2, s21_long *res) {
    setLongNullBit(res);
    s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};
    s21_long temp2 = {{0, 0, 0, 0, 0, 0, 0}};
    int firstBitDec = getLongFirstIndexBit(*dec1) - getLongFirstIndexBit(dec2);
    for (int i = 0; i <= firstBitDec; i++) {
        setLongNullBit(&temp);
        temp2 = dec2;
        funcLongSdvig(&temp2, firstBitDec - i);
        longAdder(*dec1, temp2, &temp, 1);
        if (getLongBit(temp, 223)) {
            setLongBit(res, 0, 1);
            setLongBit(&temp, 223, 0);
            longAdder(*dec1, temp2, dec1, 1);
            setLongBit(dec1, 223, 0);
        }
        if (i < firstBitDec) {
            funcLongSdvig(res, 1);
        }
    }
}

// функция умножения
int funcLongUmn(s21_long dec1, s21_long dec2, s21_long *res) {
    setLongNullBit(res);
    int flag = 1;
    for (int i = 0; i < 221 && flag; i++) {
        s21_long temp = {{0, 0, 0, 0, 0, 0, 0}};
        setLongNullBit(&temp);
        for (int j = 0; j < 221 && flag; j++) {
            if (getLongBit(dec2, i)) {
                setLongBit(&temp, j + i, getLongBit(dec1, j) & getLongBit(dec2, i));
                if (getLongBit(dec1, j) && i + j >= 221) {
                    flag = 0;
                }
            }
        }
        if (getLongBit(dec2, i)) {
            longAdder(*res, temp, res, 0);
        }
    }
    return flag;
}
