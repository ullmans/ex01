#include <stdio.h>
#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code){
    if (code==ERROR_SUCCESS){
        return 1;
    }
    return 0;
}

const char* error_getErrorMessage(ErrorCode code){
    switch (code)
    {
    case ERROR_SUCCESS: return "the operation has promoted successfully";
    case ERROR_MISSING_MATRIX: return "input matrix pointer is null";
    case ERROR_MISSING_MATRIX_HEIGHT: return "has not matrix height";
    case ERROR_MISSING_MATRIX_WIDTH: return "has not matrix width";
    case ERROR_MISSING_MATRIX_VALUES: return "missing values from the matrix";
    case ERROR_NULL_OUTPUT_POINTER: return "try to store info in NULL adress";
    case ERROR_FAILED_MEMORY_ALOCATION: return "couldn't alloctae memory";
    case ERROR_NEG_WIDTH_OR_HEIGHT: return "negative width or height";
    default: return "";
    }
}