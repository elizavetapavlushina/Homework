#include <stdio.h>
//#include "operations.h"
int division()
{
  int num1;
  int num2;
  unsigned int result;

  printf("Input the first number: ");
  scanf("%d", &num1);
  printf("\n");

  printf("Input the second number: ");
  scanf("%d", &num2);
  printf("\n");

  result = num1 / num2;

  return result;

}
