#include <stdio.h>
#include <math.h>

#define SECS_PR_WK 604800
#define SECS_PR_DY 86400
#define SECS_PR_HR 3600
#define SECS_PR_MN 60 

int main ()
{
    int secs, mins, mins_rest, hrs, hrs_rest, days, days_rest, wks, wks_rest;
    printf("Insert amount of seconds to convert.\n");
    scanf("%d", &secs);
    
    wks = secs / SECS_PR_WK;
    wks_rest = secs % SECS_PR_WK;

    days = wks_rest / SECS_PR_DY;
    days_rest = wks_rest % SECS_PR_DY;

    hrs = days_rest / SECS_PR_HR;
    hrs_rest = days_rest % SECS_PR_HR;

    mins = hrs_rest / SECS_PR_MN;
    mins_rest = hrs_rest % SECS_PR_MN;
    
    printf("%d seconds is equal to %d weeks %d days %d hours %d minutes and %d seconds.\n", secs, wks, days, hrs, mins, mins_rest);

    return 0;
}