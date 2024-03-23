// Morten Munk Andersen
// Mortan21@student.aau.dk
// Group 6
// Software

#include <stdio.h>
#include <math.h>

// kalder prototyper da vi anvender top-down programmering (del og hersk)
double run_calculator();
void do_next_op(char first, double second, double *akkumulator);
void scan_data(char *first, double *second);
int is_binary(char first);
double division(double first, double second);
double square(double akkumulator);
double fraction(double akkumulator);


int main (void){
    run_calculator();
    return 0;
}

// sætter akkumulator startværdi til 0.0 for at undgå at akkumulator får en uønsket værdi.
// laver while loop der kører scan_data og do_next_op så længe input ikke er q.
double run_calculator(){
    double akkumulator = 0.0, second;
    char first;
    printf("Enter operator, and an optional operand: \n");
    scan_data(&first, &second);
    while (first != 'q'){
            do_next_op(first, second, &akkumulator);
            printf("Result so far is %lf\n", akkumulator);
            printf("Enter operator, and an optional operand: \n");
            scan_data(&first, &second);
        }
            printf("Final result is %lf", akkumulator);
            return akkumulator;
}

// laver en switch til de forskellige chars til de forskellige operatorer
void do_next_op(char first, double second, double *akkumulator){
    switch(first){
    case '+':
        *akkumulator += second;;
        break;
    case '-':
        *akkumulator -= second;
        break;
    case '*':
        *akkumulator *= second;
        break;
    case '/':
        *akkumulator = division(*akkumulator, second);
        break;
    case '^':
        *akkumulator = pow(*akkumulator, second);
        break;
    case '#':
        *akkumulator = square(*akkumulator);
        break;
    case '%':
        *akkumulator = (-*akkumulator);
        break;
    case '!':
        *akkumulator = fraction(*akkumulator);
        break;
    default:
        break;
    }
}

//bruger min is_binary funktion til at finde ud af om der skal skannes for first og second, eller blot first
void scan_data(char *first, double *second){
    scanf(" %c", first);
    if (is_binary(*first)){
        scanf(" %lf", second);
    }
    else{
        *second = 0.0;
    }
}
// laver et array med de binære operatorer og får en for-loop til at køre array igennem.
int is_binary(char first){
    char binary_operators[5] = {'+', '-', '*', '/', '^'};
    for(int i=0; i < 5; i++){
        if (binary_operators[i] == first){
            return 1;
        }
    }
    return 0;
}

// Binære operationer
double division(double first, double second){ //må ikke kunne dividere med 0
    if(second == 0){
        return first;
    }
    else{
        first /= second;
        return first;
    } 
}

//Unære operationer
double square(double akkumulator){ //man må ikke tage kvadratrod af negativt tal
    if(akkumulator < 0){
        return akkumulator;
    }
    else{
        akkumulator = sqrt(akkumulator);
        return akkumulator;  
    } 
} 

double fraction(double akkumulator){ //man må ikke dividere med 0
    if (akkumulator == 0.0){
        return akkumulator;
    } 
    else {
        akkumulator = (1 / akkumulator);
        return akkumulator;
    } 
}