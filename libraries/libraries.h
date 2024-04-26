#include <stdio.h>
#include <stdlib.h>
#include "../generate_data/generate_data.h"

#define column_size 64
#define row_size 2

void printMatrix(float **matrix);
void zero_fill(float *vector);
void zero_fill_matrix(float **matrix);
int isEmpty(float **matrix);
void clear_screen();

float** createMatrix(int side_length);
void freeMatrix(float **matrix, int side_length);

float** flat_entries_vector(float **matrixA, float **matrixB);
float* hebb_learning_rule(float **training_data, float outputs[2], float* bias);
void rna_testing(float **testing_data, float* weights, float bias);