#include <stdio.h>   // for printf, scanf, getchar
#include <string.h>  // for strcpy, strcmp
#include "dietplanner.h"

void getFitnessGoal(char *goal) {
    int choice;

    printf("\nWhat is your fitness goal?\n");
    printf("1. Bulk (gain weight/muscle)\n");
    printf("2. Cut (lose weight)\n");
    printf("3. Maintain current weight\n");
    printf("Enter your choice (1/2/3): ");
    
    scanf("%d", &choice);
    //while ((ch = getchar()) != '\n' && ch!=EOF);  // Clear input buffer
    fflush(stdin); //clear input buffer 

    switch (choice) {
        case 1:
            strcpy(goal, "bulk");
            break;
        case 2:
            strcpy(goal, "cut");
            break;
        case 3:
            strcpy(goal, "maintain");
            break;
        default:
            printf("Invalid choice. Defaulting to 'maintain'.\n");
            strcpy(goal, "maintain");
    }

    printf("Selected goal: %s\n", goal);
}
