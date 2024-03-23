#include <stdio.h>
#include <stdlib.h>

void create_deck();
void print_suit(int i);
void print_number(int i);
void print_card();
void sorting();
int compare(const void *i, const void *j);

struct card_specs{
    int number;
    int suit;
    };

struct card_specs card[55]; 

int main(void){
    create_deck();
    printf("Your deck:\n");
    print_card();
    sorting();
    printf("sorted:\n");
    print_card();
    return 0;
}

// generer et deck af kort
void create_deck(){
    int card_amount = 54;
    for(int i = 0; i < 3; ++i){
        card[i].suit = 4;
    }
    for(int i = 0; i < 4; ++i){
        for(int j = 1; j < 14; ++j){
            card[card_amount].suit = i;
            card[card_amount].number = j;
            --card_amount;
        }
    }
}

//printer kulør
void print_suit(int i){
    switch(card[i].suit){
        case 0:
            printf("Clubs ");
            break;
        case 1:
            printf("Diamonds ");
            break;
        case 2:
            printf("Hearts ");
            break;
        case 3:
            printf("Spades ");
            break;
        default:
            printf("Joker\n");
            break;
    }
}

// printer kortets nummer
void print_number(int i){
    if(card[i].suit != 4){
        switch(card[i].number){
            case 10:
                printf("Jacks\n");
                break;
            case 11:
                printf("Queens\n");
                break;
            case 12:
                printf("Kings\n");
                break;
            case 13: 
                printf("Aces\n");
                break;
            default:
                printf("%d\n", card[i].number + 1);
                break;
        }
    }
}

// printer alle kort
void print_card(){
    for(int i = 0; i < (55); ++i){
        print_suit(i);
        print_number(i);
    }
    printf("\n\n");
}

// sorterer kort
void sorting(){
    qsort(card, (55), sizeof(struct card_specs), compare);
}

// compare anvendes i vores qsort i sorting funktionen
int compare(const void *i, const void *j){
    int result = 0;
    struct card_specs *card_specs1 = (struct card_specs *) i;
    struct card_specs *card_specs2 = (struct card_specs *) j;
    if(card_specs1->suit == card_specs2->suit){
        result = card_specs1->number - card_specs2->number;
    } 
    else {
        result = card_specs1->suit - card_specs2->suit;
    }
    return result;
}