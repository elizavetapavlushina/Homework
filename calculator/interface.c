#include <stdio.h>
#include "interface.h"
int get_command()
{
  printf("Enter a command: ");

  int command;
  scanf("%d", &command);
  while (command < 1 || command > 5)
  {
    printf("Incorrect input. Try again: ");
    scanf("%d", &command);
  }

  return command;
}

void interface()
{
  int command = 0;
  unsigned int result = 0;

  do
  {
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Exit\n");

    command = get_command();
    switch (command)
    {
      case 1:
        result = addition();                                                    
        printf("Result = %d\n", result);
        break;

      case 2:
        result = subtraction();                                                    
        printf("Result = %d\n", result);
        break;

      case 3:
        result = multiplication();                                                    
        printf("Result = %d\n", result);
        break;

      case 4:
        result = division();                                                    
        printf("Result = %d\n", result);
        break;
    }
  
  } while (command != 5);

}

int main()
{
  interface();
  return 0;
}
