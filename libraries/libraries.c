#include "libraries.h"

void clear_screen(){
    printf("\033c\n");
}

int isEmpty(float **matrix){
    int flag = 1;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(matrix[i][j] != 0)
                flag = 0;
        }
    }
    
    return flag;
}

float** createMatrix(int side_length){
    float **matrix = (float**)malloc(sizeof(float*)*side_length);

    for (int i = 0; i < side_length; i++){
        matrix[i] = (float*)malloc(sizeof(float)*side_length);
    }

    zero_fill_matrix(matrix);
    
    return matrix;
}

void freeMatrix(float **matrix, int side_length){

    for(int i = 0; i < side_length; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void printMatrix(float **matrix) {
    printf("\n");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if(matrix[i][j] == 1)
                printf("X");
            else
                printf(" ");
        }
        printf("\n");
    }
}

void zero_fill(float *vector){
    // Zerar os pesos
    for (int i = 0; i < 64; i++){
        vector[i] = 0;
    }
}

void zero_fill_matrix(float **matrix){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            matrix[i][j] = 0;
        }
    }
}

float** flat_entries_vector(float **matrixA, float **matrixB){

    float **entries = (float**)malloc(sizeof(float*)*2);
    entries[0] = (float*)malloc(sizeof(float)*64);
    entries[1] = (float*)malloc(sizeof(float)*64);

    // Achatar a matriz A
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            entries[0][i * 8 + j] = matrixA[i][j];
        }
    }

    // Achatar a matriz B
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            entries[1][i * 8 + j] = matrixB[i][j];
        }
    }

    return entries;
}

float* hebb_learning_rule(float **training_data, float outputs[2], float *bias){

    //============= APLICAÇÃO DA REGRA=================
    //Passos para calcular os pesos:
    //Multiplicar entradas e saídas [entradas de A à saída equivalente de A e entradas de B à sua saída equivalente também]
    //Somar aos pesos atuais

    float delta_weights[64], *weights;
    float delta_bias;

    weights = (float*)malloc(sizeof(float)*64);

    zero_fill(weights);

    int col, row;

    for (row = 0; row < row_size; row++){

        for (col = 0; col < 64; col++){
            delta_weights[col] = training_data[row][col]*outputs[row];
        }
        delta_bias = outputs[row];
        
        for (col = 0; col < column_size; col++){
            weights[col] = weights[col] + delta_weights[col];
        }
        //Cálculo do bias (viés):
        //Soma-se a saída esperada de cada entrada ao bias (o delta_bias que recebe o valor de cada saída no caso)
        //1 para A e -1 para B

        *bias = *bias + delta_bias; //content of bias is updated
    }

    return weights;
}

void rna_testing(float **testing_data, float* weights, float bias){

    int row, col, test_output[2];
    float delta_test;

    for (row = 0; row < 2; row++){
        delta_test = 0;
        for (col = 0; col < 64; col++){
            delta_test = delta_test + (weights[col]*testing_data[row][col]);   
        }
        delta_test = delta_test + bias;
        if(delta_test>=0){
            test_output[row] = 1;
        } else {
            test_output[row] = -1;
        }
    }

    printf("\n\n\n\n");
    printf("\nPossible Outputs:  1(A)     -1(B)\n");
    printf("\nReceived Outputs:  First Matrix:        Second Matrix:\n");
    printf("                          %i                     %i\n\n", test_output[0],test_output[1]);
}