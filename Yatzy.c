// Morten Munk Andersen
// Mortan21@student.aau.dk
// Group 6
// Software

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define DICE_EYES 6

// enumerationer som kan loopes igennem
enum game{ones = 0, twos, threes, fours, fives, sixes, 
one_pair, two_pair, three_of_a_kind, four_of_a_kind, small_staight, big_straight, house, chance, yatzy};
typedef enum game game;

void roll_multiple_dice(int amount_of_dices, int *outcomes);
void dice_printer(int *array, int size);
int eye_occurence(int dice_amount, int *array, int eye);
int highest_pair(int *array, int size, int amount_of_pairs);
int *find_two_pair(int *array, int size);
int small_straight_check(int *array, int size);
int big_straight_check(int *array, int size);
int *house_calc(int *array, int size);
int chance_calc(int *array, int size);
int yatzy_calc(int *array, int size);


int main (void){
    game game;
    int amount_of_dices;
    //char strings til at kalde de forskellige operationer der udregnes for.
    char dice_names[15][25] = {"ones", "twos", "threes", "fours", "fives", "sixes",
    "one pair", "two pairs", "three of a kind", "four of a kind", "small straight", "big straight", "house", "chance", "yatzy"};
    int point_sum = 0;
    int small_straight_point = 0;
    int big_straight_point = 0; 
    int chance_point = 0;
    int yatzy_point = 0;
    int one_pair_sum = 0;
    int three_pair_sum = 0;
    int four_pair_sum = 0;
    int two_pair_sum = 0;
    int *house_eyes;
    int house_sum = 0;

    srand(time(NULL));

    printf("How many dices would you like to throw?\n");
    scanf(" %d", &amount_of_dices);

    // Allokerer hukkommelse til array
    int *outcomes = malloc((amount_of_dices) * sizeof(int));
    if(outcomes == NULL){
        printf("Memory not allocated!\n");
        exit(EXIT_FAILURE);
    }
    // do while, så programmet kan gentages såfremt der slås igen
    do{
        point_sum=0;
        small_straight_point=0;
        big_straight_point=0; 
        chance_point=0;
        yatzy_point=0;
        one_pair_sum=0;
        three_pair_sum=0;
        four_pair_sum=0;
        two_pair_sum=0;
        house_sum=0;
        // Enumeration for-loop fra ones til sixes
        for(game = ones; game <= sixes; ++game){
            roll_multiple_dice(amount_of_dices, outcomes);
            dice_printer(outcomes, amount_of_dices);
            printf("---- %d of %s!\n", eye_occurence(amount_of_dices, outcomes, game), dice_names[game]);
            point_sum += eye_occurence(amount_of_dices, outcomes, game) * (game + 1);
        }
        // tilføjer 50 ekstra point hvis øvre sektion giver 64 eller flere point totalt
        printf("\nPoints so far: %d\n", point_sum);
        if(point_sum >= 64){
            point_sum += 50;
            printf("Totals points over 64, so you gain 50 extra points!\n");
            printf("Total points including bonus: %d\n\n", point_sum);
        }
        // Enumeration loop fra one-pair til yatzy
        for(game = one_pair; game <= yatzy; ++game){
            roll_multiple_dice(amount_of_dices, outcomes);
            switch(game){
                case one_pair:
                    dice_printer(outcomes, amount_of_dices);
                    int one_pair_value = highest_pair(outcomes, amount_of_dices, 2);
                    if(one_pair_value > 0){
                        one_pair_sum += (one_pair_value * 2);
                        printf("---- %d has %s, with a total of %d points\n", one_pair_value, dice_names[game], one_pair_sum); 
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);
                    }
                    break;   
                case two_pair:
                    dice_printer(outcomes, amount_of_dices);
                    int *result = find_two_pair(outcomes, amount_of_dices);
                    if(result[0] > 0 && result[1] > 0){
                        two_pair_sum = ((result[0] * 2) + (result[1] * 2)) ;
                        printf("---- %d and %d has %s, with a total of %d points\n", result[0], result[1], dice_names[game], two_pair_sum);
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);
                        two_pair_sum = 0;
                    }
                    break;
                case three_of_a_kind
            :
                    dice_printer(outcomes, amount_of_dices);
                    int three_pair_value = highest_pair(outcomes, amount_of_dices, 3);
                    if(three_pair_value > 0){
                        three_pair_sum = (three_pair_value * 3);
                        printf("---- %d has %s, with a total of %d points\n", three_pair_value , dice_names[game], three_pair_sum);
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);
                        three_pair_sum = 0;
                    }
                    break;
                case four_of_a_kind:
                    dice_printer(outcomes, amount_of_dices);
                    int four_pair_value = highest_pair(outcomes, amount_of_dices, 4);
                    if(four_pair_value > 0){
                        four_pair_sum = (four_pair_value * 4);
                        printf("---- %d has %s. with a total of %d points\n", four_pair_value , dice_names[game], four_pair_sum);
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);
                        four_pair_sum = 0;
                    }
                    break;
                case small_staight:
                    small_straight_point = small_straight_check(outcomes, amount_of_dices);
                    dice_printer(outcomes, amount_of_dices);
                    if(small_straight_point){
                        printf("---- You have %s, with a total of %d points\n", dice_names[game], small_straight_point);
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);
                    }
                    break;
                case big_straight:
                    big_straight_point = big_straight_check(outcomes, amount_of_dices);
                    dice_printer(outcomes, amount_of_dices);
                    if(big_straight_point){
                        printf("---- You have %s, with a total of %d points\n", dice_names[game], big_straight_point);
                    }
                    else{
                        printf("---- You don't have %s\n", dice_names[game]);                  
                    }
                    break;
                case house:
                    house_eyes = house_calc(outcomes, amount_of_dices);
                    dice_printer(outcomes, amount_of_dices);
                    if(house_eyes[0] > 0 && house_eyes[1] > 0){
                        house_sum = (house_eyes[0] * 3) + (house_eyes[1] * 2);
                        printf("---- You have %s. Three of a kind on %d and a pair on %d, with a total of %d points\n", dice_names[game], house_eyes[0], house_eyes[1], house_sum);                    
                    }
                    else{
                        printf("---- You do not have house\n");
                        house_sum = 0;
                    }
                    break;
                case chance:
                    chance_point = chance_calc(outcomes, amount_of_dices);
                    dice_printer(outcomes, amount_of_dices);
                    printf("---- You got %d points in the %s round!\n", chance_point, dice_names[game]);
                    break;
                case yatzy:
                    yatzy_point = yatzy_calc(outcomes, amount_of_dices);
                    dice_printer(outcomes, amount_of_dices);
                    if(yatzy_point == 50){
                        printf("---- You got %s, with a total of %d points\n", dice_names[game], yatzy_point);
                    }
                    else{
                        printf("---- You don't have yatzy\n");
                    }
                    break;
                default:
                    printf("error");
                    exit(EXIT_FAILURE);
            }
        }
        // totale point beregnes
        int total_points = point_sum + one_pair_sum + two_pair_sum + three_pair_sum + 
        four_pair_sum + small_straight_point + big_straight_point + house_sum + chance_point + yatzy_point;
        printf("You finished with %d total points!\n\n", total_points);
        printf("How many dices you want to throw, if you want to play again.\n");
        printf("If you want to exit, press 0.\n\n");
        game = 0;
        scanf("%d", &amount_of_dices);
    }
    while(amount_of_dices > 0);
    //befrier det allokerede hukommelse efter loopet.
    free(outcomes);
    return 0;
}

