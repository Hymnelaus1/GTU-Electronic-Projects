#include "matrix_operations.h"
#include <stdio.h>
#include <stdlib.h>

int i, j, k, l;

void searchvalue(double **array, int rows, int cols, double value, int *rowIndex, int *colIndex) {
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (array[i][j] == value) {
                *rowIndex = i;
                *colIndex = j;
                return;
            }
        }
    }
    *rowIndex = -1;
    *colIndex = -1;
}

int countnonrep(double **array, int rows, int cols) {
    int count = 0;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            double currentElement = array[i][j];
            int repeated = 0;
            for (k = 0; k < rows; k++) {
                for (l = 0; l < cols; l++) {
                    if (k != i || l != j) {
                        if (array[k][l] == currentElement) {
                            repeated = 1;
                            break;
                        }
                    }
                }
                if (repeated) break;
            }
            if (!repeated) {
                count++;
            }
        }
    }
    return count;
}

double minel(double **array, int rows, int cols) {
    double min = array[0][0];
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (array[i][j] < min) {
                min = array[i][j];
            }
        }
    }
    return min;
}

void maxsatir(double **array, int rows, int cols, double maxValues[]) {
    for (i = 0; i < rows; i++) {
        double max = array[i][0];
        for (j = 1; j < cols; j++) {
            if (array[i][j] > max) {
                max = array[i][j];
            }
        }
        maxValues[i] = max;
    }
}

void bubbleSortRows(double **array, int rows, int cols) {
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols - 1; j++) {
            for (k = 0; k < cols - j - 1; k++) {
                if (array[i][k] < array[i][k + 1]) {
                    double temp = array[i][k];
                    array[i][k] = array[i][k + 1];
                    array[i][k + 1] = temp;
                }
            }
        }
    }
}

void transposeArray(double **array, int rows, int cols, double **transposed) {
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            transposed[j][i] = array[i][j];
        }
    }
}

void multiplyMatrices(double **array1, int rows1, int cols1, double **array2, int rows2, int cols2, double ***result) {
    if (cols1 != rows2) {
        printf("Matrix multiplication not possible.\n");
        *result = NULL;
        return;
    }

    double **resultMatrix = (double **)malloc(rows1 * sizeof(double *));
    for (i = 0; i < rows1; i++) {
        resultMatrix[i] = (double *)malloc(cols2 * sizeof(double));
    }

    for (i = 0; i < rows1; i++) {
        for (j = 0; j < cols2; j++) {
            resultMatrix[i][j] = 0;
            for (k = 0; k < cols1; k++) {
                resultMatrix[i][j] += array1[i][k] * array2[k][j];
            }
        }
    }

    *result = resultMatrix;
}

int birim(double **array, int rows, int cols) {
    if (rows != cols)
        return 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (i == j) {
                if (array[i][j] != 1)
                    return 0;
            } else {
                if (array[i][j] != 0)
                    return 0;
            }
        }
    }
    return 1;
}

int isSymmetricMatrix(double **array, int rows, int cols) {
    if (rows != cols)
        return 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (array[i][j] != array[j][i])
                return 0;
        }
    }
    return 1;
}

void LUdecomposition(double **A, double **L, double **U, int n) {
	int i;
    for (i = 0; i < n; i++) {
    	int k;
        for (k = i; k < n; k++) {
            double sum = 0;
            int j;
            for (j = 0; j < i; j++) {
                sum += (L[i][j] * U[j][k]);
            }
            U[i][k] = A[i][k] - sum;
        }

        for (k = i; k < n; k++) {
            if (i == k)
                L[i][i] = 1;
            else {
                double sum = 0;
                int j;
                for (j = 0; j < i; j++) {
                    sum += (L[k][j] * U[j][i]);
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}



void printMatrix(double** matrix, int n) {
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if(matrix[i][j] > 100){
            	printf("    0.00");
			}
			else{
				printf("%8.3f ", matrix[i][j]);	
			}
        }
        printf("\n");
    }
    printf("\n");
}

