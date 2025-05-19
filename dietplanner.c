//this is a combined recipe.c + caloriecalc.c that is all cleaned up no printf scanf and ready for DLL use 
#include <stdio.h>
#include <string.h>
#include "dietplanner.h"

// Sample Recipes (global for simplicity)
Recipe recipes[MAX_RECIPES];
int recipeCount = 0;

void loadSampleRecipes() {
    recipeCount = 7;

    // Recipe 1
    strcpy(recipes[0].name, "Oatmeal with Fruits");
    recipes[0].ingredientCount = 3;
    strcpy(recipes[0].ingredients[0], "oats");
    strcpy(recipes[0].ingredients[1], "milk");
    strcpy(recipes[0].ingredients[2], "banana");
    strcpy(recipes[0].dietType, "balanced");
    recipes[0].tagCount = 2;
    strcpy(recipes[0].tags[0], "vegetarian");
    strcpy(recipes[0].tags[1], "halal");

    // Recipe 2
    strcpy(recipes[1].name, "Grilled Chicken Salad");
    recipes[1].ingredientCount = 4;
    strcpy(recipes[1].ingredients[0], "chicken");
    strcpy(recipes[1].ingredients[1], "lettuce");
    strcpy(recipes[1].ingredients[2], "olive oil");
    strcpy(recipes[1].ingredients[3], "lemon");
    strcpy(recipes[1].dietType, "low_calorie_low_carb");
    recipes[1].tagCount = 1;
    strcpy(recipes[1].tags[0], "halal");

    // Recipe 3
    strcpy(recipes[2].name, "Protein Shake");
    recipes[2].ingredientCount = 3;
    strcpy(recipes[2].ingredients[0], "protein powder");
    strcpy(recipes[2].ingredients[1], "milk");
    strcpy(recipes[2].ingredients[2], "banana");
    strcpy(recipes[2].dietType, "high_calorie_high_protein");
    recipes[2].tagCount = 2;
    strcpy(recipes[2].tags[0], "vegetarian");
    strcpy(recipes[2].tags[1], "halal");

    // Recipe 4
    strcpy(recipes[3].name, "Veggie Burger");
    recipes[3].ingredientCount = 4;
    strcpy(recipes[3].ingredients[0], "veggie patty");
    strcpy(recipes[3].ingredients[1], "bun");
    strcpy(recipes[3].ingredients[2], "lettuce");
    strcpy(recipes[3].ingredients[3], "tomato");
    strcpy(recipes[3].dietType, "balanced");
    recipes[3].tagCount = 2;
    strcpy(recipes[3].tags[0], "vegetarian");
    strcpy(recipes[3].tags[1], "halal");
    strcpy(recipes[3].tags[2], "vegan");

    // Recipe 5
    strcpy(recipes[4].name, "Chicken Fajitas");
    recipes[4].ingredientCount = 4;
    strcpy(recipes[4].ingredients[0], "chicken");
    strcpy(recipes[4].ingredients[1], "bell peppers");
    strcpy(recipes[4].ingredients[2], "onion");
    strcpy(recipes[4].ingredients[3], "fajita seasoning");
    strcpy(recipes[4].dietType, "low_calorie_low_carb");
    recipes[4].tagCount = 1;
    strcpy(recipes[4].tags[0], "halal");

    // Recipe 6
    strcpy(recipes[5].name, "Paneer Tikka");
    recipes[5].ingredientCount = 3;
    strcpy(recipes[5].ingredients[0], "paneer");
    strcpy(recipes[5].ingredients[1], "yogurt");
    strcpy(recipes[5].ingredients[2], "spices");
    strcpy(recipes[5].dietType, "high_calorie_high_protein");
    recipes[5].tagCount = 1;
    strcpy(recipes[5].tags[0], "vegetarian");
    strcpy(recipes[5].tags[1], "halal");

    // Recipe 7
    strcpy(recipes[6].name, "Mango Lassi");
    recipes[6].ingredientCount = 3;
    strcpy(recipes[6].ingredients[0], "mangoes");
    strcpy(recipes[6].ingredients[1], "yogurt");
    strcpy(recipes[6].ingredients[2], "honey");
    strcpy(recipes[6].dietType, "high_calorie_high_protein");
    recipes[6].tagCount = 1;
    strcpy(recipes[6].tags[0], "vegetarian");
}

float calculateCalories(float weight, float height, int age, char sex, const char* goal, char* outDietType) {
    float bmr;
    if (sex == 'M' || sex == 'm') {
        bmr = 10 * weight + 6.25 * (height * 100) - 5 * age + 5;
    } else {
        bmr = 10 * weight + 6.25 * (height * 100) - 5 * age - 161;
    }

    if (strcmp(goal, "bulk") == 0) {
        strcpy(outDietType, "high_calorie_high_protein");
        return bmr + 500;
    } else if (strcmp(goal, "cut") == 0) {
        strcpy(outDietType, "low_calorie_low_carb");
        return bmr - 500;
    } else {
        strcpy(outDietType, "balanced");
        return bmr;
    }
}

void suggestRecipes(const char* dietType, char ingredients[][50], int ingredientCount, char resultBuffer[5000]) {
    char result[5000] = "";
    int found = 0;

    for (int i = 0; i < recipeCount; i++) {
        if (strcmp(recipes[i].dietType, dietType) != 0)
            continue;

        int matchCount = 0;
        for (int j = 0; j < recipes[i].ingredientCount; j++) {
            for (int k = 0; k < ingredientCount; k++) {
                if (strcmp(recipes[i].ingredients[j], ingredients[k]) == 0) {
                    matchCount++;
                    break;
                }
            }
        }

        float matchRatio = (float)matchCount / recipes[i].ingredientCount;
        if (matchRatio >= 0.7) {
            strcat(result, recipes[i].name);
            strcat(result, "\n");
            found = 1;
        }
    }

    if (!found) {
        strcpy(result, "No matching recipes found.\n");
    }

    strcpy(resultBuffer, result);
}
