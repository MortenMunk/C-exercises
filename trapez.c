#include <stdio.h>
#include <math.h>

double trap(double a, double b, int n, double(*f)(double));
double h(double x);
double g(double x);
double sum(int n, double(*f)(double), double h, double a);


int main (void){
    for (int i=2; i <= 128; i*=2){
        printf("result is %lf on interval number %d\n", trap(-2, 2, i, h),i);
    }
    printf("\n");
    for (int i=2; i <= 128; i*=2){
        printf("result is %lf on interval number %d\n", trap(0, 3.14159, i, g), i);
    }
}

double trap(double a, double b, int n, double(*f)(double)){
    double result;
    double h = (b-a)/n;
    result = (h/2)*(f(a)+f(b)+2*sum(n, f, h, a));
    return result;
}

// Funktionen f til en halvcirkel
double h(double x){
    return sqrt(4-pow(x,2));
}

double g(double x){
    return pow(x,2)*sin(x);
}

// Danner summen
double sum(int n, double(*f)(double), double h, double a){
    double x, sum=0;
    for(int i=0; i < n; i++){
        x = a + i * h;
        sum += f(x);
    }
    return sum;
}