#include <stdio.h>
#define N 8

int main(){
	
	int array[N];
	int i;
	int a;
	
	for (i = 0; i < N; i++){
		array[i] = i + 1;
		printf("%d ", array[i]);
	}
	printf("\n");
	
	for (i = 0; i < N/2; i++){
		a = array[i];
		array[i] = array[N-i-1];
		array[N-i-1] = a;
	}
	for (i = 0; i < N; i++){
		printf("%d ", array[i]);
	}
	return 0;
}
