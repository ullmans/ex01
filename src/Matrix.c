#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

typedef struct Matrix {
    uint32_t height;
    uint32_t width;
    double** values;
} Matrix;

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width){
    //check if width and height are valid
    if(height < 1){
        return ERROR_NEGATIVE_HEIGHT;
    }
    if(width < 1){
        return ERROR_NEGATIVE_WIDTH;
    }

    //allocate memory for the matrix
    *matrix = (PMatrix) malloc(sizeof(Matrix));

    //check the allocate worked well
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
    
    //allocate memory for the arrays inside the array
    for (uint32_t i = 0; i < height; ++i){
        ((*matrix)->values)[i] = (double*) calloc(width, sizeof(double));
        if(((*matrix)->values)[i] == NULL){
            for(uint32_t j = 0; j < i; ++j){
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

    ErrorCode errorCode =  matrix_create(result, source->height, source->width);
    if(errorCode != ERROR_SUCCESS){
        return errorCode;
    }

    for(uint32_t i = 0; i < source->height; ++i){
        for(uint32_t j = 0; j < source->width; ++j){
            ErrorCode errorCode = matrix_setValue(*result, i, j, (source->values)[i][j]);
            if(errorCode != ERROR_SUCCESS){
                return errorCode;
            }
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
        return ERROR_NULL_POINTER;
    }

    if(rowIndex < 0){
        return ERROR_NEGATIVE_HEIGHT;
    }
    if(colIndex < 0){
        return ERROR_NEGATIVE_WIDTH;
    }

    if(value == NULL){
        return ERROR_NULL_POINTER;
    }

    for(uint32_t i = 0; i < matrix->height; ++i){
        if(matrix->values[i] == NULL){
            return ERROR_NULL_POINTER;
        }
    }

    *value = (matrix->values)[rowIndex][colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    if (lhs == NULL || rhs == NULL){
        return ERROR_NULL_POINTER;
    }

    //alocate memoty for thr new matrix
    ErrorCode errorCode = matrix_create(result, lhs->height, lhs->width);
    if(errorCode != ERROR_SUCCESS){
        return errorCode;
    }

    //calculate the values and add them to the new natrix
    for (uint32_t i = 0; i < lhs->height; ++i){
        for (uint32_t j = 0; j < rhs->width; ++j){
            ErrorCode errorCode = matrix_setValue(*result, i, j, lhs->values[i][j] + rhs->values[i][j]);
            if(errorCode != ERROR_SUCCESS){
                return errorCode;
            }
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    if (lhs == NULL || rhs == NULL){
        return ERROR_NULL_POINTER;
    }

    if(lhs->width != rhs->height){
        return ERROR_CAN_NOT_MULTIPLY;
    }

    //alocate memoty for thr new matrix
    ErrorCode errorCode = matrix_create(result, lhs->height, rhs->width);
    if(errorCode != ERROR_SUCCESS){
        return errorCode;
    }

    if(result == NULL){
        return ERROR_NULL_POINTER;
    }

    for(uint32_t i = 0; i < (*result)->height; ++i){
        for (uint32_t j = 0; j < (*result)->width; ++j){
            double calculator = 0;
            for(uint32_t k = 0; k < lhs->width; ++k){
                calculator += lhs->values[i][k] * rhs->values[k][j];
            }
            ErrorCode errorCode = matrix_setValue(*result, i, j, calculator);
            if(errorCode != ERROR_SUCCESS){
                return errorCode;
            }
        }
    }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar){
    if(matrix == NULL){
        return ERROR_NULL_POINTER;
    }

    for (uint32_t i = 0; i < matrix->height; ++i){
        for (uint32_t j = 0; j < matrix->width; ++j){
            double newVal = 0.0;
            ErrorCode errorCode = matrix_getValue(matrix, i, j, &newVal);
            if(errorCode != ERROR_SUCCESS){
                return errorCode;
            }
            ErrorCode errorCode = matrix_setValue(matrix, i, j, newVal * scalar);
            if(errorCode != ERROR_SUCCESS){
                return errorCode;
            }
        }
    }

    return ERROR_SUCCESS;
    
}