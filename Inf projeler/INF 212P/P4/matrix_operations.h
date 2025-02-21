#ifndef MY_ARRAY_LIBRARY_H
#define MY_ARRAY_LIBRARY_H

void searchvalue(double **array, int rows, int cols, double value, int *rowIndex, int *colIndex);
int countnonrep(double **array, int rows, int cols);
double minel(double **array, int rows, int cols);
void maxsatir(double **array, int rows, int cols, double maxValues[]);
void bubbleSortRows(double **array, int rows, int cols);
void transposeArray(double **array, int rows, int cols, double **transposed);
void multiplyMatrices(double **array1, int rows1, int cols1, double **array2, int rows2, int cols2, double ***result);
int birim(double **array, int rows, int cols);
int isSymmetricMatrix(double **array, int rows, int cols);
void LUdecomposition(double **A, double **L, double **U, int n);

#endif /* MY_ARRAY_LIBRARY_H */

