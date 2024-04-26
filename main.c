#include "libraries/libraries.h"
#include "libraries/libraries.c"
#include "generate_data/generate_data.c"

int main() {

    float delta_bias, bias;
    
    float outputs[2] = {1,-1};
    float **training_data, **testing_data;
    float delta_test;
    float *trained_sinaptic_weights;

    int col, row, test_output[2], res, sample_number, swap;
    char confirmation;

    float **letterA, **letterB;
    float **test1 = NULL, **test2 = NULL;
    
    letterA = createMatrix(8);
    letterB = createMatrix(8);

    generate_train_data(8, letterA, letterB);

    test1 = createMatrix(8);
    test2 = createMatrix(8);

    printf("\nLetter A:\n");
    printMatrix(letterA);
    printf("\nLetter B:\n");
    printMatrix(letterB);

    
    training_data = flat_entries_vector(letterA, letterB);
    testing_data = flat_entries_vector(test1, test2);

    trained_sinaptic_weights = hebb_learning_rule(training_data, outputs, &bias);

    rna_testing(testing_data, trained_sinaptic_weights, bias);

    do {
        clear_screen();
        printf("================ * HEBBIAN LEARNING RULE * =================\n");
        printf("============== RECOGNIZING LETTERS \"A\" AND \"B\" ==============\n");
        printf("============================================================\n");
        printf("***         Select an option from the list below         ***\n");
        printf("1 - RUN LETTER RECOGNITION ARTIFICAL NEURAL NEWTORK MODEL\n");
        printf("2 - PRINT LETTER \"A\" MODEL\n");
        printf("3 - PRINT LETTER \"B\" MODEL\n");
        printf("4 - CHECK CURRENT TESTING DATA\n");
        printf("5 - GENERATE \"A\" AND \"B\" LETTERS WITH NOISE TO TEST RNA MODEL\n");
        printf("6 - RESET TESTING DATA (FILL IT WITH ZEROS)\n");
        printf("7 - LEAVE MENU\n\n\n");

        printf("YOUR ANSWER:  ");
        scanf(" %d", &res);
        printf("CHOSEN ANSWER:  %d", res);
        getchar();
        clear_screen();

        switch (res){
            
        case 1:
            printMatrix(test1);
            printMatrix(test2);
            getchar();
            rna_testing(testing_data, trained_sinaptic_weights, bias);
            getchar();
            clear_screen();
            break;

        case 2:
            printMatrix(letterA);
            getchar();
            clear_screen();
            break;
        
        case 3:
            printMatrix(letterB);
            getchar();
            clear_screen();
            break;

        case 4:
            printf("\nTest1:\n");
            printMatrix(test1);
            printf("\nTest2:\n");
            printMatrix(test2);
            getchar();
            clear_screen();
            break;
        
        case 5:
            clear_screen();

            if(isEmpty(test1) || isEmpty(test2)){
                printf("Do you want to swap A and B for testing?\n");
                printf("That means if you input empty matrixes for testing, test1 is B and test2 is A, now.\n");
                printf("1 - FOR YES;  0 - FOR NO\n\n");
                scanf(" %d", &swap);
            }

            generate_test_data(8, test1, test2, swap);
            getchar();
            testing_data = flat_entries_vector(test1, test2);
            clear_screen();
            break;

        case 6:
            zero_fill_matrix(test1);
            zero_fill_matrix(test2);
            getchar();
            break;
        case 7:

            printf("Are you sure you wanna leave?  y - for yes; n - for no\n");
            scanf(" %c", &confirmation);

            if(confirmation == 'n')
                res = 0;

            break;
        }

    }while(res != 7);

    //Freeing memory that has been allocated before in the program
    free(training_data[0]);
    free(training_data[1]);
    free(training_data);
    free(trained_sinaptic_weights);
    freeMatrix(letterA, 8);
    freeMatrix(letterB, 8);

    return 0;
}
