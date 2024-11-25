#include<stdio.h>
#include<string.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    char course_name[20];
    char code[10];
} course;

// A structure to store the student details
typedef struct {
    char roll_no[50];
    char name[50];
    char dob[20];
    char email[50];
    int no_of_courses;
    float cgpa;
} student;

// Pointers for dynamic allocation
student *students = NULL;
course *courses = NULL;
int student_count = 0;
int course_count = 0;
int max_student = 0;
int max_courses = 0;

// TO DISPLAY THE LIST OF STUDENTS
void display_all() {
    if (student_count == 0) {
        printf("No students to display.\n");
        return;
    }

    // Header line
    printf("+-------------+---------------------+------------+---------------------------+------------------+-------+\n");
    printf("|  ROLL NO    |        NAME         |    DOB     |          EMAIL            | NO. OF COURSES   |  CGPA |\n");
    printf("+-------------+---------------------+------------+---------------------------+------------------+-------+\n");

    // Rows
    for (int i = 0; i < student_count; i++) {
        printf("| %-11s | %-19s | %-10s | %-25s | %-16d | %-5.2f |\n",
               students[i].roll_no, students[i].name, students[i].dob,
               students[i].email, students[i].no_of_courses, students[i].cgpa);
    }

    // Footer line
    printf("+-------------+---------------------+------------+---------------------------+------------------+-------+\n");
}



// TO ADD STUDENTS
void add_student() {
    if (student_count >= max_student) {
        printf("Maximum student limit reached.\n");
        return;
    }

    student s;
    printf("Enter roll number: ");
    scanf("%s", s.roll_no);
    printf("Enter name: ");
    scanf(" %[^\n]s", s.name);
    printf("Enter date of birth (DD/MM/YYYY): ");
    scanf("%s", s.dob);
    printf("Enter email: ");
    scanf("%s", s.email);
    printf("Enter number of courses: ");
    scanf("%d", &s.no_of_courses);
    printf("Enter CGPA: ");
    scanf("%f", &s.cgpa);

    students[student_count++] = s;
    printf("Student added successfully.\n");
}

// TO UPDATE STUDENT DETAILS
void update_student() {
    char roll_no[20];
    int found = 0;

    printf("Enter the roll number of the student to update: ");
    scanf("%s", roll_no);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].roll_no, roll_no) == 0) {
            found = 1;

            printf("\nStudent found! Current details:\n");
            printf("Roll No.: %s\n", students[i].roll_no);
            printf("Name: %s\n", students[i].name);
            printf("DOB: %s\n", students[i].dob);
            printf("Email: %s\n", students[i].email);
            printf("Number of Courses: %d\n", students[i].no_of_courses);
            printf("CGPA: %.2f\n", students[i].cgpa);

            printf("Enter new name: ");
            scanf(" %[^\n]s", students[i].name);
            printf("Enter new DOB (DD/MM/YYYY): ");
            scanf("%s", students[i].dob);
            printf("Enter new email: ");
            scanf("%s", students[i].email);
            printf("Enter new number of courses: ");
            scanf("%d", &students[i].no_of_courses);
            printf("Enter new CGPA: ");
            scanf("%f", &students[i].cgpa);

            printf("Student details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %s.\n", roll_no);
    }
}

// TO DELETE A STUDENT
void delete_student() {
    char roll_no[20];
    int found = 0;

    printf("Enter the roll number of the student to delete: ");
    scanf("%s", roll_no);

    for (int i = 0; i < student_count; i++) {
        if (strcmp(students[i].roll_no, roll_no) == 0) {
            found = 1;
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("Student with roll number %s has been deleted successfully.\n", roll_no);
            break;
        }
    }

    if (!found) {
        printf("No student found with roll number %s.\n", roll_no);
    }
}

// TO SEARCH FOR A STUDENT
void search_student() {
    int choice;
    char query[50];
    int found = 0;

    printf("\nSearch Student By:\n");
    printf("1. Roll Number\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter Roll Number: ");
        scanf("%s", query);
        for (int i = 0; i < student_count; i++) {
            if (strcmp(students[i].roll_no, query) == 0) {
                found = 1;
                printf("\nStudent Found:\n");
                printf("Roll No.: %s\n", students[i].roll_no);
                printf("Name: %s\n", students[i].name);
                printf("DOB: %s\n", students[i].dob);
                printf("Email: %s\n", students[i].email);
                printf("Number of Courses: %d\n", students[i].no_of_courses);
                printf("CGPA: %.2f\n", students[i].cgpa);
                break;
            }
        }
    } else if (choice == 2) {
        printf("Enter Name: ");
        scanf(" %[^\n]s", query);
        for (int i = 0; i < student_count; i++) {
            if (strcasecmp(students[i].name, query) == 0) {
                found = 1;
                printf("\nStudent Found:\n");
                printf("Roll No.: %s\n", students[i].roll_no);
                printf("Name: %s\n", students[i].name);
                printf("DOB: %s\n", students[i].dob);
                printf("Email: %s\n", students[i].email);
                printf("Number of Courses: %d\n", students[i].no_of_courses);
                printf("CGPA: %.2f\n", students[i].cgpa);
            }
        }
    } else {
        printf("Invalid choice.\n");
        return;
    }

    if (!found) {
        printf("No student found with the given %s.\n", (choice == 1) ? "Roll Number" : "Name");
    }
}

// MAIN FUNCTION
int main() {
    printf("Enter the maximum number of students: ");
    scanf("%d", &max_student);
    printf("Enter the maximum number of courses: ");
    scanf("%d", &max_courses);

    // Allocate memory dynamically
    students = (student *)malloc(max_student * sizeof(student));
    courses = (course *)malloc(max_courses * sizeof(course));

    if (students == NULL || courses == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    int choice;
    do {
        printf("\t***EduTrack - Student Management System***\n");
        printf("\t\t\tMAIN MENU\n");
        printf("\t\t=========================\n");
        printf("\t\t1. Add Student\n");
        printf("\t\t2. Update Student\n");
        printf("\t\t3. Delete Student\n");
        printf("\t\t4. Search Student\n");
        printf("\t\t5. Display All Students\n");
        printf("\t\t0. Exit\n");
        printf("\t\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                update_student();
                break;
            case 3:
                delete_student();
                break;
            case 4:
                search_student();
                break;
            case 5:
                display_all();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    // Free allocated memory
    free(students);
    free(courses);

    return 0;
}
