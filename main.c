#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>


struct Matrix
{
    int r;
    int c;
    double** data;
    double** originaState;
    double Determinant;
    int Rang;

};

void cleanBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


double Det(struct Matrix matrix);

int TransformMatrixTriangle(struct Matrix matrix);

void TransponeMatrix(struct Matrix matrix);

void printMatrix(struct Matrix matrix);

int Rang(struct Matrix matrix);



int main(){

    int rows;
    int columns;
    printf("Please insert dimensions of matrix:\n");
    while(1){
        printf("Insert rows: ");
        if(scanf("%d", &rows) == 0 || rows <= 0){
            printf("rows must be an non negative intiger!\n");
            cleanBuffer();
            continue;
        }
        else{
            cleanBuffer();
            break;
        }
    }
    while(1){
        printf("Insert columns: ");
        if(scanf("%d", &columns) == 0 || columns <= 0){
            printf("columns must be a non negative intiger!\n");
            cleanBuffer();
            continue;
        }
        else{
            cleanBuffer();
            break;
        }
    }

    double** data = malloc(rows*sizeof(double*));
    for(int i = 0; i<rows; i++){
        data[i] = malloc(columns*sizeof(double));
    }

    for(int r = 0; r<rows; r++){
        printf("Enter elements of row %d one by one:\n", r+1);
        for(int c = 0; c<columns; c++){
            while(1){
                printf("Enter element %d%d: ", r+1, c+1);
                if(scanf("%lf", &data[r][c]) == 0){
                    printf("The inserted value must be a number!\n");
                    cleanBuffer();
                    continue;
                }
                else{
                    cleanBuffer();
                    break;
                }
            }
        }
    }
    struct Matrix mr = {rows, columns, data, data};

    

    for(int i = 0; i<rows; i++){
        free(data[i]);
    }
    free(data);

    // if(mr.r == mr.c){
    //     printf("The determinant of matrix:\n");
    //     printMatrix(mr);
    //     printf("Which becomes:\n");
    //     double det = Det(mr);
    //     printMatrix(mr);
    //     printf("is %.2lf", det);
    // }
    // else{
    //     printf("This matrix is not square, but it becomes a trapezoid like this: \n");
    //     TransformMatrixTriangle(mr);
    //     printMatrix(mr);
    // }


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

int Rang(struct Matrix matrix){
    int maxRang = matrix.r;
    bool isZero = true;
    TransformMatrixTriangle(matrix);
    for(int r = matrix.r-1; r >= 0; r--)
    {
        for(int c = 0; c < matrix.c; c++)
        {
            if(matrix.data[r][c] != 0){
                isZero = false;
                break;
            }
        }
        if(isZero){
            maxRang --;
        }
        else{
            isZero = true;
        }
    }
    return maxRang;
}

// void TransponeMatrix(struct Matrix m) {
//     struct Matrix result;
//     result.r = m.c; 
//     result.c = m.r; 


//     result.data = malloc(result.r * sizeof(double*));
    
//     for (int i = 0; i < result.r; i++) {

//         result.data[i] = malloc(result.c * sizeof(double));
        

//         for (int j = 0; j < result.c; j++) {

//             result.data[i][j] = m.data[j][i];
//         }
//     }
// }

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
