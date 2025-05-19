#ifndef DIETPLANNER_H
#define DIETPLANNER_H

#define MAX_INGREDIENTS 20
#define MAX_RECIPES 10
#define MAX_TAGS 5

typedef struct {
    char name[50];
    char ingredients[MAX_INGREDIENTS][50];
    int ingredientCount;
    char dietType[50];
    char tags[MAX_TAGS][20];
    int tagCount;
} Recipe;

void loadSampleRecipes();
float calculateCalories(float weight, float height, int age, char sex, const char *goal, char *outDietType);
void suggestRecipes(const char* dietType, char ingredients[][50], int ingredientCount, char resultBuffer[5000]);

#endif

