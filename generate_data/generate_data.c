#include "generate_data.h"
#include <time.h>

void generate_train_data(int side_length, float **matrix1, float **matrix2){

    // Letter A matrix
    float copy1[8][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1,  1,  1, -1, -1, -1, -1},
        {-1,  1, -1, -1,  1, -1, -1, -1},
        { 1, -1, -1, -1, -1,  1, -1, -1},
        { 1,  1,  1,  1,  1,  1, -1, -1},
        { 1, -1, -1, -1, -1,  1, -1, -1},
        { 1, -1, -1, -1, -1,  1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1}
    };

    // Letter B matrix
    float copy2[8][8] = {
        {-1, -1, -1, -1, -1, -1, -1, -1},
        {-1,  1,  1,  1,  1,  -1, -1, -1},
        {-1,  1, -1, -1, -1,  1, -1, -1},
        {-1,  1, -1, -1, -1,  1, -1, -1},
        {-1,  1,  1,  1,  1,  -1, -1, -1},
        {-1,  1, -1, -1, -1,  1, -1, -1},
        {-1,  1, -1, -1, -1,  1, -1, -1},
        {-1,  1,  1,  1,  1,  -1, -1, -1}
    };
    // printf("Matriz 1: \n");
    for(int i = 0; i < side_length; i++){
        // printf("\n");
        for(int j = 0; j < side_length; j++){
            matrix1[i][j] = copy1[i][j];
            // printf("%f ", matrix1[i][j]);
        }
    }
    // printf("\nMatriz 2: \n");
    for(int i = 0; i < side_length; i++){
        // printf("\n");
        for(int j = 0; j < side_length; j++){
            matrix2[i][j] = copy2[i][j];
            // printf("%f ", matrix2[i][j]);
        }
    }
}

void generate_test_data(int side_length, float **matrix1, float **matrix2, int swap){

    int randomness_weight;
    int row, col, index;
    srand(time(NULL));


    if(isEmpty(matrix1) || isEmpty(matrix2)){
        if(swap)
            generate_train_data(8, matrix2, matrix1);
        else
            generate_train_data(8, matrix1, matrix2);
    }

    // generate_train_data(8, matrix1, matrix2);

    printf("\nInput how much noise you want in a Scale from 0 to 7\n");
    printf("0 is no noise and 7 means a quarter of the matrix is going to be randomnly affected\n");
    printf("Each degree is equivalent to 2 pixels potentially changed\n");
    scanf(" %d", &randomness_weight);

    int used1[64] = {0}; // Array to keep track of used indices
    int used2[64] = {0};

    printf("\nTest1:\n");
    for (int i = 0; i < randomness_weight; i++) {
        for (int j = 0; j < 2; j++) {
            do {
                row = rand() % 8;
                col = rand() % 8;
                index = row * 8 + col; // Calculate a unique index for the 2D array
            } while (used1[index]); // Keep generating until we find an unused index

            used1[index] = 1; // Mark this index as used
            
            printf("[%d][%d]\n", row, col);

            matrix1[row][col] = matrix1[row][col] == 1 ? -1 : 1;
        }
    }
    printf("\nTest2:\n");
    for (int i = 0; i < randomness_weight; i++) {
        for (int j = 0; j < 2; j++) {
            do {
                row = rand() % 8;
                col = rand() % 8;
                index = row * 8 + col; // Calculate a unique index for the 2D array
            } while (used2[index]); // Keep generating until we find an unused index

            used2[index] = 1; // Mark this index as used
            
            printf("[%d][%d]\n", row, col);

            matrix2[row][col] = matrix2[row][col] == 1 ? -1 : 1;
        }
    }

    getchar();
}