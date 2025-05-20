//this is a combined recipe.c + caloriecalc.c that is all cleaned up no printf scanf and ready for DLL use 
#include <stdio.h>
#include <string.h>
#include "dietplanner.h"
#include <stdbool.h>

// Sample Recipes
Recipe recipes[MAX_RECIPES];
int recipeCount = 0;

void addConnection(Recipe* a, Recipe* b) {
    a->connections[a->connectionCount++] = b;
}

void connectRecipes() {
    for (int i = 0; i < recipeCount; i++) {
        for (int j = i + 1; j < recipeCount; j++) {
            int connect = 0;

            // Match diet type
            if (strcmp(recipes[i].dietType, recipes[j].dietType) == 0)
                connect = 1;

            // Match any common ingredient
            for (int m = 0; m < recipes[i].ingredientCount && !connect; m++) {
                for (int n = 0; n < recipes[j].ingredientCount; n++) {
                    if (strcmp(recipes[i].ingredients[m], recipes[j].ingredients[n]) == 0) {
                        connect = 1;
                        break;
                    }
                }
            }

            // Match any common tag
            for (int m = 0; m < recipes[i].tagCount && !connect; m++) {
                for (int n = 0; n < recipes[j].tagCount; n++) {
                    if (strcmp(recipes[i].tags[m], recipes[j].tags[n]) == 0) {
                        connect = 1;
                        break;
                    }
                }
            }

            if (connect) {
                addConnection(&recipes[i], &recipes[j]);
                addConnection(&recipes[j], &recipes[i]);
            }
        }
    }
}

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

    connectRecipes();
}

float calculateCalories(float weight, float height, int age, char sex, const char *goal, char *dietType) {
    float calories;

    if (sex == 'M' || sex == 'm')
        calories = 10 * weight + 6.25 * height * 100 - 5 * age + 5;
    else
        calories = 10 * weight + 6.25 * height * 100 - 5 * age - 161;

    if (strcmp(goal, "bulk") == 0) {
        calories += 500;
        strcpy(dietType, "high_calorie_high_protein");
    } else if (strcmp(goal, "cut") == 0) {
        calories -= 500;
        strcpy(dietType, "low_calorie_low_carb");
    } else {
        strcpy(dietType, "balanced");
    }

    return calories;
}

int isTagRestricted(Recipe* r, char restrictions[][20], int restrictionCount) {
    for (int i = 0; i < restrictionCount; i++) {
        int found = 0;
        for (int j = 0; j < r->tagCount; j++) {
            if (strcmp(r->tags[j], restrictions[i]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) return 1;
    }
    return 0;
}

int hasAllergy(Recipe* r, char allergies[][50], int allergyCount) {
    for (int i = 0; i < r->ingredientCount; i++) {
        for (int j = 0; j < allergyCount; j++) {
            if (strcmp(r->ingredients[i], allergies[j]) == 0)
                return 1;
        }
    }
    return 0;
}

int hasIngredients(Recipe* r, char ingredients[][50], int count) {
    int matches = 0;
    for (int i = 0; i < r->ingredientCount; i++) {
        for (int j = 0; j < count; j++) {
            if (strcmp(r->ingredients[i], ingredients[j]) == 0)
                matches++;
        }
    }
    return matches;
}

void suggestRecipes(const char* dietType, char ingredients[][50], int ingredientCount,
                    char allergies[][50], int allergyCount, char restrictions[][20],
                    int restrictionCount, char resultBuffer[5000]) {
    resultBuffer[0] = '\0';

    int visited[MAX_RECIPES] = {0};
    int queue[MAX_RECIPES];
    int front = 0, rear = 0;

    // Enqueue recipes matching dietType
    for (int i = 0; i < recipeCount; i++) {
        if (strcmp(recipes[i].dietType, dietType) == 0)
            queue[rear++] = i;
    }

    while (front < rear) {
        int current = queue[front++];
        if (visited[current]) continue;
        visited[current] = 1;

        Recipe *r = &recipes[current];

        // Allergy check
        if (hasAllergy(r, allergies, allergyCount)) continue;

        // Restriction check
        if (isTagRestricted(r, restrictions, restrictionCount)) continue;

        // Ingredient availability check
        if (hasIngredients(r, ingredients, ingredientCount) == 0) continue;

        // Add to result
        strcat(resultBuffer, r->name);
        strcat(resultBuffer, "\n");

        // Enqueue connected recipes
        for (int k = 0; k < r->connectionCount; k++) {
            int idx = r->connections[k] - recipes;
            if (!visited[idx])
                queue[rear++] = idx;
        }
    }
}

