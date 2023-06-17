#include <stdio.h>
#define N 3

int main() {
	
    int matrix[N][N];
    int i;
    int j;
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
        	
            if (i >= j) {
                matrix[i][j] = 0;
            }
	    else {
                matrix[i][j] = 1;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
