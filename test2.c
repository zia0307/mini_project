#include <stdio.h>
#include <string.h>

#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5
#define MAX_RECIPES 5
#define MAX_INGREDIENTS 10

// Recipe struct with foodType and dietType tags
typedef struct {
    char name[50];
    char ingredients[MAX_INGREDIENTS][50];
    int ingredientCount;
    char dietType[50];
    char foodType[20];
} Recipe;

// Function prototypes
void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount,
                       char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount);
void suggestRecipes(char restrictions[MAX_RESTRICTIONS][50], int restrictionCount, char *dietType);

// Sample recipes database
Recipe recipes[MAX_RECIPES] = {
    {"Grilled Tofu", {"tofu", "soy_sauce", "broccoli"}, 3, "low_calorie_low_carb", "vegan"},
    {"Chicken Salad", {"chicken", "lettuce", "olive_oil"}, 3, "low_calorie_low_carb", "halal"},
    {"Fish Curry", {"fish", "turmeric", "chili"}, 3, "balanced", "pescatarian"},
    {"Paneer Tikka", {"paneer", "yogurt", "spices"}, 3, "high_calorie_high_protein", "vegetarian"},
    {"Beef Steak", {"beef", "pepper", "salt"}, 3, "high_calorie_high_protein", "non_vegetarian"}
};

// Collect dietary restrictions
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
        printf("Enter restriction %d (e.g. vegetarian, vegan, halal, pescatarian): ", i + 1);
        scanf("%s", restrictions[i]);
    }
}

// Suggest recipes based on restrictions and diet type
void suggestRecipes(char restrictions[MAX_RESTRICTIONS][50], int restrictionCount, char *dietType) {
    printf("\nRecommended recipes for your preferences:\n");

    int isVegetarian = 0, isVegan = 0, isHalal = 0, isPescatarian = 0;
    for (int r = 0; r < restrictionCount; r++) {
        if (strcmp(restrictions[r], "vegetarian") == 0)
            isVegetarian = 1;
        else if (strcmp(restrictions[r], "vegan") == 0)
            isVegan = 1;
        else if (strcmp(restrictions[r], "halal") == 0)
            isHalal = 1;
        else if (strcmp(restrictions[r], "pescatarian") == 0)
            isPescatarian = 1;
    }

    for (int i = 0; i < MAX_RECIPES; i++) {
        // Filter by diet type
        if (strcmp(recipes[i].dietType, dietType) != 0)
            continue;

        // Filter by restrictions
        if (isVegetarian && strcmp(recipes[i].foodType, "non_vegetarian") == 0)
            continue;
        if (isVegan && (strcmp(recipes[i].foodType, "non_vegetarian") == 0 || strcmp(recipes[i].foodType, "vegetarian") == 0))
            continue;
        if (isHalal && strcmp(recipes[i].foodType, "non_vegetarian") == 0)
            continue;
        if (isPescatarian && (strcmp(recipes[i].foodType, "non_vegetarian") == 0))
            continue;

        // If it passes, display
        printf("🍽️  %s (%s)\n", recipes[i].name, recipes[i].foodType);
    }
}

// MAIN program to demo this
int main() {
    char allergies[MAX_ALLERGIES][50];
    int allergyCount;
    char restrictions[MAX_RESTRICTIONS][50];
    int restrictionCount;

    // User dietType
    char dietType[50];
    printf("Enter your target diet type (low_calorie_low_carb / high_calorie_high_protein / balanced): ");
    scanf("%s", dietType);

    getUserHealthData(allergies, &allergyCount, restrictions, &restrictionCount);
    suggestRecipes(restrictions, restrictionCount, dietType);

    return 0;
}
