#ifndef DIETPLANNER_H
#define DIETPLANNER_H

#include <stdio.h>
#include <string.h>

// Constants
#define MAX_INGREDIENTS 20
#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5
#define MAX_RECIPES 5
#define MAX_TAGS 5

// Recipe struct
typedef struct {
    char name[50];
    char ingredients[MAX_INGREDIENTS][50];
    int ingredientCount;
    char dietType[50];
    char tags[MAX_TAGS][20];
    int tagCount;
} Recipe;


// Function declarations

// User info
void getUserInfo(float *height, float *weight, int *age, char *sex);

// Health data
void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount,
                       char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount);

// Fitness goal
void getFitnessGoal(char *goal);

// Calorie calculation
float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType);

// Recipe management
void loadSampleRecipes(Recipe recipes[], int *recipeCount);
void getAvailableIngredients(char availableIngredients[MAX_INGREDIENTS][50], int *availableCount);
void suggestRecipes(Recipe recipes[], int recipeCount, char availableIngredients[][50], int availableCount, 
                    char allergies[][50], int allergyCount, char dietType[50], char selectedTags[][20], int selectedTagCount);

#endif // DIETPLANNER_H
