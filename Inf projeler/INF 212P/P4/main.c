#include <stdio.h>
#include <stdlib.h>
#include "matrix_operations.h"

int main() {
    int i, j, k;
    int rows, cols;
    printf("Enter rows and columns for matrix: ");
    scanf("%d %d", &rows, &cols);

    double **matrix = (double **)malloc(rows * sizeof(double *));
    double **orgmatrix = (double **)malloc(rows * sizeof(double *));
    double **summatrix = (double **)malloc(rows * sizeof(double *));
    double **org2matrix = (double **)malloc(rows * sizeof(double *));
    
    for (i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        orgmatrix[i] = (double *)malloc(cols * sizeof(double));
        summatrix[i] = (double *)malloc(cols * sizeof(double));
        org2matrix[i] = (double *)malloc(cols * sizeof(double));
        if (matrix[i] == NULL || orgmatrix[i] == NULL || summatrix[i] == NULL || org2matrix[i] == NULL) {
            printf("Memory allocation failed\n");
            for (k = 0; k < i; k++) {
                free(matrix[k]);
                free(orgmatrix[k]);
                free(summatrix[k]);
                free(org2matrix[k]);
            }
            free(matrix);
            free(orgmatrix);
            free(summatrix);
            free(org2matrix);
            return 1;
        }
    }

    // Inputs
    printf("Enter the elements of the matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%lf", &orgmatrix[i][j]);
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            matrix[i][j] = orgmatrix[i][j];
            org2matrix[i][j] = orgmatrix[i][j];
        }
    }
    
    double value;
    int rowIndex, colIndex;
    printf("Value to search in the matrix: ");
    scanf("%lf", &value);
    searchvalue(matrix, rows, cols, value, &rowIndex, &colIndex);
    if (rowIndex != -1 && colIndex != -1) {
        printf("Value %lf index (%d, %d)\n", value, rowIndex, colIndex);
    } else {
        printf("Value %lf not found in the matrix\n", value);
    }

    int nonRepeated = countnonrep(matrix, rows, cols);
    printf("Number of non-repeated elements: %d\n", nonRepeated);

    double minElement = minel(matrix, rows, cols);
    printf("Minimum element in the matrix: %lf\n", minElement);

    double *maxValues = (double *)malloc(rows * sizeof(double));
    maxsatir(matrix, rows, cols, maxValues);
    printf("Maximum element of each row:\n");
    for (i = 0; i < rows; i++) {
        printf("Row %d: %lf\n", i + 1, maxValues[i]);
    }
    free(maxValues);

    bubbleSortRows(matrix, rows, cols);
    printf("Row in descending order:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }

    // Transpose
    double **transposed = (double **)malloc(cols * sizeof(double *));
    for (i = 0; i < cols; i++) {
        transposed[i] = (double *)malloc(rows * sizeof(double));
    }
    transposeArray(matrix, rows, cols, transposed);
    printf("Transpose of the matrix:\n");
    for (i = 0; i < cols; i++) {
        for (j = 0; j < rows; j++) {
            printf("%lf ", transposed[i][j]);
        }
        printf("\n");
    }

    // Sum of transpose and original matrix
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            summatrix[i][j] = transposed[j][i] + orgmatrix[i][j];
        }
    }
    printf("Sum of transpose and original matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("%lf ", summatrix[i][j]);
        }
        printf("\n");
    }
    
    double **result;
    multiplyMatrices(matrix, rows, cols, orgmatrix, rows, cols, &result);
    if (result != NULL) {
        printf("Matrix multiplication result:\n");
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                printf("%lf ", result[i][j]);
            }
            printf("\n");
        }

        // Free memory for the result matrix
        for (i = 0; i < rows; i++) {
            free(result[i]);
        }
        free(result);
    }
    
    // Free memory for transposed matrix
    for (i = 0; i < cols; i++) {
        free(transposed[i]);
    }
    free(transposed);

    if (birim(matrix, rows, cols)) {
        printf("The matrix is an identity matrix\n");
    } else {
        printf("The matrix is not an identity matrix\n");
    }

    if (isSymmetricMatrix(matrix, rows, cols)) {
        printf("The matrix is a symmetric matrix\n");
    } else {
        printf("The matrix is not a symmetric matrix\n");
    }

    // LU Decomposition
    double **L = (double **)malloc(rows * sizeof(double *));
    double **U = (double **)malloc(rows * sizeof(double *));
    for (i = 0; i < rows; i++) {
        L[i] = (double *)malloc(cols * sizeof(double));
        U[i] = (double *)malloc(cols * sizeof(double));
    }
    LUdecomposition(org2matrix, L, U, rows);

    printf("LU Decomposition result:\n");
    printf("L matrix:\n");
    printMatrix(L, rows);

    printf("U matrix:\n");
    printMatrix(U, rows);

    for (i = 0; i < rows; i++) {
        free(L[i]);
        free(U[i]);
    }
    free(L);
    free(U);

    // Free memory
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
        free(orgmatrix[i]);
        free(summatrix[i]);
        free(org2matrix[i]);
    }
    free(matrix);
    free(orgmatrix);
    free(summatrix);
    free(org2matrix);

    return 0;
}

