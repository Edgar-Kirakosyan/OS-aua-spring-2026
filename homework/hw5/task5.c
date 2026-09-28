#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    float highest, lowest;
    float *grades;

    printf("How many students are in the class? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of students must be greater than 0\n");
        return 1;
    }

    grades = malloc(n * sizeof(float));
    if (grades == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("Enter grade for student %d: ", i + 1);
        scanf("%f", &grades[i]);
    }

    highest = grades[0];
    lowest = grades[0];
    for (i = 1; i < n; i++) {
        if (grades[i] > highest) {
            highest = grades[i];
        }
        if (grades[i] < lowest) {
            lowest = grades[i];
        }
    }

    printf("Highest grade = %.2f\n", highest);
    printf("Lowest grade = %.2f\n", lowest);
    free(grades);
    return 0;
}
