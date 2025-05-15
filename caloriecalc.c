#include <stdio.h>   // for printf, scanf, getchar
#include <string.h>  // for strcpy, strcmp
#include "dietplanner.h"

float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType) {
    float bmr;

    // Convert height to cm
    height = height * 100;

    if (sex == 'M' || sex == 'm') {
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    } else {
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;
    }

    float maintenanceCalories = bmr * 1.2; // Sedentary activity level

    float finalCalories;


    if (strcmp(goal, "bulk") == 0) {
        finalCalories = maintenanceCalories + 500;
        strcpy(dietType, "high_calorie_high_protein");
    } else if (strcmp(goal, "cut") == 0) {
        finalCalories = maintenanceCalories - 500;
        strcpy(dietType, "low_calorie_low_carb");
    } else {
        finalCalories = maintenanceCalories;
        strcpy(dietType, "balanced");
    }

    return finalCalories;
}