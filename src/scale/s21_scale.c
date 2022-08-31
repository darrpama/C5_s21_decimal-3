#include "../s21_decimal.h"

s21_long _LONGDEC10 = {{10, 0, 0, 0, 0, 0, 0}};

int getScale(s21_decimal dec) {
    int scale = 0;
    for (int i = 119; i > 111; i--) {
        if (getBit(dec, i)) {
            scale += pow(2, i - 112);
        }
    }
    return scale;
}

void setScale(s21_decimal *dec, int scale) {
    for (int i = 112; i < 120; i++) {
        int temp = scale;
        setBit(dec, i, (temp >>= i - 112) & 1);
    }
}
// нужно дописать функцию, это пока набросок для \ , + и -
// sacale не должен быть больше 28!
/*
void scaleVyrov(s21_decimal *dec1, s21_decimal *dec2) {
    s21_decimal tempUmn10 = {{10, 0, 0, 0}};
    int znak1 = getBit(*dec1, 127);
    int znak2 = getBit(*dec2, 127);
    int scale1 = getScale(*dec1);
    int scale2 = getScale(*dec2);
    if (scale1 < scale2) {
        for (; scale1 < scale2; scale1++) {
            funcUmn(*dec1, tempUmn10, dec1);
        }
        setScale(dec1, scale1);
        setBit(dec1, 127, znak1);
    }
    if (scale1 > scale2) {
        for (; scale2 < scale1; scale2++) {
            funcUmn(*dec2, tempUmn10, dec2);
        }
        setScale(dec2, scale2);
        setBit(dec2, 127, znak2);
    }
}
*/
int longScaleVyrov(s21_long *dec1, s21_long *dec2, int scale1, int scale2) {
    if (scale1 < scale2) {
        for (; scale1 < scale2; scale1++) {
            funcLongUmn(*dec1, _LONGDEC10, dec1);
        }
    }
    if (scale1 > scale2) {
        for (; scale2 < scale1; scale2++) {
            funcLongUmn(*dec2, _LONGDEC10, dec2);
        }
    }
    return scale1;
}
