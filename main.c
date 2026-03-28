#include<stdio.h>
#include<stdlib.h>
#include<math.h>


struct Matrix
{
    int r;
    int c;
    double** data;

};


double Det(struct Matrix matrix);

int TransformMatrixTriangle(struct Matrix matrix);

void printMatrix(struct Matrix matrix);


int main(){

    int rows;
    int columns;
    printf("Please insert dimensions of matrix:\n");
    printf("Insert rows: ");
    scanf("%d", &rows);
    printf("Insert columns: ");
    scanf("%d", &columns);

    double** data = malloc(rows*sizeof(double*));
    for(int i = 0; i<rows; i++){
        data[i] = malloc(columns*sizeof(double));
    }

    for(int r = 0; r<rows; r++){
        printf("Enter elements of row %d one by one:\n", r+1);
        for(int c = 0; c<columns; c++){
            printf("Enter element %d%d: ", r+1, c+1);
            scanf("%lf", &data[r][c]);
        }
    }

    struct Matrix mr = {rows, columns, data};

    if(mr.r == mr.c){
        printf("The determinant of matrix:\n");
        printMatrix(mr);
        printf("Which becomes:\n");
        double det = Det(mr);
        printMatrix(mr);
        printf("is %.2lf", det);
    }



    return 0;

    
}

int TransformMatrixTriangle(struct Matrix matrix) {
    int sign = 1;

    for (int c = 0; c < matrix.r && c < matrix.c; c++) {
        int pivotRow = c;
        while (pivotRow < matrix.r && matrix.data[pivotRow][c] == 0) {
            pivotRow++;
        }

        if (pivotRow == matrix.r) continue; 

        if (pivotRow != c) {
            double* temp = matrix.data[c];
            matrix.data[c] = matrix.data[pivotRow];
            matrix.data[pivotRow] = temp;
            sign *= -1;
        }

        for (int r = c + 1; r < matrix.r; r++) {
            if (matrix.data[r][c] == 0) continue;

            double multiplier = -matrix.data[r][c] / matrix.data[c][c];
            
            for (int i = c; i < matrix.c; i++) {
                matrix.data[r][i] += multiplier * matrix.data[c][i];
            }
            matrix.data[r][c] = 0;
        }
    }
    return sign;
}



double Det(struct Matrix matrix){
    double determinant = TransformMatrixTriangle(matrix);
    for(int i = 0; i<matrix.r; i++){
         determinant*=matrix.data[i][i];
    }
    return determinant;
}

void printMatrix(struct Matrix matrix){
    for(int r = 0; r<matrix.r; r++)
    {
        for(int c = 0; c<matrix.c; c++)
        {
            printf(" %.2lf ", matrix.data[r][c]);
        }
        printf("\n");
    }
}
