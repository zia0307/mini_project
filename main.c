#include <stdio.h>
#include <string.h>

// Include your custom module headers here
#include "dietplanner.h"

// Declare any needed defines
#define MAX_INGREDIENTS 20
#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5
#define MAX_RECIPES 5

// Function prototypes (or #include corresponding .h files)
void getUserInfo(float *height, float *weight, int *age, char *sex);
void getFitnessGoal(char *goal);
float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType);
void loadSampleRecipes(Recipe recipes[], int *recipeCount);
void getAvailableIngredients(char availableIngredients[MAX_INGREDIENTS][50], int *availableCount);
void suggestRecipes(Recipe recipes[], int recipeCount, char availableIngredients[MAX_INGREDIENTS][50],
                    int availableCount, char allergies[MAX_ALLERGIES][50], int allergyCount, char dietType[50]);

int main() {
    float height, weight;
    int age;
    char sex;
    char goal[20];
    char dietType[50];

    // User info
    getUserInfo(&height, &weight, &age, &sex);

    // Health data
    char allergies[MAX_ALLERGIES][50];
    char restrictions[MAX_RESTRICTIONS][50];
    int allergyCount = 0, restrictionCount = 0;
    getUserHealthData(allergies, &allergyCount, restrictions, &restrictionCount);

    // Fitness goal
    getFitnessGoal(goal);

    // Calorie calculation & diet type
    float calories = calculateCalories(weight, height, age, sex, goal, dietType);
    printf("\nDaily Caloric Requirement: %.2f kcal\n", calories);
    printf("Recommended Diet Type: %s\n", dietType);

    // Load recipes
    Recipe recipes[MAX_RECIPES];
    int recipeCount;
    loadSampleRecipes(recipes, &recipeCount);

    // Available ingredients
    char availableIngredients[MAX_INGREDIENTS][50];
    int availableCount = 0;
    getAvailableIngredients(availableIngredients, &availableCount);

    // Suggest recipes
    suggestRecipes(recipes, recipeCount, availableIngredients, availableCount, allergies, allergyCount, dietType);

    return 0;
}
