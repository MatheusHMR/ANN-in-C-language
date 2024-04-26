#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generate_train_data(int side_length, float **matrix1, float **matrix2);

void generate_test_data(int side_length, float **matrix1, float **matrix2, int swap);

float** customize_matrix(int randomness_weight, float** matrix);