#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

typedef struct Matrix {
    uint32_t height;
    uint32_t width;
    double** values;
} Matrix;

const uint32_t FIRST_POSSIBLE_VALUE = 0;


ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width){
    //check if wisth and height are valid
    if(width < FIRST_POSSIBLE_VALUE + 1 || height < FIRST_POSSIBLE_VALUE + 1){
        return ERROR_NEG_WIDTH_OR_HEIGHT;
    }

    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }

    *matrix = NULL;

    //allocate memory for the matrix
    *matrix = (PMatrix) malloc(sizeof(Matrix));

    if(*matrix == NULL){
        return ERROR_FAILED_MEMORY_ALOCATION;
    }

    (*matrix)->height = height;
    (*matrix)->width = width;

    //allocate memory for the array of the arrays
    (*matrix)->values = (double**) malloc(height * sizeof(double*));
    if((*matrix)->values == NULL){
        free(*matrix);
        return ERROR_FAILED_MEMORY_ALOCATION;
    }
    
    //allocate memory for the arrays insude the array
    for (uint32_t i = 0; i < height; ++i){
        ((*matrix)->values)[i] = (double*) calloc(width, sizeof(double));
        if(((*matrix)->values)[i] == NULL){
            for(uint32_t j=0; j < i; ++j){
                free(((*matrix)->values)[j]);
            }
            free((*matrix)->values);
            free(*matrix);
            return ERROR_FAILED_MEMORY_ALOCATION;
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source){

    if(source == NULL){
        return ERROR_NULL_POINTER;
    }

    matrix_create(result, source->height, source->width);

    for(uint32_t i = 0; i < source->height; ++i){
        for(uint32_t j = 0; j < source->width; ++j){
            matrix_setValue(*result, i, j, (source->values)[i][j]);
            // double* newVal = 0;
            // matrix_getValue(source, i, j, newVal);
            // matrix_setValue(*result, i, j, *newVal);
        }
    }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix){

    if(matrix == NULL){
        return;
    }

    //free the arrays  of the values
    for (uint32_t i = 0; i < (matrix->height); ++i){
        free((matrix->values)[i]);
    }

    //free the array of the arrays
    free(matrix->values);

    //free the matrix
    free(matrix);
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result){
    
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }
    
    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result){
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }
    
    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value){
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }

    matrix->values[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value){
    
    //check for errors
    if(matrix == NULL){
        //printf("matrix_getValue_1\n");
        return ERROR_NULL_POINTER;
    }

    if(rowIndex < FIRST_POSSIBLE_VALUE || colIndex < FIRST_POSSIBLE_VALUE){
        //printf("matrix_getValue_2\n");
        return ERROR_NEG_WIDTH_OR_HEIGHT;
    }

    if(value == NULL){
        //printf("matrix_getValue_3\n");
        return ERROR_NULL_POINTER;
    }

    for(uint32_t i = 0; i < matrix->height; ++i){
        if(matrix->values[i] == NULL){
            //printf("matrix_getValue_4\n");
            return ERROR_NULL_POINTER;
        }
    }

    *value = (matrix->values)[rowIndex][colIndex];
    //printf("matrix_getValue_5\n");
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    if (lhs == NULL || rhs == NULL){
        //printf("matrix_add_1\n");
        return ERROR_NULL_POINTER;
    }

    //alocate memoty for thr new matrix
    matrix_create(result, lhs->height, lhs->width);

    //calculate the values and add them to the new natrix
    for (uint32_t i = 0; i < lhs->height; ++i){
        for (uint32_t j = 0; j < rhs->width; ++j){
            matrix_setValue(*result, i, j, lhs->values[i][j] + rhs->values[i][j]);
        }
    }
    //printf("matrix_add_3\n");
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    if (lhs == NULL || rhs == NULL){
        //printf("matrix_multiplyMatrices_1\n");
        return ERROR_NULL_POINTER;
    }

    if(lhs->width != rhs->height){
         //printf("matrix_multiplyMatrices_2\n");
        return ERROR_CAN_NOT_MULTI;
    }

    //alocate memoty for thr new matrix
    matrix_create(result, lhs->height, rhs->width);

    if(result == NULL){
        //printf("matrix_multiplyMatrices_3\n");
        return ERROR_NULL_POINTER;
    }

    for(uint32_t i = 0; i < (*result)->height; ++i){
        //printf("aaaaaa\n");
        for (uint32_t j = 0; j < (*result)->width; ++j){
            //printf("bbbbb\n");
            double calculator = 0;
            for(uint32_t k = 0; k < lhs->width; ++k){
                calculator += lhs->values[i][k] * rhs->values[k][j];
                // double val1;
                // double val2;
                // matrix_getValue(lhs, i, k, &val1);
                // matrix_getValue(rhs, k, j, &val2);
                // calculator += (val1 * val2);
            }
            matrix_setValue(*result, i, j, calculator);
        }
    }
    //printf("matrix_multiplyMatrices_5");
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar){
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }

    for (uint32_t i = 0; i < matrix->height; ++i){
        for (uint32_t j = 0; j < matrix->width; ++j){
            double newVal = 0;
            matrix_getValue(matrix, i, j, &newVal);
            matrix_setValue(matrix, i, j, newVal * scalar);
        }
    }

    return ERROR_SUCCESS;

}




