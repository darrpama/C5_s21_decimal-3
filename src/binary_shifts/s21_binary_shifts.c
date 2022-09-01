#include "../s21_decimal.h"

int funcLongSdvig(s21_long *dec, int coll) {
    int firstIndexBit = getLongFirstIndexBit(*dec);
    if ((firstIndexBit + coll) < 223) {
        for (int i = firstIndexBit; i >= 0; i--) {
            setLongBit(dec, i + coll, getLongBit(*dec, i));
        }
        for (int i = coll - 1; i >= 0; i--) {
            setLongBit(dec, i, 0);
        }
    } else {
        firstIndexBit = -1;
    }
    return firstIndexBit;
}