// Generer tilfældigt terningekast med øjne mellem 1-6
void roll_multiple_dice(int amount_of_dices, int *outcomes){
    int n;
    for(int i = 0; i <= amount_of_dices; ++i){
        n = (rand() % DICE_EYES) + 1;
        outcomes[i] = n;
    }
}

// Printer arrays
void dice_printer(int *array, int size){
    for(int i = 0; i < size; ++i){
        printf("%d ", array[i]);
    }
}

// Søger efter antal af specifikke øjne
int eye_occurence(int dice_amount, int *array, int eye){
    int occurences = 0;
    for(int i = 0; i < dice_amount; ++i){
        if(array[i] == eye+1){
            ++occurences;
        }
    }
    return occurences;
}

// Søger efter par på specifikke øjne
int highest_pair(int *array, int size, int amount_of_pairs){
    int pair;
    for(int i = 6; i > 0; --i){
        pair = 0;
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++pair;
            }
        }
        if(pair >= amount_of_pairs){
            return i;
        }
    }
    return 0;
}

// Finder højeste øjne med to par
int *find_two_pair(int *array, int size){
    int pair;
    int i;   // initialiserer int i her, da den ellers ikke kan findes i loop på linje 268
    static int result[2];
    result[0] = 0;
    result[1] = 0;
    for(i = 6; i > 0; --i){
        pair = 0;
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++pair;
            }
        }
        if(pair >= 2){
            result[0] = i;
            break;
        }
    }
    for(int k = i -1; k > 0; --k){
        pair = 0;
        for(int l = 0; l < size; ++l){
            if(array[l] == k){
                ++pair;
            }
        }
        if(pair >= 2){
            result[1] = k;
            return result;
        }
    }
    return result;
}

// Checker for rækkefølgen 1, 2, 3, 4, 5 og returnerer score værdi 15
int small_straight_check(int *array, int size){
    int score = 0;
    for(int i = 1; i <= 5; ++i){
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++score;
                break;
            }  
        }
        if(score == 5){
            return 15;
        }
    }
    return 0;
}

// Checker for rækkefølgen 2, 3, 4, 5, 6 og returnerer score værdi 20
int big_straight_check(int *array, int size){
    int score=0;
    for(int i = 2; i <= 6; ++i){
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++score;
                break; 
            }
        }
        if(score == 5){
            return 20;
        }
    }
    return 0;
}

// Finder summen af de 5 terninger med flest øjne i arrayet
int chance_calc(int *array, int size){
    int sum = 0;
    int eye = 0;
    for(int i = DICE_EYES; i > 0; --i){
        for(int j=0; j < size; ++j){
            if(array[j] == i){
                sum += array[j];
                ++eye;
            }
            if(eye == 5){
                return sum;
            }    
        }
    }
    return 0;
}

// Checker for om alle terninger har samme antal øjne
int yatzy_calc(int *array, int size){
    int pair = 0;
    for(int i = DICE_EYES; i > 0; --i){
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++pair;
            }
            if(pair == 5){
                return 50;
            }
        }
        pair = 0;
    }
    return 0;
}
// finder 3 af en slags og et par
int *house_calc(int *array, int size){
    int pair;
    int i;
    static int result[2];
    result[0] = 0;
    result[1] = 0;
    for(i = 6; i > 0; --i){
        pair = 0;
        for(int j = 0; j < size; ++j){
            if(array[j] == i){
                ++pair;
            }
        }
        if(pair >= 3){
            result[0] = i;
            break;
        }
    }
    for(int k = DICE_EYES; k > 0; --k){
        pair = 0;
        for(int l = 0; l < size; ++l){
            if(array[l] == k){
                ++pair;
            }
        }
        if(pair >= 2 && k != result[0]){
            result[1] = k;
            return result;
        }
    }
    return result;
} 