#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Mahasiswa
{
    long long int studentID;
    char name[50];
    int entryYear;
    float GPA;
};

bool Input(char* answer){
    return (strcmp(answer, "Yes") == 0 || strcmp(answer, "No") == 0);
}

int main() {

    int studentsTotal;
    long long int studentIDNumber;
    char studentName[50], category[10], answer[3];

    printf("\nHow many students? ");
    scanf("%d", &studentsTotal);
    struct Mahasiswa students[studentsTotal]; 

    for(int i = 0; i < studentsTotal; i++) {
        printf("\nStudent ID Number: ");
        scanf("%lld", &students[i].studentID);
        printf("Name: ");
        scanf(" %[^\n]", students[i].name); 
        printf("Year of Entry: ");
        scanf("%d", &students[i].entryYear);
        printf("GPA of said students: ");
        scanf("%f", &students[i].GPA);
    }

    printf("\nDo you want to display student's data?\n(Yes/No)\n\n");
    scanf("%s", answer);

    while (!Input(answer)){
            printf("Please enter either 'Yes' or 'No': ");
            scanf("%s", answer);
    }

    do {

        if(strcmp(answer, "Yes") == 0) {

            do {

                printf("\nOn what category would you want to display the student's data?\n1. ID\n2. Name\n3. Year of Entry\n4. GPA\n\n");
                scanf("%s", category);

                if(strcmp(category, "ID") == 0) {
                    printf("\nPlease Type the ID Number: \n");
                    scanf("%lld", &studentIDNumber); 
                    for(int i = 0; i < studentsTotal; i++) {
                        if(students[i].studentID == studentIDNumber) {
                            printf("\nStudent ID: %lld\n", students[i].studentID);
                            printf("Name: %s\n", students[i].name);
                            printf("Year of Entry %d\n", students[i].entryYear);
                            printf("GPA: %.2f\n", students[i].GPA);
                            break;
                        }
                    }

                } else if(strcmp(category, "Name") == 0) {
                    printf("\nPlease Type the Name: \n");
                    scanf(" %[^\n]", studentName); 
                    for(int i = 0; i < studentsTotal; i++) {
                        if(strcmp(students[i].name, studentName) == 0) {
                            printf("\nStudent ID: %lld\n", students[i].studentID);
                            printf("Name: %s\n", students[i].name);
                            printf("Year of Entry %d\n", students[i].entryYear);
                            printf("GPA: %.2f\n", students[i].GPA);
                            break;
                        }
                    }
                }

                printf("\nDo you want to display another student's data?\n(Yes/No)\n\n");
                scanf("%s", answer);

                while (!Input(answer)){
                    printf("Please enter either 'Yes' or 'No': ");
                    scanf("%s", answer);
                }

            }while(strcmp(answer, "Yes") == 0);

        }else if(strcmp(answer, "No") == 0) {
            break;
        }

        // printf("\nDo you want to display student's data again?\n(Yes/No)\n\n");
        // scanf("%s", answer);

        // while (!Input(answer)){
        //     printf("Please enter either 'Yes' or 'No': ");
        //     scanf("%s", answer);
        // }

    } while(strcmp(answer, "Yes") == 0);

    return 0;
}
