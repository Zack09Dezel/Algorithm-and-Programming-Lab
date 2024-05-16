#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATABASE "C:/Arts and Literatures/Studying Progress/College/Academic Year/2nd Semester/CS/Algorithm and Programming Practicum/Experiments/Assignments/DATABASE/DATABASE.csv"
#define TEMP_FILE "C:/Arts and Literatures/Studying Progress/College/Academic Year/2nd Semester/CS/Algorithm and Programming Practicum/Experiments/Assignments/DATABASE/temp.csv"


struct Mahasiswa {
    long long int studentID;
    char name[50];
    int entryYear;
    float GPA;
};

int main() {
    FILE *fl;
    int choice;
    do {
        printf("\nData manipulation menu (In Numbers):\n");
        printf("1. Add\n");
        printf("2. Delete\n");
        printf("3. Edit\n");
        printf("4. Display All\n");
        printf("5. Search\n");
        printf("6. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                fl = fopen(DATABASE, "a"); // Initialize FILE pointer
                if (fl == NULL){
                    printf("Failed to open the file.\n");
                    exit(1);
                }

                int studentsTotal;
                printf("\nHow many students? ");
                scanf("%d", &studentsTotal);
                struct Mahasiswa add[studentsTotal]; 

                for(int i = 1; i <= studentsTotal; i++){

                    printf("\nStudent number %d", i);
                    printf("\nStudent ID Number: ");
                    scanf("%lld", &add[i].studentID);
                    printf("Name: ");
                    scanf(" %[^\n]", add[i].name);
                    printf("Year of Entry: ");
                    scanf("%d", &add[i].entryYear);
                    printf("GPA of said students: ");
                    scanf("%f", &add[i].GPA);

                    fprintf(fl, "%lld,%s,%d,%.2f\n", add[i].studentID, add[i].name, add[i].entryYear, add[i].GPA);
                }

                fclose(fl);
                break;
            }
            
            case 2: {
                fl = fopen(DATABASE, "r"); // Initialize FILE pointer
                if (fl == NULL){
                    printf("Failed to open the file.\n");
                    exit(1);
                }

                FILE *tempFile = fopen(TEMP_FILE, "w");
                if (tempFile == NULL){
                    printf("Failed to create temporary file.\n");
                    exit(1);
                }

                struct Mahasiswa delete;
                long long int targetID;
                
                printf("Enter the student ID you want to delete: ");
                scanf("%lld", &targetID);
                rewind(fl);


                while(fscanf(fl, "%lld,%49[^,],%d,%f\n", &delete.studentID, delete.name, &delete.entryYear, &delete.GPA) == 4){
                    if(delete.studentID != targetID){
                        fprintf(tempFile, "%lld,%s,%d,%.2f\n", delete.studentID, delete.name, delete.entryYear, delete.GPA);
                    }
                }

                fclose(fl);
                fclose(tempFile);

                if(remove(DATABASE) != 0){
                    printf("Error deleting the original file.\n");
                    exit(1);
                }

                if(rename(TEMP_FILE, DATABASE) != 0){
                    printf("Error renaming the temporary file.\n");
                    exit(1);
                }

                printf("Record deleted successfully.\n");
                break;
            }
            
            case 3: {
                fl = fopen(DATABASE, "r"); // Initialize FILE pointer
                if (fl == NULL){
                    printf("Failed to open the file.\n");
                    exit(1);
                }

                FILE *tempFile3 = fopen(TEMP_FILE, "w");
                if (tempFile3 == NULL){
                    printf("Failed to create temporary file.\n");
                    exit(1);
                }

                struct Mahasiswa modify;
                long long int targetID;
                
                printf("Enter the student ID you want to modify: ");
                scanf("%lld", &targetID);
                rewind(fl);

                int found = 0; 
                while(fscanf(fl, "%lld,%49[^,],%d,%f\n", &modify.studentID, modify.name, &modify.entryYear, &modify.GPA) == 4){
                    if(modify.studentID == targetID){
                        found = 1; 
                        printf("\nEnter new data for the student:\n");
                        printf("Name: ");
                        scanf(" %[^\n]", modify.name);
                        printf("Year of Entry: ");
                        scanf("%d", &modify.entryYear);
                        printf("GPA: ");
                        scanf("%f", &modify.GPA);
                    }
                    fprintf(tempFile3, "%lld,%s,%d,%.2f\n", modify.studentID, modify.name, modify.entryYear, modify.GPA);
                }

                fclose(fl);
                fclose(tempFile3);

                if(remove(DATABASE) != 0){
                    printf("Error deleting the original file.\n");
                    exit(1);
                }

                if(rename(TEMP_FILE, DATABASE) != 0){
                    printf("Error renaming the temporary file.\n");
                    exit(1);
                }

                if(found) {
                    printf("Record modified successfully.\n");
                } else {
                    printf("Student ID not found.\n");
                }
                break;
            }
            case 4: {
                fl = fopen(DATABASE, "r");
                if (fl == NULL) {
                    printf("Failed to open the file.\n");
                    exit(1);
                }

                struct Mahasiswa student;
                printf("\nAll Data:\n");
                printf("ID:\t\tName:\t\t\tEntry Year: \tGPA:\n");
                while (fscanf(fl, "%lld,%49[^,],%d,%f\n", &student.studentID, student.name, &student.entryYear, &student.GPA) == 4) {
                    printf("%lld\t%s\t%d\t\t%.2f\n", student.studentID, student.name, student.entryYear, student.GPA);
                }

                fclose(fl);
                break;
            }
            case 5: {
                fl = fopen(DATABASE, "r");
                if (fl == NULL) {
                    printf("Failed to open the file.\n");
                    exit(1);
                }

                long long int searchID;
                printf("Enter Student ID to search: ");
                scanf("%lld", &searchID);

                struct Mahasiswa student;
                int found = 0;
                while (fscanf(fl, "%lld,%49[^,],%d,%f\n", &student.studentID, student.name, &student.entryYear, &student.GPA) == 4) {
                    if (student.studentID == searchID) {
                        printf("\nStudent Found:\n");
                        printf("ID:\t\tName:\t\t\tEntry Year: \tGPA:\n");
                        printf("%lld\t%s\t%d\t\t%.2f\n", student.studentID, student.name, student.entryYear, student.GPA);
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Student with ID %lld not found.\n", searchID);
                }

                fclose(fl);
                break;
            }
            case 6:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 6);

    return 0;
}
