#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEMP_FILE "temp.csv"

struct Mahasiswa{
    long long int studentID;
    char name[50];
    int entryYear;
    float GPA;
};

void newFile(char filename[]){
    printf("Enter the name of the new file (50 character max): ");
    scanf("%49s", filename);
    strcat(filename, ".csv");
    remove(filename);

    FILE *fl = fopen(filename, "w");
    if (fl == NULL) {
        printf("Error: Unable to create file.\n");
        exit(1);
    }
    fclose(fl);
}

void openFile(char filename[]) {
    printf("\nEnter the name of the file you want to open: ");
    scanf("%49s", filename);
    strcat(filename, ".csv");

    FILE *fl = fopen(filename, "r");
    if(fl == NULL){
        printf("There is no file called %s\n", filename);
        exit(1);
    } else {
        printf("Opening file: %s\n", filename);
        fclose(fl);
    }
}

void deleteFile(char filename[]) {
    printf("\nEnter the name of the file you want to delete: ");
    scanf("%49s", filename); 
    strcat(filename, ".csv");

    FILE *fl = fopen(filename, "r");
    if(fl == NULL){
        printf("\nThere is no file called %s\n", filename);
        exit(1);
    } else {
        fclose(fl);
        remove(filename);    
        printf("Deleting file: %s\n", filename);
        printf("...\n");
        printf("...\n");
        printf("...\n");
        printf("%s has been successfully deleted\n", filename);
    }
}

void addRecord(char filename[]) {
    FILE *fl = fopen(filename, "a"); 
    if (fl == NULL){
        printf("Failed to open the file.\n");
        exit(1);
    }

    int studentsTotal;
    printf("\nHow many students? ");
    scanf("%d", &studentsTotal);
    struct Mahasiswa add[studentsTotal]; 

    for(int i = 0; i < studentsTotal; i++) {
        printf("\nStudent number %d", i + 1);
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
}

void deleteRecord(char filename[]) {
    FILE *fl_read = fopen(filename, "r"); 
    if (fl_read == NULL){
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
    rewind(fl_read); 

    while(fscanf(fl_read, "%lld,%49[^,],%d,%f\n", &delete.studentID, delete.name, &delete.entryYear, &delete.GPA) == 4){
        if(delete.studentID != targetID){
            fprintf(tempFile, "%lld,%s,%d,%.2f\n", delete.studentID, delete.name, delete.entryYear, delete.GPA);
        }
    }

    fclose(fl_read); 
    fclose(tempFile); 

    remove(filename); 
    rename(TEMP_FILE, filename); 
    printf("Record deleted successfully.\n");
}

void editRecord(char filename[]) {
    FILE *tempFile3 = fopen(TEMP_FILE, "w");
    if (tempFile3 == NULL){
        printf("Failed to create temporary file.\n");
        exit(1);
    }

    struct Mahasiswa modify;
    long long int targetID;
    
    printf("Enter the student ID you want to modify: ");
    scanf("%lld", &targetID);

    FILE *fl = fopen(filename, "r"); 
    if (fl == NULL){
        printf("Failed to open the file.\n");
        exit(1);
    }
    rewind(fl);

    int found = 0; 
    while(fscanf(fl, "%lld,%49[^,],%d,%f\n", &modify.studentID, modify.name, &modify.entryYear, &modify.GPA) == 4){
        if(modify.studentID == targetID){
            found = 1; 
            printf("\nEnter new data for the student\n");
            printf("Student ID Number: ");
            scanf(" %lld", &modify.studentID);
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

    if(remove(filename) != 0){
        printf("Error deleting the original file.\n");
        exit(1);
    }

    if(rename(TEMP_FILE, filename) != 0){
        printf("Error renaming the temporary file.\n");
        exit(1);
    }

    if(found) {
        printf("Record modified successfully.\n");
    } else {
        printf("Student ID not found.\n");
    }
}

void displayAll(char filename[]) {
    FILE *fl = fopen(filename, "r");
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
}

void searchRecord(char filename[]) {
    FILE *fl = fopen(filename, "r");
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
}

int main(){
    int choice;
    char filename[50];

    do {
        printf("\nMain Menu (In Numbers):\n");
        printf("1. New File\n");
        printf("2. Open File\n");
        printf("3. Delete File\n");
        printf("4. Exit\n");
        printf("Your Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                newFile(filename);
                break;
            case 2:
                openFile(filename);
                break;
            case 3:
                deleteFile(filename);
                break;
            case 4:
                printf("Exiting the program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
                continue;    
        }

        do {
            printf("\nData manipulation menu (In Numbers):\n");
            printf("1. Add\n");
            printf("2. Delete\n");
            printf("3. Edit\n");
            printf("4. Display All\n");
            printf("5. Search\n");
            printf("6. Back to main menu\n");
            printf("7. Exit the program\n");
            printf("Your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    addRecord(filename);
                    break;
                case 2:
                    deleteRecord(filename);
                    break;
                case 3:
                    editRecord(filename);
                    break;
                case 4:
                    displayAll(filename);
                    break;
                case 5:
                    searchRecord(filename);
                    break;
                case 6:
                    printf("Returning to main menu.\n");
                    break;
                case 7:
                    printf("Exiting the program.\n");
                    return 0;
                default:
                    printf("Invalid choice.\n");
            }  
        } while (choice != 6 && choice != 7);
    } while (choice!=4);

    return 0;
}
