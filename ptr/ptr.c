#include <stdio.h>

int main(){
	
	unsigned int a = 270533154;
	char *ptr;
	
	ptr = &a;
	printf("first byte: %d\n", *ptr);
	ptr++;
	printf("second byte: %d\n", *ptr);
	ptr++;
	printf("third byte: %d\n", *ptr);
	ptr++;
	printf("fourth byte: %d\n\n", *ptr);
	
	ptr -= 1;
	*ptr = 10;
	
	ptr = &a;
	printf("first byte: %d\n", *ptr);
	ptr++;
	printf("second byte: %d\n", *ptr);
	ptr++;
	printf("third byte: %d\n", *ptr);
	ptr++;
	printf("fourth byte: %d\n", *ptr);

	return 0;
}
