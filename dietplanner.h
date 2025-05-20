#ifndef DIETPLANNER_H //this is an inclusion guard- i don't want multiple inclusions of this header file 
#define DIETPLANNER_H

#define MAX_INGREDIENTS 20
#define MAX_RECIPES 50
#define MAX_TAGS 5

typedef struct Recipe {
    char name[50];
    char ingredients[MAX_INGREDIENTS][50];
    int ingredientCount;
    char dietType[50];
    char tags[MAX_TAGS][20];
    int tagCount;
    struct Recipe* connections[MAX_RECIPES]; //these are your graph edges 
    //each node is a recipe and the edges are the connections between them
    int connectionCount;
} Recipe;

void loadSampleRecipes();
float calculateCalories(float weight, float height, int age, char sex, const char *goal, char *outDietType);
void suggestRecipes(
    const char* dietType,
    char ingredients[][50],
    int ingredientCount,
    char allergies[][50],
    int allergyCount,
    char restrictions[][20],
    int restrictionCount,
    char resultBuffer[5000] //the function will write the result here and the GUI will decode & display it
);

#endif 
