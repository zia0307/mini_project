#include <stdio.h>
#include <string.h>

#define MAX_ALLERGIES 5
#define MAX_RESTRICTIONS 5
#define MAX_INGREDIENTS 20
#define MAX_RECIPES 10

// Structure for Recipe Node
typedef struct {
    char name[50];
    char ingredients[10][50];
    int ingredientCount;
    char dietTag[50]; // e.g. "high_calorie_high_protein", "low_calorie_low_carb"
} Recipe;

// Function to calculate BMI
float calculateBMI(float weight, float height) {
    return weight / (height * height);
}

// Function to get user info and calculate BMI
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

// Function to get allergies and restrictions
void getUserHealthData(char allergies[MAX_ALLERGIES][50], int *allergyCount,
                       char restrictions[MAX_RESTRICTIONS][50], int *restrictionCount) {

    printf("\nHow many allergies do you have? ");
    scanf("%d", allergyCount);
    for (int i = 0; i < *allergyCount; i++) {
        printf("Enter allergy %d: ", i + 1);
        scanf("%s", allergies[i]);
    }

    printf("\nHow many dietary restrictions/medical conditions? ");
    scanf("%d", restrictionCount);
    for (int i = 0; i < *restrictionCount; i++) {
        printf("Enter restriction %d: ", i + 1);
        scanf("%s", restrictions[i]);
    }
}

// Function to get fitness goal
void getFitnessGoal(char *goal) {
    int choice;
    printf("\nChoose your fitness goal:\n");
    printf("1. Bulk\n2. Cut\n3. Maintain\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: strcpy(goal, "bulk"); break;
        case 2: strcpy(goal, "cut"); break;
        case 3: strcpy(goal, "maintain"); break;
        default: strcpy(goal, "maintain"); break;
    }
}

// Function to calculate daily calorie needs using Harris-Benedict
float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType) {
    float bmr;
    height = height * 100; // Convert m to cm

    if (sex == 'M' || sex == 'm')
        bmr = 10 * weight + 6.25 * height - 5 * age + 5;
    else
        bmr = 10 * weight + 6.25 * height - 5 * age - 161;

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

// Function to get available ingredients from user
void getAvailableIngredients(char availableIngredients[MAX_INGREDIENTS][50], int *availableCount) {
    printf("\nHow many ingredients do you have available? ");
    scanf("%d", availableCount);
    for (int i = 0; i < *availableCount; i++) {
        printf("Enter ingredient %d: ", i + 1);
        scanf("%s", availableIngredients[i]);
    }
}

// Function to suggest recipes based on available ingredients and diet type
void suggestRecipes(Recipe recipes[], int recipeCount, char availableIngredients[MAX_INGREDIENTS][50],
                    int availableCount, char allergies[MAX_ALLERGIES][50], int allergyCount, char *dietType) {
    printf("\nRecommended Recipes for you:\n");

    for (int i = 0; i < recipeCount; i++) {
        // Check diet type match
        if (strcmp(recipes[i].dietTag, dietType) != 0)
            continue;

        int matchCount = 0, allergic = 0;

        for (int j = 0; j < recipes[i].ingredientCount; j++) {
            // Check for allergy
            for (int a = 0; a < allergyCount; a++) {
                if (strcmp(recipes[i].ingredients[j], allergies[a]) == 0) {
                    allergic = 1;
                    break;
                }
            }
            if (allergic)
                break;

            // Check if user has ingredient
            for (int k = 0; k < availableCount; k++) {
                if (strcmp(recipes[i].ingredients[j], availableIngredients[k]) == 0) {
                    matchCount++;
                    break;
                }
            }
        }

        if (!allergic && matchCount == recipes[i].ingredientCount) {
            printf("- %s\n", recipes[i].name);
        }
    }
}

// MAIN FUNCTION
int main() {
    float height, weight;
    int age;
    char sex;

    // Step 1: Get User Info
    getUserInfo(&height, &weight, &age, &sex);

    // Step 2: Get Health Data
    char allergies[MAX_ALLERGIES][50];
    int allergyCount;
    char restrictions[MAX_RESTRICTIONS][50];
    int restrictionCount;
    getUserHealthData(allergies, &allergyCount, restrictions, &restrictionCount);

    // Step 3: Get Fitness Goal
    char goal[20];
    getFitnessGoal(goal);

    // Step 4: Calculate Calories & Diet Type
    char dietType[50];
    float calorieTarget = calculateCalories(weight, height, age, sex, goal, dietType);
    printf("\nDaily Calorie Target: %.2f kcal\n", calorieTarget);
    printf("Diet Type: %s\n", dietType);

    // Step 5: Get Available Ingredients
    char availableIngredients[MAX_INGREDIENTS][50];
    int availableCount;
    getAvailableIngredients(availableIngredients, &availableCount);

    // Step 6: Define Recipes
    Recipe recipes[MAX_RECIPES] = {
        {"Chicken Salad", {"chicken", "lettuce", "olive_oil"}, 3, "low_calorie_low_carb"},
        {"Peanut Butter Shake", {"peanut butter", "milk", "banana"}, 3, "high_calorie_high_protein"},
        {"Fruit Bowl", {"apple", "banana", "orange"}, 3, "balanced"},
        {"Grilled Tofu", {"tofu", "soy_sauce", "broccoli"}, 3, "low_calorie_low_carb"},
        {"Oats Porridge", {"oats", "milk", "honey"}, 3, "balanced"}
    };

    // Step 7: Suggest Recipes
    suggestRecipes(recipes, 5, availableIngredients, availableCount, allergies, allergyCount, dietType);

    return 0;
}
