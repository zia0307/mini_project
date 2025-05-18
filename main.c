#include <stdio.h>
#include <string.h>
#include "dietplanner.h"

#define MAX_INGREDIENTS 20
#define MAX_RECIPES 10
#define MAX_ALLERGIES 10
#define MAX_TAGS 5

int main() {
    Recipe recipes[MAX_RECIPES];
    int recipeCount;

    char availableIngredients[MAX_INGREDIENTS][50];
    int availableCount;

    char allergies[MAX_ALLERGIES][50];
    int allergyCount;

    char dietType[50];

    char selectedTags[MAX_TAGS][20];
    int selectedTagCount;

    loadSampleRecipes(recipes, &recipeCount);

    printf("Welcome to the Diet Planner Recipe Suggestion System!\n");

    // Get ingredients
    getAvailableIngredients(availableIngredients, &availableCount);

    // Get allergies
    printf("\nHow many allergies do you have? ");
    scanf("%d", &allergyCount);

    for (int i = 0; i < allergyCount; i++) {
        printf("Enter allergy %d: ", i + 1);
        scanf("%s", allergies[i]);
    }

    // Get diet type
    printf("\nEnter your diet type (e.g., balanced, low_calorie_low_carb, high_calorie_high_protein): ");
    scanf("%s", dietType);

    // Get tags
    printf("\nHow many tags do you want to filter by? (e.g., vegetarian, halal) ");
    scanf("%d", &selectedTagCount);

    for (int i = 0; i < selectedTagCount; i++) {
        printf("Enter tag %d: ", i + 1);
        scanf("%s", selectedTags[i]);
    }

    // Suggest recipes
    suggestRecipes(recipes, recipeCount, availableIngredients, availableCount, 
                   allergies, allergyCount, dietType, selectedTags, selectedTagCount);

    return 0;
}