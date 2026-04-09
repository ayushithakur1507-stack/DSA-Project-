#include<stdio.h>
#include<string.h>

#define MAX 100  
#define LIMIT 120   

int violations[MAX] =  {0};

struct Student
{
    int studentID;
    char name[50];
    int violationCount;
};

struct Record
{
    int studentID;
    int date;
    int outTime;
    int inTime;
    int duration;
    int flag; 
};

struct Record queue[MAX]; 
int front = 0;
int rear = -1;

struct Student students[MAX];
int studentCount = 0;

void addStudent()
{
    printf("Enter the student ID: ");
    scanf("%d",&students[studentCount].studentID);
    
    printf("Enter name of the student: ");
    getchar();  
    fgets(students[studentCount].name, 50, stdin);
    
    students[studentCount].violationCount = 0;
    studentCount++;
}

int findStudent(int id) 
{
    for (int i = 0; i < studentCount; i++) 
    {
        if (students[i].studentID == id)
            return i;
    }
    return -1;
}

void recordOuting() 
{
    struct Record r;

    printf("Enter the student ID: ");
    scanf("%d", &r.studentID);

    printf("Enter the date: ");
    scanf("%d", &r.date);

    printf("Enter the out time (in minutes): ");
    scanf("%d", &r.outTime);

    printf("Enter the in time (in minutes): ");
    scanf("%d", &r.inTime);
    
    r.duration = r.inTime - r.outTime;
    
    if (r.duration > LIMIT) 
    {
        r.flag = 1;
        printf("Violation detected!\n");
        
        rear++;
        queue[rear] = r;

        
        int x = findStudent(r.studentID);
        if (x != -1) 
        {
            students[x].violationCount++;
        }
    } 
    else 
    {
        r.flag = 0;
        printf("No violation detected!\n");
    }
}

void removeOldViolations(int currentDay) 
{
    while (front <= rear && queue[front].date <= currentDay - 14) 
    {
        int id = queue[front].studentID;

        int x = findStudent(id);
        if (x != -1) 
        {
            students[x].violationCount--;
        }

        front++;
    }
    printf("Old records have been removed.\n");
}
    
void displayReport() 
{
    printf("\nStudent Violation Report\n");

    for (int i = 0; i < studentCount; i++) 
    {
        printf("\nStudent ID: %d", students[i].studentID);
        printf("\nName: %s", students[i].name);
        printf("\nViolation Count: %d\n", students[i].violationCount);
    }
}

void showHistory(int id) 
{
    printf("\nViolation History for Student %d:\n", id);

    for (int i = front; i <= rear; i++) 
    {
        if (queue[i].studentID == id) 
        {
            printf("Date: %d, Duration: %d mins\n",
                   queue[i].date,
                   queue[i].duration);
        }
    }
}

int main() 
{
    int ch, currentDay, id;

    while (1) 
    {
        printf("\nMENU\n");
        printf("1. Add Student\n");
        printf("2. Record Outing\n");
        printf("3. Remove Old Records\n");
        printf("4. Display All Students\n");
        printf("5. Show Violation History\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) 
        {
            case 1:
                addStudent();
                break;

            case 2:
                recordOuting();
                break;

            case 3:
                printf("Enter current day: ");
                scanf("%d", &currentDay);
                removeOldViolations(currentDay);
                break;

            case 4:
                displayReport();
                break;

            case 5:
                printf("Enter Student ID: ");
                scanf("%d", &id);
                showHistory(id);
                break;

            case 6:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

