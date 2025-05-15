#include <stdio.h>
#include <string.h>

#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5
#define MAX_INGREDIENTS 10
#define MAX_RECIPES 5

// ---------- STRUCT FOR RECIPE ----------
typedef struct {
    char name[50];
    char dietType[50];
    char foodType[50];
    char ingredients[MAX_INGREDIENTS][50];
    int ingredientCount;
} Recipe;

// ---------- FUNCTION PROTOTYPES ----------
float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType);
void getUserInfo(float *height, float *weight, int *age, char *sex);
void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount, char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount);
void getFitnessGoal(char *goal);
float calculateBMI(float weight, float height);
void getUserIngredients(char ingredients[MAX_INGREDIENTS][50], int *ingredientCount);
int hasAllIngredients(Recipe recipe, char userIngredients[MAX_INGREDIENTS][50], int userIngredientCount);
void suggestRecipes(Recipe recipes[MAX_RECIPES], int recipeCount, char *dietType, char restrictions[MAX_RESTRICTIONS][50], int restrictionCount, char userIngredients[MAX_INGREDIENTS][50], int userIngredientCount);

// ---------- MAIN ----------
int main() {
    // User data
    float height, weight;
    int age;
    char sex;

    getUserInfo(&height, &weight, &age, &sex);

    char allergies[MAX_ALLERGIES][50];
    int allergyCount;
    char restrictions[MAX_RESTRICTIONS][50];
    int restrictionCount;

    getUserHealthData(allergies, &allergyCount, restrictions, &restrictionCount);

    char goal[20];
    getFitnessGoal(goal);

    char dietType[50];
    float calorieTarget = calculateCalories(weight, height, age, sex, goal, dietType);

    printf("\nYour daily calorie target: %.0f calories\n", calorieTarget);
    printf("Recommended diet type: %s\n", dietType);

    // User Ingredients
    char userIngredients[MAX_INGREDIENTS][50];
    int userIngredientCount;
    getUserIngredients(userIngredients, &userIngredientCount);

    // Recipes
    Recipe recipes[MAX_RECIPES];

    strcpy(recipes[0].name, "Paneer Tikka");
    strcpy(recipes[0].dietType, "high_calorie_high_protein");
    strcpy(recipes[0].foodType, "vegetarian");
    recipes[0].ingredientCount = 3;
    strcpy(recipes[0].ingredients[0], "paneer");
    strcpy(recipes[0].ingredients[1], "yogurt");
    strcpy(recipes[0].ingredients[2], "spices");

    strcpy(recipes[1].name, "Grilled Chicken Salad");
    strcpy(recipes[1].dietType, "low_calorie_low_carb");
    strcpy(recipes[1].foodType, "halal");
    recipes[1].ingredientCount = 3;
    strcpy(recipes[1].ingredients[0], "chicken");
    strcpy(recipes[1].ingredients[1], "lettuce");
    strcpy(recipes[1].ingredients[2], "olive_oil");

    int recipeCount = 2;

    // Suggest recipes
    suggestRecipes(recipes, recipeCount, dietType, restrictions, restrictionCount, userIngredients, userIngredientCount);

    return 0;
}

// ---------- FUNCTION DEFINITIONS ----------
float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType) {
    float bmr;
    height = height * 100;
    if (sex == 'M' || sex == 'm') {
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    } else {
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;
    }
    float maintenanceCalories = bmr * 1.2;
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

void getUserInfo(float *height, float *weight, int *age, char *sex) {
    printf("Enter your height (in meters): ");
    scanf("%f", height);
    printf("Enter your weight (in kilograms): ");
    scanf("%f", weight);
    printf("Enter your age: ");
    scanf("%d", age);
    printf("Enter your sex (M/F): ");
    scanf(" %c", sex);

    float bmi = *weight / ((*height) * (*height));
    printf("Your BMI is: %.2f\n", bmi);
    if (bmi < 18.5)
        printf("You are underweight.\n");
    else if (bmi < 25)
        printf("Healthy weight.\n");
    else if (bmi < 30)
        printf("Overweight.\n");
    else
        printf("Obese.\n");
}

void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount, char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount) {
    printf("\nHow many allergies do you have? ");
    scanf("%d", allergyCount);
    for (int i = 0; i < *allergyCount; i++) {
        printf("Enter allergy %d: ", i + 1);
        scanf("%s", allergies[i]);
    }
    printf("\nHow many dietary restrictions? (vegetarian, vegan, halal, pescatarian): ");
    scanf("%d", restrictionCount);
    for (int i = 0; i < *restrictionCount; i++) {
        printf("Enter restriction %d: ", i + 1);
        scanf("%s", restrictions[i]);
    }
}

void getFitnessGoal(char *goal) {
    int choice;
    printf("\nWhat's your fitness goal?\n1. Bulk\n2. Cut\n3. Maintain\nEnter choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: strcpy(goal, "bulk"); break;
        case 2: strcpy(goal, "cut"); break;
        case 3: strcpy(goal, "maintain"); break;
        default: printf("Invalid, defaulting to maintain.\n"); strcpy(goal, "maintain");
    }
}

void getUserIngredients(char ingredients[MAX_INGREDIENTS][50], int *ingredientCount) {
    printf("\nHow many ingredients do you have? ");
    scanf("%d", ingredientCount);
    for (int i = 0; i < *ingredientCount; i++) {
        printf("Enter ingredient %d: ", i + 1);
        scanf("%s", ingredients[i]);
    }
}

int hasAllIngredients(Recipe recipe, char userIngredients[MAX_INGREDIENTS][50], int userIngredientCount) {
    int found;
    for (int i = 0; i < recipe.ingredientCount; i++) {
        found = 0;
        for (int j = 0; j < userIngredientCount; j++) {
            if (strcmp(recipe.ingredients[i], userIngredients[j]) == 0) {
                found = 1;
                break;
            }
        }
        if (!found) return 0;
    }
    return 1;
}

void suggestRecipes(Recipe recipes[MAX_RECIPES], int recipeCount, char *dietType, char restrictions[MAX_RESTRICTIONS][50], int restrictionCount, char userIngredients[MAX_INGREDIENTS][50], int userIngredientCount) {
    printf("\n--- Recommended Recipes ---\n");
    int foundRecipe = 0;
    for (int i = 0; i < recipeCount; i++) {
        if (strcmp(recipes[i].dietType, dietType) != 0) continue;
        int skip = 0;
        for (int r = 0; r < restrictionCount; r++) {
            if (strcmp(recipes[i].foodType, restrictions[r]) == 0) {
                skip = 1;
                break;
            }
        }
        if (skip) continue;
        if (hasAllIngredients(recipes[i], userIngredients, userIngredientCount)) {
            printf("-> %s\n", recipes[i].name);
            foundRecipe = 1;
        }
    }
    if (!foundRecipe)
        printf("No recipes found matching your ingredients and preferences.\n");
}
