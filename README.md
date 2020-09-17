## matrix class
---

the matrix class implements "matrix" and it's function.
every function return an ErrorCode object - an ERROR_SUCCESS if it worked well or other error that explain about the error that has acourd.

#### fields:

---

* uint32_t height;
* uint32_t width;
* double** values;

#### the functions of Matrix.c:

---

* matrix_create  
* matrix_copy  
* void matrixdestroy  
* matrix_getHeight  
* matrix_getWidth  
* matrix_setValue  
* matrix_getValue  
* matrix_add  
* matrix_multiplyMatrices  
* matrix_multiplyWithScalar 

## ErrorCode class

---

the ErrorCode class implements errors so if there will be an error in the program- so the user will know about it.
I use enums for the errors (according to the number, the program knows which message to return to the user) and implements two functions for it.

#### the functions of ErrorCode.c:  

---

* error_isSuccess  
* error_getErrorMessage

## target

---

the target was to create a matrix object that can be changed according to functions- so we can add matrices, multiply them and change them.

## testing

---

I tested my code with the tester from the piazza and a tester of a friend (Yair Koskas).