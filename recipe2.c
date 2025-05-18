#include <stdio.h>
#include <string.h>
#include "dietplanner.h"

#define MAX_INGREDIENTS 20
#define MAX_RECIPES 10

void loadSampleRecipes(Recipe recipes[], int *recipeCount) {
    *recipeCount = 3; // total number of recipes added

    // Recipe 1
    strcpy(recipes[0].name, "Oatmeal with Fruits");
    recipes[0].ingredientCount = 3;
    strcpy(recipes[5].foodType, "vegetarian");
    strcpy(recipes[0].ingredients[0], "oats");
    strcpy(recipes[0].ingredients[1], "milk");
    strcpy(recipes[0].ingredients[2], "banana");
    strcpy(recipes[0].dietType, "balanced");

    // Recipe 2
    strcpy(recipes[1].name, "Grilled Chicken Salad");
    recipes[1].ingredientCount = 4;
    strcpy(recipes[1].foodType, "halal");
    strcpy(recipes[1].ingredients[0], "chicken");
    strcpy(recipes[1].ingredients[1], "lettuce");
    strcpy(recipes[1].ingredients[2], "olive oil");
    strcpy(recipes[1].ingredients[3], "lemon");
    strcpy(recipes[1].dietType, "low_calorie_low_carb");

    // Recipe 3
    strcpy(recipes[2].name, "Protein Shake");
    recipes[2].ingredientCount = 3;
    strcpy(recipes[2].foodType, "vegetarian");
    strcpy(recipes[2].ingredients[0], "protein powder");
    strcpy(recipes[2].ingredients[1], "milk");
    strcpy(recipes[2].ingredients[2], "banana");
    strcpy(recipes[2].dietType, "high_calorie_high_protein");

    //Recipe 4 
    strcpy(recipes[3].name, "Veggie Burger");
    strcpy(recipes[3].foodType, "vegetarian");
    recipes[3].ingredientCount = 4;
    strcpy(recipes[3].ingredients[0], "veggie patty");
    strcpy(recipes[3].ingredients[1], "bun");
    strcpy(recipes[3].ingredients[2], "lettuce");
    strcpy(recipes[3].ingredients[3], "tomato");
    strcpy(recipes[3].dietType, "balanced");

    //Recipe 5
    strcpy(recipes[4].name, "Chicken Fajitas");
    strcpy(recipes[5].foodType, "halal");
    recipes[4].ingredientCount = 4;
    strcpy(recipes[4].ingredients[0], "chicken");
    strcpy(recipes[4].ingredients[1], "bell peppers");
    strcpy(recipes[4].ingredients[2], "onion");
    strcpy(recipes[4].ingredients[3], "fajita seasoning");
    strcpy(recipes[4].dietType, "low_calorie_low_carb");

    //Recipe 6 
    strcpy(recipes[5].name, "Paneer Tikka");
    strcpy(recipes[5].dietType, "high_calorie_high_protein");
    strcpy(recipes[5].foodType, "vegetarian");
    recipes[0].ingredientCount = 3;
    strcpy(recipes[5].ingredients[0], "paneer");
    strcpy(recipes[5].ingredients[1], "yogurt");
    strcpy(recipes[5].ingredients[2], "spices");


}

void suggestRecipes(Recipe recipes[], int recipeCount, char availableIngredients[][50], int availableCount, 
                    char allergies[][50], int allergyCount, char dietType[50]) {
    printf("\n--- Suggested Recipes ---\n");
    int found = 0;
    float threshold = 0.7;  // 70% ingredients match threshold

    for (int i = 0; i < recipeCount; i++) {
        // Check if diet type matches
        if (strcmp(recipes[i].dietType, dietType) != 0)
            continue;

        int matchingIngredients = 0;
        int totalIngredients = recipes[i].ingredientCount;
        int allergic = 0;

        for (int j = 0; j < totalIngredients; j++) {
            // Check allergy first
            for (int m = 0; m < allergyCount; m++) {
                if (strcmp(recipes[i].ingredients[j], allergies[m]) == 0) {
                    allergic = 1;
                    break;
                }
            }
            if (allergic) break;

            // Check if ingredient is available
            for (int k = 0; k < availableCount; k++) {
                if (strcmp(recipes[i].ingredients[j], availableIngredients[k]) == 0) {
                    matchingIngredients++;
                    break;
                }
            }
        }

        if (!allergic && ((float)matchingIngredients / totalIngredients) >= threshold) {
            printf("- %s (You have %d of %d ingredients)\n", recipes[i].name, matchingIngredients, totalIngredients);
            found = 1;
        }
    }

    if (!found)
        printf("No recipes available based on your ingredients, allergies, and diet plan.\n");
}

void getAvailableIngredients(char availableIngredients[MAX_INGREDIENTS][50], int *availableCount) {
    printf("\nHow many ingredients do you have available? ");
    scanf("%d", availableCount);

    for (int i = 0; i < *availableCount; i++) {
        printf("Enter ingredient %d: ", i + 1);
        scanf("%s", availableIngredients[i]);
    }
}
