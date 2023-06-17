#include <stdio.h>
#define N 3

int main(){
	
	int matrix[N][N];
	int i;
	int j;
	int a = 1;
	
	for (i=0; i<N; i++){
		
		for (j=0; j<N; j++){
			matrix[i][j]=a;
			a++;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	return 0;
}
