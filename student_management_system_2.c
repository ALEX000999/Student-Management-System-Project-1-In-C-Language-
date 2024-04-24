#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void menu();
void add();
void view();
void search();
void modify();

struct student {
    char student_name[30];
    int id_no;
    int mobile_no;
    char department[3];
    int age;
    char gender[1];
    float cgpa;
};
int main() {
    
    printf("\n>>>>>----- UNIVERSITY OF LIBERAL ARTS BANGLADESH -----<<<<<\n\n");
    printf(">>>>>----- Students Records Management System -----<<<<\n\n");
    menu();
    return 0;
}
void menu() {
    int choice;

    printf("\t\t>>>>>----- MENU -----<<<<<\n\n");
    printf("\tEnter appropriate number to perform following task.\n\n");
    printf("\t\t\t1: Add Record\n");
    printf("\t\t\t2: View Record\n");
    printf("\t\t\t3: Search Record\n");
    printf("\t\t\t4: Modify Record\n");
    printf("\t\t\t5: Exit\n");
    printf("\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            add();
            break;
        case 2:
            view();
            break;
        case 3:
            search();
            break;
        case 4:
            modify();
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid Choice.\n");
    }
    menu();
}
void add()
{
    FILE *fp;
    struct student std;
    char another ='y';
    system("cls");

    fp = fopen("record.txt","ab+");
    if(fp == NULL){
        printf("Error opening file");
        exit(1);
    }
    fflush(stdin);
    while(another == 'y')
    {
        printf("<--:ADD RECORD:-->\n");
        printf("Enter details of student.\n");

        printf("Enter Student Name : \n");
        gets(std.student_name);

        printf("Enter Mobile Number : \n");
        scanf("%d", &std.mobile_no);

        printf("Enter ID No : \n");
        scanf("%d",&std.id_no);
        fflush(stdin);

        printf("Enter Depertment (CSE/EEE/BBA/MSJ): \n");
        gets(std.department);

        printf("Enter Gender (M/F): \n");
        gets(std.gender);

        printf("Enter Age : \n");
        scanf("%d", &std.age);

        printf("Enter CGPA: \n");
        scanf("%f", &std.cgpa);

        fwrite(&std,sizeof(std),1,fp);
        printf("Want to add of another record? Then press 'y' else 'n'.\n");
        fflush(stdin);
        another = getchar();
        system("cls");
        fflush(stdin);
    }
    fclose(fp);
    menu();
}
void view() {
    FILE *fp;
    struct student std;
    int found = 0;

    printf("<--:VIEW RECORD:-->\n");

    printf("Enter Department (CSE/EEE/BBA/MSJ) To View Details Of Students: \n");
    fflush(stdin);
    scanf("%s", std.department);

    if (strcmp(std.department, "CSE") != 0 && strcmp(std.department, "EEE") != 0 && 
        strcmp(std.department, "BBA") != 0 && strcmp(std.department, "MSJ") != 0) {
        printf("Invalid department code. Please try again.\n");
        return;
    }

    fp = fopen("record.txt", "rb");
    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (strcmp(std.department, std.department) == 0) {
            printf("Student Name: %s\n", std.student_name);
            printf("Student ID No: %d\n", std.id_no);
            printf("Student Mobile Number: %d\n", std.mobile_no);
            printf("Student Department: %s\n", std.department);
            printf("Student Gender: %s\n", std.gender);
            printf("Student Age: %d\n", std.age);
            printf("Student CGPA: %.2f\n", std.cgpa);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No student record found for the entered department.\n");
    }
    fclose(fp);
    menu();
}
void search() {
    FILE *fp;
    struct student std;
    int stidno, found = 0;
    system("cls");

    printf("<--:SEARCH RECORD:-->\n");

    printf("Enter ID No Of Student To Search: \n");
    fflush(stdin);
    scanf("%d", &stidno);

    fp = fopen("record.txt", "r");

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id_no == stidno) {
            printf("Student Name: %s\n", std.student_name);
            printf("Student ID No: %d\n", std.id_no);
            printf("Student Mobile Number: %d\n", std.mobile_no);
            printf("Student Department: %s\n", std.department);
            printf("Student Gender: %s\n", std.gender);
            printf("Student Age: %d\n", std.age);
            printf("Student CGPA: %.2f\n", std.cgpa);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", stidno);
    }

    fclose(fp);

    menu();
}
void modify() {
    int stidno, found = 0;
    FILE *fp, *temp_fp;
    struct student std;

    system("cls"); 

    printf("<--:MODIFY RECORD:-->\n");

    printf("Enter ID No Of Student To Modify: \n");
    scanf("%d", &stidno);

    fp = fopen("record.txt", "r"); 

    if (fp == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    temp_fp = fopen("temp.txt", "w");

    if (temp_fp == NULL) {
        printf("Error creating temporary file\n");
        fclose(fp);
        exit(1);
    }
    while (fread(&std, sizeof(std), 1, fp) == 1) {
        if (std.id_no == stidno) {
            printf("Enter new details for student:\n");
            printf("Enter Student Mobile Number: ");
            scanf("%d", &std.mobile_no);
            printf("Enter CGPA: ");
            scanf("%f", &std.cgpa);
            found = 1;
        }
        fwrite(&std, sizeof(std), 1, temp_fp); 
    }
    fclose(fp);
    if (!found) {
        printf("Student with ID %d not found.\n", stidno);
        remove("temp.txt");
    } else {
        fclose(temp_fp); 

        remove("record.txt");
        rename("temp.txt", "record.txt"); 
        printf("Record modified successfully.\n");
    }
    menu();
}