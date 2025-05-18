#include "dietplanner.h"

#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

DLL_EXPORT float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType) {
    float calories;

    if (sex == 'M' || sex == 'm') {
        calories = 10 * weight + 6.25 * height * 100 - 5 * age + 5;
    } else {
        calories = 10 * weight + 6.25 * height * 100 - 5 * age - 161;
    }

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
