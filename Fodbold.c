#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AMOUNT_OF_TEAMS 12
#define AMOUNT_OF_GAMES 132

typedef struct{ // struct for each team
    char team_name[4];
    int point;
    int goals;
    int opponent_goals;
    int goal_diff;
} team;

typedef struct{ // struct for each game
    char week_day[100];
    char date[100];
    char time[100];
    char team1[100];
    char team2[100];
    int team1_score;
    int team2_score;
    int spectators;
} game;

void find_teams_data(game games[], team teams[]); // collecting all team data functions
void find_team_names(game games[], team teams[]); // saving team names from game array of structs, to team array of structs
int team_exists(team teams[], char team_name[]); // returning either 1 or 0 if team is already present in team array of structs
void find_goals_scored(game games[], team teams[]); // finding goals scored for each team
void find_total_points(game games[], team teams[]); // finding points for each team
void goal_difference(team teams[]); // calculating goal difference for each team
void sort_scores(team teams[]); // sorting the scores from high to low
int compare(const void *i, const void *j); // comapre for sorting function
void print_titles(); // printing the titles of the columns in the terminal
void print_game_data(team teams[]); // printing the team data

int main (void){
    team teams[AMOUNT_OF_TEAMS]; // creating array of structs for 12 teams
    game games[AMOUNT_OF_GAMES]; // creating array of structs for 132 teams
    int i = 0;

    FILE *fptr = fopen("kampe-2020-2021.txt", "r"); //command to read from file
    if(fptr == NULL){
        printf("Error: could not find file\n");
        exit(EXIT_FAILURE);
    }

    while (EOF != fscanf(fptr, " %s %s %s %s %*[-] %s %d %*[-] %d %d", // scanning from the files, and saving to games array of structs
    games[i].week_day, games[i].date, games[i].time, games[i].team1, games[i].team2, &games[i].team1_score, &games[i].team2_score, &games[i].spectators))
    {
        ++i;
    }
    
    find_teams_data(games, teams);
    print_titles();
    print_game_data(teams);
    fclose(fptr); // closing the file
    return 0;
}

void find_teams_data(game games[], team teams[]){ // all functions finding data gathered in one function
    find_team_names(games, teams);
    find_goals_scored(games, teams);
    find_total_points(games, teams);
    goal_difference(teams);
    sort_scores(teams);
}

void find_team_names(game games[], team teams[]){ // finding team names
    int j = 0;
    for(int i = 0; i < AMOUNT_OF_GAMES; ++i){
        if(team_exists(teams, games[i].team1) == 0){ //if team exist, it will return 1, so when if-statement == 0 then team is not present
            strcpy(teams[j].team_name, games[i].team1); // copy from games team name 1 to teams if not is not already present
            ++j;
        }
        if(team_exists(teams, games[i].team2) == 0){  // same as before, except checking for team 2
            strcpy(teams[j].team_name, games[i].team2); // same as before, except copying from games team name 2 to teams team2
            ++j;
        }
    }
}

void find_goals_scored(game games[], team teams[]){ // finding amount of goals scored
    for(int k = 0; k < AMOUNT_OF_TEAMS; ++k){ // first setting all goals, points and opponent goals to zero to avoid incorrect values
        teams[k].goals = 0;
        teams[k].point = 0;
        teams[k].opponent_goals = 0;
    }

    for(int j = 0; j < AMOUNT_OF_TEAMS; ++j){
        for(int i = 0; i < AMOUNT_OF_GAMES; ++i){
            if(strcmp(teams[j].team_name, games[i].team1) == 0){ // adding goals for each team
                teams[j].goals += games[i].team1_score;
                teams[j].opponent_goals += games[i].team2_score;
            }
            if(strcmp(teams[j].team_name, games[i].team2) == 0){ // adding opponent goals for each team
                teams[j].goals += games[i].team2_score;
                teams[j].opponent_goals += games[i].team1_score;
            }
        }
    }
}

int team_exists(team teams[], char team_name[]){ // returning 1 if team is already present in array
    for(int i = 0; i < AMOUNT_OF_TEAMS; ++i){
        if(strcmp(team_name, teams[i].team_name) == 0){
            return 1;
        }
    }
    return 0; // returning 0 if not present
}

void find_total_points(game games[], team teams[]){ // finding total points
    for(int j = 0; j < AMOUNT_OF_TEAMS; ++j){
        for(int i = 0; i < AMOUNT_OF_GAMES; ++i){
            if(strcmp(teams[j].team_name, games[i].team1) == 0){
                if(games[i].team1_score > games[i].team2_score){
                    teams[j].point += 3; // team 1 has more goals add 3 points
                }
                else if(games[i].team1_score == games[i].team2_score){
                    teams[j].point += 1; // if team1 and team2 has equal points, add 1
                }
            }
            if(strcmp(teams[j].team_name, games[i].team2) == 0){ // same as above, just for team2
                if(games[i].team2_score > games[i].team1_score){
                    teams[j].point += 3;
                }
                else if(games[i].team1_score == games[i].team2_score){
                    teams[j].point += 1;
                }
            }
        }
    }
}

void goal_difference(team teams[]){ //finding goals difference, by dividing goals and opponent goals and saving to goal_diff
    for(int i = 0; i < AMOUNT_OF_TEAMS; ++i){
        teams[i].goal_diff = (teams[i].goals - teams[i].opponent_goals);
    }
}

void sort_scores(team teams[]){ // function to sort results
    qsort(teams, AMOUNT_OF_TEAMS, sizeof(team), compare);
}

int compare(const void *i, const void *j){ // compare function to use with qsort to sort results
    int result = 0;
    team *team1 = (team *) i;
    team *team2 = (team *) j;
    if(team2->point != team1->point){
        result = team2->point - team1->point;
    } else {
        result = team2->goals - team1->goals;
    }
    return result;
}

void print_titles(){ // printing titles with beautifully aligned columns
    char name[10] = "TEAM:";
    char point[10] = "POINTS:";
    char goals[20] = "GOALS MADE:";
    char opp_goals[10] = "GOALS AT:";
    char goal_diff[20] = "GOAL DIFFERENCE:";
    printf("%-12s", name);
    printf("%-12s", point);
    printf("%-12s", goals);
    printf("%-12s", opp_goals);
    printf("%-12s\n", goal_diff);
}

void print_game_data(team teams[]){ // printing results with equally as beautifully aligned columns
    for(int i = 0; i < AMOUNT_OF_TEAMS; ++i){
        printf("%-11s ", teams[i].team_name);
        printf("%-11d ", teams[i].point);
        printf("%-11d ", teams[i].goals);
        printf("%-11d ", teams[i].opponent_goals);
        printf("%-11d\n", teams[i].goal_diff);
    }
}