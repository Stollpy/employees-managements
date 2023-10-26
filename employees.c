#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <uuid/uuid.h>
#include "helper.c"

struct Employee {
    char firstname[25];
    char lastname[25];
    char job[50];
};

int action_write()
{
    struct Employee employee;
    char action = 'Y';
    FILE* pFile = fopen("employees.txt", "a");

    printf("\n Add a new employee\n\n");

    while(action == 'Y') {
        printf("What is firstname: ");
        scanf("%s", employee.firstname);

        printf("What is lastname: ");
        scanf("%s", employee.lastname);

        printf("What is job: ");
        scanf("%s", employee.job);

        fprintf(pFile, "%s,%s,%s\n", employee.firstname, employee.lastname, employee.job);
        printf("Add a new employee ? (Y/N)");
        scanf(" %c", &action);
    }

    fclose(pFile);

    return 0;
}

int action_read()
{
    FILE* pFile = fopen("employees.txt", "r");
    int i = 0;
    char row[150];

    printf("\n----------------------------------------------------\n");
    printf(" Name | Firstname | Job\n");

    while(fgets(row, 150, pFile) != NULL) {
        char* tmpRow = strcpy((char*)malloc(strlen(row)),row);
        char** data = explode(',', tmpRow);

        if (NULL != data) {
            printf("----------------------------------------------------\n");
            printf(" %d | %s | %s | %s", i, data[0], data[1], data[2]);

            free(data);
        }

        i++;

        free(tmpRow);
    }

    printf("\n");

    return 0;
}

int action_delete()
{

    char action = 'Y';

    while(action == 'Y') {
       action_read();

       int id = 0;
       int i = 0;
       char *fileId = uuid();
       char fileName[45] = "employees-";
       char row[150];

       strcat(fileName, fileId);
       strcat(fileName, ".txt");

       FILE* tmpDB = fopen(fileName, "w");

       printf("\n Which employee are you cutting? ");
       scanf(" %d", &id);

       FILE* DB = fopen("employees.txt", "r");

        while(fgets(row, 150, DB) != NULL) {
            if (i != id) {
                char* tmpRow = strcpy((char*)malloc(strlen(row)),row);
                char** data = explode(',', tmpRow);
                fprintf(tmpDB, "%s,%s,%s", data[0], data[1], data[2]);
                free(tmpRow);
            }

            i++;
        }

        fclose(tmpDB);
        fclose(DB);

        remove("employees.txt");

        char tmpDBFileName[45] = "employees-";
        strcat(tmpDBFileName, fileId);
        strcat(tmpDBFileName, ".txt");

        if (rename(tmpDBFileName, "employees.txt") != 0) {
            int error_code = errno;
            printf("Erreur (%d): %s\n", error_code, strerror(error_code));
            return 1;
        }

        remove(tmpDBFileName);

       printf("Delete a other employee ? (Y/N)");
       scanf(" %c", &action);
    }

    return 0;
}

int main(void)
{
   char con = 'Y';
   int action = 0;
   int r;

   while('Y' == con) {

       printf("What action would you like to take:\n");
       printf("0 - Read list\n");
       printf("1 - Add a employee\n");
       printf("2 - Delete a employee\n");
       printf("3 - Exit\n");
       scanf(" %d", &action);

       switch(action) {
           case 0:
               r = action_read();
               break;
           case 1:
               r = action_write();
               break;
           case 2:
               r = action_delete();
               break;
           case 3:
               printf("Choice not found.");
               r = 1;
               break;
       }

        if (1 <= r) {
            return r;
        }

       printf("Would you like to see another action? (Y/N) ");
       scanf(" %c", &con);
   }


    return 0;
}