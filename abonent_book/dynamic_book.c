#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define AB_CNT 100
#define STR_SIZE 20

typedef struct {

  int number;
  char name[STR_SIZE];
  char surname[STR_SIZE];

} abonent;

void menu(){

    printf("1. Add abonent\n");
    printf("2. Delete abonent\n");
    printf("3. Output book\n");
    printf("4. Search abonent\n");
    printf("5. Exit\n");
    printf("Enter a command: ");
}

int get_command(){
   
    int command;
    scanf("%d", &command);

    while (command < 1 || command > 5)
    {
        printf("\nIncorrect input. Try again: ");
        scanf("%d",&command);
    }

    return command;
}

bool add_abonent(abonent **abonents, int *abonent_id, int *max_abonents){
   
        printf("\nEnter the callnumber: ");

        int number = -1;
        scanf("%d",&number);

        if (number <= 0  ||  number > 999999)
        {
            printf("Number recording error\n");
            return false;
        }

        printf("\nEnter the name: ");

        char name[STR_SIZE] = {0};
        scanf("%s",name);

        if (strlen(name) > STR_SIZE)
        {  
            printf("Name recording error\n");
            return false;
        }

        printf("\nEnter the surname: ");

        char surname[STR_SIZE] = {0};
        scanf("%s",surname);

        if (strlen(surname) > STR_SIZE)
        {
            printf("Surname recording error\n");
            return false;
        }

        (*abonents)[*abonent_id].number = number;                                
        strncpy((*abonents)[*abonent_id].name, name, STR_SIZE);                  
        strncpy((*abonents)[*abonent_id].surname, surname, STR_SIZE); 
        (*abonent_id)++;

    if (*abonent_id >= *max_abonents)  
    {
        *max_abonents += 2;
        *abonents = (abonent *)realloc(*abonents, *max_abonents * sizeof(abonent));
    }

    return true;
} 

bool delete_abonent(abonent *abonents[], int abonent_id)
{

    abonent_id--;
    if (abonent_id >= 0)
    {
        char null_str[STR_SIZE] = {0};
        (*abonents)[abonent_id].number = 0;
        strncpy((*abonents)[abonent_id].name, null_str, STR_SIZE);
        strncpy((*abonents)[abonent_id].surname, null_str, STR_SIZE);
    }

    else
    {
        printf("\nThe book is empty!\n");
        
        return false;
    }

    return true;
}

void book_print(abonent abonents[], int max_ab_id)
{
    if (max_ab_id  > 0)
    {
        for (int i = 0; i < max_ab_id; i++)
        {
            printf("ID: %d Number: %d Name: %s Surname: %s\n", i, abonents[i].number, abonents[i].name, abonents[i].surname);  
        }
    }
    
    else
    {
        printf("\nThe book is empty!\n");
    }
}

void search_abonent (abonent abonents[], int max_ab_id)
{   
    if (max_ab_id > 0)
    {
        printf("\nEnter a surname: ");

        char key[STR_SIZE] = {0};
        scanf("%s", key);
        printf("\n");

        int flag = 0;
        for (int i = 0; i < max_ab_id; i++)
        {
            if (strncmp(abonents[i].surname, key, STR_SIZE) == 0)
            {
            
                printf("ID: %d Number: %d Name: %s Surname: %s\n", i, abonents[i].number, abonents[i].name, abonents[i].surname);
                flag = 1;
            }
        }

        if (flag == 0)
            printf("Not found abonent\n");
    }

    else 
    {
        printf("\nThe book is empty!\n");
    }    
}

int main()
{    
    int cur_ab_cnt = 0;
    int size_book = 1;
    abonent *book = (abonent *)malloc(size_book * sizeof(abonent));

    enum cmd
    {
        CMD_ADD = 1,
        CMD_DELETE,
        CMD_PRINT,
        CMD_SEARCH,
        CMD_EXIT,
    };
    
    enum cmd command = -1;
    do
    {
        menu();
        command = get_command();
        switch (command) 
        {
            case CMD_ADD:

                if (add_abonent(&book, &cur_ab_cnt, &size_book))
                {
                   // cur_ab_cnt++;
                   // size_book++;
                    printf("\nAbonent %d added\n\n", cur_ab_cnt);
                }

                break;

            case CMD_DELETE:

                if (delete_abonent(&book, cur_ab_cnt))
                {
                    cur_ab_cnt--;
                    size_book--;
                    printf("\nAbonent %d deleted\n\n", cur_ab_cnt);
                }

                break;

            case CMD_PRINT:

                book_print(book, cur_ab_cnt);
                break;

            case CMD_SEARCH:
                
                search_abonent(book, cur_ab_cnt);
                break;
        }

    } while (command != CMD_EXIT);

    free(book);
    return 0;
}

