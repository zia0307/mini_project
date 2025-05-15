//smol code
#include <stdio.h>
#include <string.h>

#define MAX_INGREDIENTS 5
#define MAX_RECIPES 3

// Ingredient list
char ingredients[MAX_INGREDIENTS][20] = {"eggs", "bread", "milk", "cheese", "chicken"};

// Recipe struct
typedef struct recipe{
    char name[50];
    char requiredIngredients[5][20];
    int ingredientCount;
} Recipe;

// Recipes
Recipe recipes[MAX_RECIPES] = {
    {"Scrambled Eggs", {"eggs", "milk"}, 2},
    {"Grilled Cheese", {"bread", "cheese"}, 2},
    {"Chicken Sandwich", {"chicken", "bread"}, 2}
};

// Check if user has all required ingredients for a recipe
int canMakeRecipe(Recipe recipe, char userIngredients[5][20], int userCount) {
    int found;
    for (int i = 0; i < recipe.ingredientCount; i++) {
        found = 0;
        for (int j = 0; j < userCount; j++) {
            if (strcmp(recipe.requiredIngredients[i], userIngredients[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

int main() {
    int userCount;
    char userIngredients[5][20];

    printf("How many ingredients do you have? (max 5): ");
    scanf("%d", &userCount);

    for (int i = 0; i < userCount; i++) {
        printf("Enter ingredient %d: ", i + 1);
        scanf("%s", userIngredients[i]);
    }

    printf("\nYou can make:\n");

    int possible = 0;
    for (int i = 0; i < MAX_RECIPES; i++) {
        if (canMakeRecipe(recipes[i], userIngredients, userCount)) {
            printf("- %s\n", recipes[i].name);
            possible = 1;
        }
    }

    if (!possible) {
        printf("Sorry, no recipes match your ingredients.\n");
    }

    return 0;
}