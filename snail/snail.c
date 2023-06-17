#include <stdio.h>
#define N 7

int main() {
	
    int matrix[N][N];
    int i;
    int j;
    int col = 0, row = 0;
    int col_end = N - 1, row_end = N - 1; 
    int num = 1;
    
    while (col <= col_end && row <= row_end) {
    	
        for (i = col; i <= col_end; i++) {
            matrix[row][i] = num++;
        }
        row++;
        
        for (i = row; i <= row_end; i++) {
            matrix[i][col_end] = num++;
        }
        col_end--;

        if (row <= row_end) {
            for (i = col_end; i >= col; i--) {
                matrix[row_end][i] = num++;
            }
            row_end--;
        }
        if (col <= col_end) {
            for (i = row_end; i >= row; i--) {
                matrix[i][col] = num++;
            }
            col++;
        }
    }
    
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
