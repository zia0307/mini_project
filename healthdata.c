#include <stdio.h>
#include <string.h>
#include "dietplanner.h"
#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5

void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount,
    char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount) {

printf("\nDo you have any allergies? (enter number): ");
scanf("%d", allergyCount);

for (int i = 0; i < *allergyCount; i++) {
printf("Enter allergy %d: ", i + 1);
scanf("%s", allergies[i]);
}

printf("\nDo you have any dietary restrictions or medical conditions? (enter number): ");
scanf("%d", restrictionCount);

for (int i = 0; i < *restrictionCount; i++) {
printf("Enter restriction %d (enter vegetarian, diabetic, halal, vegan, gluten-free): ", i + 1);
scanf("%s", restrictions[i]);
}
}
