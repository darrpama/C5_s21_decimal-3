#include "../s21_decimal.h"
/*
void print_decimal(s21_decimal x) {
    printf("Mantiss is:");
    for (int j = 0; j < 96; j++) {
        if (j%32 == 0) {
            printf(" ");
        }
        printf("%d", get_bit(x, j));
    }
    printf("\nExponent is: ");
    for (int j = 96; j < 128; j++) {
        printf("%d", get_bit(x, j));
    }
    printf("\n");
}

void print(s21_decimal res) {
    printf("\n_______START___________\n");
    for (int i = 0; i < 128; i++) {
        if (i && i%32 == 0) {
            printf("\n");
        }
        if (i == 112 || i == 120) {
            printf("| ");
        }
        printf("%d ", getBit(res, i));
    }
    printf("\n________END__________\n");
}

void printLong(s21_long res) {
    printf("\n_______START___________\n");
    for (int i = 0; i < 224; i++) {
        if (i && i%32 == 0) {
            printf("\n");
        }
        printf("%d ", getLongBit(res, i));
    }
    printf("\n________END__________\n");
}
*/
