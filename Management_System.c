/*Create a menu-driven C program that manages student records using structures, functions, and file handling.*/
#include<stdio.h>
#include<string.h>
/* ----------- MACROS ----------- */
#define max_student 100    //student array limit 
#define max_course 100  //course array limit
#define max_marks 100   //marks maximum limit
#define max_name 100    //name array limit
#define max_age 100 //age maximum limit
/* ----------- FUNCTIONS ----------- */    
void save();    //update file
void getind();  //calculate index for student array
void disstu();  //display student(s)
void addstu();  //add new student
void clebuff();     //clear input buffer
int check(int*);    //compare roll number with pre-existing ones
void delstu(int*);  //delete student
void updstu(int*);  //update student
void seastu(int*);  //search student
/* ----------- STRUCTURE ----------- */
typedef struct student_structure
{
    char course[max_course];
    char name[max_name];
    int marks;
    int roll;
    int age;
}stu;
stu student[max_student];  
/* ----------- GLOBAL VARIABLE(S) ----------- */ 
int indx= 0;    //control index of student structure array
/* ----------- MAIN FUNCTION ----------- */    
int main()
{
    /* --- variables --- */
    int choice;     //control of Main Menu
    int temp_roll;  //argument for logic function(s) -- search, update, delete
    /* --- get index function --- */
    getind();
    /* --- main menu with loop --- */
    printf("\n --- Student Management Programme --- \n");
    do
    {
        printf("\nMAIN MENU\n1. Add Student\n2. Display Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit");
        printf("\nEnter your choice:\n");
        scanf("%d", &choice);
        /* --- action based on response --- */
        switch (choice)
        {
            case 1:
                //check array availability
                if(indx>=max_student)
                {
                    printf("Storage full, Exitting...\n");
                    break;
                }
                //logic function
                addstu();
                break;
            case 2:
                disstu();
                break;
            case 3:
                printf("Enter Roll Number:\n");
                scanf("%d", &temp_roll);
                clebuff();
                //logic function
                seastu(&temp_roll);
                break;
            case 4: 
                printf("Enter Roll Number:\n");
                scanf("%d", &temp_roll);
                clebuff();
                //logic function
                updstu(&temp_roll);
                break;
            case 5:
                printf("Enter Roll Number:\n");
                scanf("%d", &temp_roll);
                clebuff();
                //logic function
                delstu(&temp_roll);
                break;
            case 6:
                printf("Exitting...\n");
                break;
            default: 
                printf("Invalid Response! Exitting...\n");
                break;
        }
    } while(choice!=6);
    /* --- main menu loop ends --- */
    return 0;
}
/* ----------- BUFFER CLEANUP FUNCTION ----------- */
void clebuff()
{
    while(getchar() != '\n');
}
/* ----------- SCAN INDEX FUNCTION ----------- */
void getind()
{
    indx=0;     //index reset
    /* --- file open --- */ 
    FILE *student_database_pointer;
    student_database_pointer= fopen("student_database.dat", "rb");
    if(student_database_pointer==NULL)
    {
        return;
    }
    /* --- index logic --- */
    while(indx<max_student && fread(&student[indx], sizeof(stu), 1, student_database_pointer))
    {
        indx++;
    }
    /* --- file close --- */
    fclose(student_database_pointer);
}
/* ----------- ROLL NUMBER CHECKER ----------- */
int check(int* rollnumber)
{
    for(int i=0; i<indx; i++)
    {
        if(student[i].roll==*rollnumber)
        {
            return 0;
        }
    }
    return 1;                                           
}
/* ----------- UPDATE FILE ----------- */
void save()
{
    /* --- open file --- */
    FILE *student_database_pointer;
    student_database_pointer= fopen("student_database.dat", "wb");
    if(student_database_pointer==NULL)
    {
        printf("\nFile open error. Exitting...\n");
        return;
    }
    /* --- file save logic --- */
    for(int j=0; j<indx; j++)
    {
        fwrite(&student[j], sizeof(stu), 1, student_database_pointer);
    }
    /* --- file close --- */
    fclose(student_database_pointer);
}
/* ----------- ADD STUDENT FUNCTION ----------- */
void addstu()
{
    /* --- roll number --- */
    printf("Enter Roll number:\n");
    scanf("%d", &student[indx].roll);
    clebuff();
    //checking existance of input roll number
    if(check(&student[indx].roll)==0)
    {
        printf("Student already exists, Exiting...\n");
        return;                                                
    }
    /* --- name --- */
    printf("Enter Name:\n");      
    fgets(student[indx].name, max_name, stdin);
    student[indx].name[strcspn(student[indx].name, "\n")]= '\0';
    /* --- age --- */
    printf("Enter Age:\n");
    //non integer age checker
    if(scanf("%d", &student[indx].age) != 1)
    {
        printf("Invalid input\n");
        return;
    }
    clebuff();
    //age limit
    if(student[indx].age<=0 || student[indx].age>max_age)
    {
        printf("Invalid age, Exitting...\n");
        return;
    }
    /* --- course --- */
    printf("Enter Course:\n");
    fgets(student[indx].course, max_course, stdin);
    student[indx].course[strcspn(student[indx].course, "\n")]= '\0';
    /* --- marks --- */     //IMP- floating point datatype for marks
    printf("Enter Marks:\n");
    //non integer marks checker
    if(scanf("%d", &student[indx].marks) != 1)
    {
        printf("Invalid input\n");
        return;
    }
    clebuff();
    //marks limit
    if(student[indx].marks>max_marks || student[indx].marks<0)
    {
        printf("Invalid marks, Exitting...\n");
        return;                                         
    }
    /* --- file open --- */
    FILE *student_database_pointer;
    student_database_pointer= fopen("student_database.dat", "ab"); 
    if (student_database_pointer==NULL)
    {
        printf("File open error, Exitting...\n");
        return;
    }
    /* --- save logic --- */
    fwrite(&student[indx], sizeof(stu), 1, student_database_pointer);
    indx++;
    /* --- file close --- */
    fclose(student_database_pointer);                                           
    printf("\n---Student added successfully---\n");
}
/* ----------- DISPLAY FUNCTION ----------- */
void disstu()   //IMP- shorting logic/ ordering logic based on roll number
{
    printf("\nTotal Students: %d\n", indx);
    for(int i=0; i<indx; i++)
    {
        printf(">>Student %d<<\n", i+1);
        printf("Name: %s\n", student[i].name);
        printf("Age: %d\n", student[i].age);
        printf("Roll number: %d\n", student[i].roll);
        printf("Course: %s\n", student[i].course);
        printf("Marks: %d\n", student[i].marks);
    }
    printf("\n---End of Record---\n");
}
/* ----------- SEARCH STUDENT FUNCTION ----------- */
void seastu(int* roll)
{
    /* --- variable --- */
    int result=0;   //Number of match found
    /* --- UI --- */
    printf("Searching...\n");
    /* --- search logic --- */
    for(int i=0; i<indx; i++)
    {
        if(student[i].roll==*roll)
        {
            result++;
            printf("Student Number: %d\n", i+1);
            printf("Name: %s\n", student[i].name);
            printf("Age: %d\n", student[i].age);
            printf("Roll number: %d\n", student[i].roll);
            printf("Course: %s\n", student[i].course);
            printf("Marks: %d\n", student[i].marks);
        }
    }
    /* --- UI --- */
    if(result==0)
    {
        printf("No results found. Exitting...\n");
    }
    else
        printf("---%d Result(s) found---\n", result);
}
/* ----------- UPDATE STUDENT ----------- */
void updstu(int* roll)
{
    /* --- variables --- */
    int upd_verify;    //verification of update operation 
    int upd_choice;     //response of 'update menu'
    int upd_unmatch=0;  //if roll number does'nt exist -> 0, otherwise 1
    char upd_course[max_course];    //temp string array, used to update course
    /* --- logic --- */
    for(int i=0; i<indx; i++)
    {
        if(student[i].roll==*roll)
        {
            upd_unmatch=1;
            //print student of matching roll number
            printf("Student Number: %d\n", i+1);
            printf("Name: %s\n", student[i].name);
            printf("Age: %d\n", student[i].age);
            printf("Roll number: %d\n", student[i].roll);
            printf("Course: %s\n", student[i].course);
            printf("Marks: %d\n", student[i].marks);
            //verify update?
            printf("Do you wants to update?\n1. Yes, Continue\n2. No, Exit\n");
            scanf("%d", &upd_verify);
            //update cancelled
            if(upd_verify==2)
            {
                return;
            }
            //update verified
            else if(upd_verify==1)
            {
                //'update menu' with loop
                do
                {
                    printf("\n --- Update Menu --- \n");
                    printf("Enter your choice:\n1. Update Age\n2. Update Course\n3. Update Marks\n4. Exit to Main Menu\n");
                    scanf("%d", &upd_choice);
                    clebuff();
                    //action based on response
                    switch(upd_choice)
                    {
                        case 1:     //update age
                            printf("Enter new age:\n");
                            //checking non integer age
                            if(scanf("%d", &student[i].age) != 1)
                            {
                                printf("Invalid input\n");
                                return;
                            }
                            clebuff();
                            //checking age limit
                            if(student[i].age<=0 || student[i].age>max_age)
                            {
                                printf("Invalid age, Exitting...\n");
                                return;
                            }
                            //false statement
                            printf("\n --- Student updated successfully --- \n");
                            break;
                        case 2:     //update course
                            printf("Enter new Course:\n");
                            fgets(upd_course, max_course, stdin);
                            upd_course[strcspn(upd_course, "\n")]= '\0';
                            strcpy(student[i].course, upd_course);
                            //false statement
                            printf("\n --- Student updated successfully --- \n");
                            break;
                        case 3:     //update marks
                            printf("Enter new marks:\n");
                            //checking non integer marks
                            if(scanf("%d", &student[i].marks) != 1)
                            {
                                printf("Invalid input\n");
                                return;
                            }
                            clebuff();
                            //checking marks limit
                            if(student[i].marks>max_marks || student[i].marks<0)
                            {
                                printf("Invalid marks, Exitting...\n");
                                return;                                         
                            }
                            //false statement
                            printf("\n --- Student updated successfully --- \n");
                            break;
                        case 4:
                            break;
                        default: 
                            printf("Invalid response, Exitting...\n");
                            return;
                    }
                }while(upd_choice!=4);
                //'update menu' loop ends
                //updating file [making false statement(s) true]
                save();
            }
            //update verify- invalid
            else
            {
                printf("Invalid response! Exitting...\n");
                return;
            }
            return;
        }
    }
    //input roll number doesn't exist
    if(upd_unmatch!=1)
    {
        printf("No results found, Exitting...\n");
        return;
    }
}
/* ----------- DELETE STUDENT ----------- */
void delstu(int* roll)
{
    /* --- variables --- */
    int del_verify;     //verification of delete operation
    int del_unmatch=0;  //if roll number does'nt exist -> 0, otherwise 1
    /* --- logic --- */
    for(int i=0; i<indx; i++)
    {
        if(student[i].roll==*roll)
        {
            del_unmatch=1;
            //print student of matching roll number
            printf("Student Number: %d\n", i+1);
            printf("Name: %s\n", student[i].name);
            printf("Age: %d\n", student[i].age);
            printf("Roll number: %d\n", student[i].roll);
            printf("Course: %s\n", student[i].course);
            printf("Marks: %d\n", student[i].marks);
            //verify delete?
            printf("Do you wants to delete?\n1. Yes, Continue\n2. No, Exit\n");
            scanf("%d", &del_verify);
            //delete cancelled
            if(del_verify==2)
            {
                return;
            }
            //delete verified
            else if(del_verify==1)  //arrays:    12(3)45600 -> 12456600, left shifted data instead of free()
            {
                for(int j=i; j<indx-1; j++)
                {
                    student[j]=student[j+1];
                }
                indx= indx-1;   //clear last array:  12456600 -> 12456000
                memset(&student[indx], 0, sizeof(stu));
                //update file 
                save();
                //UI
                printf("\n --- Student deleted successfully --- \n");
                return;
            }
            //delete verify- invalid
            else
            {
                printf("Invalid Response! Exitting...\n");
                return;
            }
        }
    }
    //input roll number doesn't exist
    if(del_unmatch!=1)
    {
        printf("No results found, Exitting...\n");
        return;
    }
}
