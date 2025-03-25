/*#include<stdio.h>

struct student{
    int roll_no;
    char name[100];
    float marks;
};

int main()
{
    struct student s;
    printf("Enter Students Roll number, Name, Marks");
    scanf("%d%s%f",&s.roll_no,s.name,&s.marks);

    printf("\n Roll number of student is %d, Name of Student is %s, Marks Obtain is %f",s.roll_no,s.name,s.marks);
}*/

//--------------------------------
//Array of Structures

/*#include<stdio.h>

struct student{
    int roll_no;
    char name[100];
    float marks;
};

int main()
{
    struct student students[3];
    
    printf("Please, Enter Students Information Roll No  Name  Marks");
    for(int i=0;i<3;i++)
    {
        scanf("%d %s %f", &students[i].roll_no,students[i].name,&students[i].marks);
    }

    for(int i = 0;i<3;i++)
    {
        printf("\n Roll No:%d , Name : %s, Marks : %f", students[i].roll_no,students[i].name,students[i].marks);
    }
}*/

//---------------------------------
/* Structure Pointer
#include <stdio.h>
#include <stdlib.h>

// Define structure
struct Student {
    int roll_no;
    char name[50];
    float marks;
};

int main() {
    struct Student *ptr;  // Pointer to structure
    int i, n = 2;  // Number of students

    // Allocate memory dynamically for 10 students
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Input details for each student
    for (i = 0; i < n; i++) {
        printf("\nEnter details for Student %d:\n", i + 1);
        printf("Enter Roll No: ");
        scanf("%d", &(ptr + i)->roll_no);     //&(ptr[i])
        printf("Enter Name: ");
        scanf(" %[^\n]", (ptr + i)->name);  // Read full name  //&(ptr[i])
        printf("Enter Marks: ");
        scanf("%f", &(ptr + i)->marks);  //&(ptr[i])
    }

    // Display student details
    printf("\n------ Student Details ------\n");
    for (i = 0; i < n; i++) {
        printf("\nStudent %d:\n", i + 1);
        printf("Roll No: %d\n", (ptr + i)->roll_no);
        printf("Name: %s\n", (ptr + i)->name);
        printf("Marks: %.2f\n", (ptr + i)->marks);
    }

    // Free allocated memory
    free(ptr);

    return 0;
}
*/
//------------------------------------------------
//Bitfield
/*
#include <stdio.h>

struct Status {
    unsigned int flag1 : 1;  // 1 bit
    unsigned int flag2 : 1;  // 1 bit
    unsigned int flag3 : 1;  // 1 bit
    unsigned int reserved : 5;  // 5 bits (padding)
};
*/
//-----------------------------------------------

//union bitfield
/*
#include <stdio.h>

union Data {
    struct {
        unsigned int x : 4;  // 4 bits
        unsigned int y : 4;  // 4 bits
    };
    unsigned char value;  // 1 byte (8 bits)
};

int main() {
    union Data d;
    d.value = 0b10100011;  // 163 in decimal

    printf("X: %d, Y: %d\n", d.x, d.y);
    printf("Value: %d\n", d.value);

    return 0;
}*/
