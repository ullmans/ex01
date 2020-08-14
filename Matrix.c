#include <stdio.h>
#include "Matrix.h"

typedef struct Matrix {
    uint32_t height;
    uint32_t width;
    int** values;
} Matrix;

const uint32_t FIRST_POSSIBLE_VALUE = 0;


ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width){
    //check if wisth and height are valid
    if(width < FIRST_POSSIBLE_VALUE || height < FIRST_POSSIBLE_VALUE){
        return ERROR_NEG_WIDTH_OR_HEIGHT;
    }

    //for safety
    matrix = NULL;

    //allocate memory for the matrix
    *matrix = (PMatrix) malloc(sizeof(Matrix));
    if(matrix = NULL){
        return ERROR_FAILED_MEMORY_ALOCATION;
    }
    (*matrix)->height = height;
    (*matrix)->width = width;

    //allocate memory for the array of the arrays
    (*matrix)->values =  (double**)malloc (height * sizeof(double*));
    if((*matrix)->values = NULL){
        free(*matrix);
        return ERROR_FAILED_MEMORY_ALOCATION;
    }
    
    //allocate memory for the arrays insude the array
    for (uint32_t i = 0; i < height; ++i){
        ((*matrix)->values)[i] = (double*) calloc (width, sizeof(double));
        if(((*matrix)->values)[i] = NULL){
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

    if(source = NULL){
        return ERROR_NULL_OUTPUT_POINTER;
    }

    //for safety
    result = NULL;

    //change th poiner to point the cpied matrix
    *result = source;

    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix){

    if(matrix = NULL){
        return ERROR_NULL_OUTPUT_POINTER;
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
    
    if(matrix = NULL){
        return ERROR_NULL_OUTPUT_POINTER;
    }

    //for safety
    result = NULL;
    
    *result = matrix->height;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result){
    if(matrix = NULL){
        return ERROR_NULL_OUTPUT_POINTER;
    }

    //for safety
    result = NULL;
    
    *result = matrix->width;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double value){
    if(matrix = NULL){
        return ERROR_NULL_OUTPUT_POINTER;
    }

    if(rowIndex < 0 || colIndex < 0){
        return ERROR_NEG_WIDTH_OR_HEIGHT;
    }

    matrix->values[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

//ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex, double* value);

//ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs);

//ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs);

//ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar);




