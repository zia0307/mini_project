#include <stdio.h>   // for printf, scanf, getchar
#include <string.h>  // for strcpy, strcmp
#include "dietplanner.h"

void getUserInfo(float *height, float *weight, int *age, char *sex) {
    printf("Enter your height (in meters): ");
    scanf("%f", height);

    if (*height <= 0) {
    printf("Bro has negative height. Please restart and enter a valid value.\n");
    return;
    }

    printf("Enter your weight (in kilograms): ");
    scanf("%f", weight);

    if (*weight <= 0) {
    printf("Bro does not exist. Please restart and enter a valid value.\n");
    return;
    }

    printf("Enter your age: ");
    scanf("%d", age);

    printf("Enter your sex (M/F): ");
    scanf(" %c", sex); 

    float bmi = *weight / ((*height) * (*height));
    printf("Your BMI is: %.2f\n", bmi);
    if (bmi < 18.5)
        printf("It seems that you are underweight. We can help you fix that!\n");
    else if (bmi < 25)
        printf("You're healthy! We can help you maintain that!'\n");
    else if (bmi > 25 && bmi < 30)
        printf("It seems that you are overweight :( No worries, we can help!\n");
    else if (bmi > 30)
        printf("Uh oh! You are obese. But it's never too late :)\n");
    else
        printf("Please enter valid inputs.");
}


