#include <stdio.h>
#include <math.h>

int main(void) {
    int a, b, i, cdiv;
    do {
        printf("enter two positive numbers to find greatest common divisor\n");
        scanf("%d %d", &a, &b);
        
        if ((a < 0) || (b < 0)) {
            return 0;
        }
        for(i=1; i <= a && i <= b; i++) {
            if ((a % i) == 0 && (b % i) == 0) {
                cdiv = i;
            }
        }
        printf("Greatest common divisor of %d and %d is %d\n\n", a, b, cdiv);
    } while(a >= 1 && b >= 1);
    return 0;
}