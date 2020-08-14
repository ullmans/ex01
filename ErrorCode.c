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
    case ERROR_NULL_POINTER: return "null pointer exeption";
    case ERROR_CAN_NOT_MULTI: return "the two matrixs cant be multiple together in this order";
    case ERROR_FAILED_MEMORY_ALOCATION: return "couldn't alloctae memory";
    case ERROR_NEG_WIDTH_OR_HEIGHT: return "negative width or height";
    default: return "";
    }
}