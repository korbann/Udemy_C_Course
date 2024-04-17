#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
//------------------------------------------------------------------------------------
// void ArrayPrinting(void*, size_t);

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
/* Lesson 82
 * Develop your special "realloc" function.
 * the function should have the following signature:
 *  void* myRealloc(void *srcblock, unsigned oldsize, unsigned newsize);
 *
 * The function should implement a General/Universal reallocation functionality
 * (without using the realloc function...)
*/
void* customRealloc(void*, size_t, size_t);
void test_customRealloc(void);

//------------------------------------------------------------------------------------
/* Lesson 84
 * Function that creates and filles with values a dynamic array.
 * The size of the array is UNKNOWN in advance.
 * What's known is that once read a value of "-1", the function should stop
 * reading inputs from the user and it should return the array, and pass its size.
*/
void fillingDynamicArray(void);

//------------------------------------------------------------------------------------
/* Lesson 87
* Create and Pass 1D Array using Pointer to Pointer
*/
void create1DByRef(int **ptr, int size);
void test_create1DByRef(void);

//------------------------------------------------------------------------------------
/* Lesson 92
* Create function for inserting to array.
* Should be universal for all types.
*/
void test_insertToArray(void);
void* insertToArray(void*, size_t, size_t, void *, size_t);
//------------------------------------------------------------------------------------
/* Lesson 94
* Create a function for removing from array.
* Should be universal for all types.
*/
void* removeFromArray(void*, size_t, size_t, size_t);
void test_removeFromArray(void);
//------------------------------------------------------------------------------------
/* Lesson 96
* Write a function that receives an array of integers.
* This function should be of a void type.
* Create and copy all the elements from the received array to a new one.
* The new array (copied) should be passed by reference to the caller function.
*/
void copyingArrayByReference(void*, size_t, void **);
void test_copyingArrayByReference(void);
//------------------------------------------------------------------------------------
/* Lesson 102
* 2D Dynamically Allocated Arrays
*/
void allocate2DArray(int**);
void test_allocate2DArray(void);

int** allocate2DMatrix(size_t, size_t);
void allocate2DMatrixByReference(int ***arr, size_t rows, size_t columns);
void test_allocate2Matrix(void);
//------------------------------------------------------------------------------------
/* Lesson 107
* 2 Dynamic arrays
* 1. Implement 2 functions that receive a Dynamic 2D Array (Pointer to pointer..)
*   a. First function should receive 2 rows.
*      The function should SWAP between the 2 rows in O(1). Make it universal.
*   b. Second function should receive 2 columns.
*      The function should SWAP between the 2 columns in O(n).
*/
void swapRows(void **array, int row1, int row2);
void swapColumns(int **array, int column1, int column2, size_t rowNumb); // swaps only by elements
void test_swapRowsColumns(void);
//------------------------------------------------------------------------------------
/* Lesson 110 & 112
*  Triangular matrix
*  Implement 2 functions that should:
*   1. Create a "Lower triangular Matrix" and return it.
*   2. Create an "Upper triangular Matrix" and return it.
*
*   Printing these matrixes
*/
int** lowerTriangularMatrix(size_t rowNumb);
void lowerTriangularMatrixPrint(int **matrix, size_t rowNumb);
void lowerTriangularMatrixZerosPrint(int **matrix, size_t rowNumb);

int** upperTriangularMatrix(size_t rowNumb);
void upperTriangularMatrixPrint(int **matrix, size_t rowNumb);
void upperTriangularMatrixZerosPrint(int **matrix, size_t rowNumb);

void test_triangularMatrix(void);
//------------------------------------------------------------------------------------
/* Lesson 114
*  Write a function that allocates a 2D Dynamic Array and Passes it by Reference
*/
void allocate2DArrayByRef(int ***array, size_t rowsNumb, size_t columnNumb);
void test_allocate2DArrayByRef(void);
//------------------------------------------------------------------------------------
int main()
{

    //test_customRealloc();
    //fillingDynamicArray();
    //test_create1DByRef();
    //test_insertToArray();
    //test_removeFromArray();
    //test_copyingArrayByReference();
    //test_allocate2Matrix();
    //test_swapRowsColumns();
    // test_triangularMatrix();
    test_allocate2DArrayByRef();

    return 0;
}

//------------------------------------------------------------------------------------
// void ArrayPrinting(void* arr, size_t arrSize)
// {
//     for(size_t i=0; i <= arrSize; i++)
//     {
//         printf("%d",);
//     }
// }

//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// Lesson 82
void* customRealloc(void *srcblock, size_t oldsize, size_t newsize)
{
    void *newblock = NULL;

    if(NULL != srcblock)
    {
        newblock = malloc(newsize);
        if(NULL != newblock)
        {
            memset(newblock, 0, newsize);

            size_t tempsize = oldsize<newsize ? oldsize : newsize;
            memcpy(newblock, srcblock, tempsize);

            free(srcblock);
            srcblock = NULL;
        }
    }

    return newblock;
}
void test_customRealloc(void)
{
    size_t blockSize = 50;
    int *memBlock = malloc(blockSize * sizeof(int));
    memset(memBlock, -20, blockSize);

    size_t newBlockSize = 100;
    int* newBlock = (int*)customRealloc(memBlock, blockSize, newBlockSize * sizeof(int));

    printf("block addres: %p \n", memBlock);
    printf("new block addres: %p \n", newBlock);

}
//------------------------------------------------------------------------------------
// Lesson 84
void fillingDynamicArray(void)
{
    int numb = 0;
    size_t counter = 0;

    int staticArray[10] = {0};
    size_t staticArraySize = sizeof(staticArray) / sizeof(int);
    size_t i = 0;

    int *a = (int*)calloc(staticArraySize, sizeof(int));


    /* last value of -1 will not be written in array but will not be counted */
    while(1)
    {
        printf("enter value: ");
        scanf("%d", &numb);

        if(numb == -1)
        {
            if( counter%staticArraySize != 0 )
            {
                if( counter/staticArraySize > 1 )
                {
                    a = (int*)realloc( a, counter * sizeof(int) );
                    memcpy( (a + counter - counter % staticArraySize), staticArray, ( counter%staticArraySize * sizeof(int) ) );
                    break;
                }
                memcpy(a, staticArray, counter * sizeof(int));
            }
            break;
        }

        counter++;
        staticArray[i] = numb;
        i++;

        if(i == staticArraySize)
        {
            if( counter/staticArraySize > 1 )
            {
                a = (int*)realloc( a, counter * sizeof(int) );
            }
            memcpy( (a + counter - staticArraySize), staticArray, sizeof(staticArray));
            i = 0;
        }
    }

    for(size_t j = 0; j < counter; j++)
    {
        printf("%d ", a[j]);
    }
    printf("\n array size = %lu", counter);
}
//------------------------------------------------------------------------------------
// Lesson 87
void create1DByRef(int **ptr, int size)
{
    *ptr = (int*) calloc( size, sizeof(int) );
}
void test_create1DByRef(void)
{
    int *ptr = NULL;
    int size = 3;

    create1DByRef(&ptr, size);
    *ptr = 5;
    ptr++;
    *ptr = 2;
    ptr++;
    *ptr = 3;

    printf("%d, %d, %d",*(ptr-2), *(ptr-1), *ptr);
}
//------------------------------------------------------------------------------------
// Lesson 92
void* insertToArray(void* arr, size_t arrSizeBytes, size_t newValueIndexBytes, void *newValue, size_t NewValueSizeBytes)
{
    void* newArr = malloc( arrSizeBytes + NewValueSizeBytes);
    if(newArr == NULL)
    {
        printf("Error in allocation");
        return NULL;
    }

    memcpy(newArr, arr, newValueIndexBytes);

    /* Inserting new value */
    memcpy(newArr + newValueIndexBytes, newValue, NewValueSizeBytes);

    /*Copy the rest of the array*/
    memcpy((char*)newArr + newValueIndexBytes + NewValueSizeBytes, (char*)arr + newValueIndexBytes, arrSizeBytes - newValueIndexBytes);

    return newArr;
}

void test_insertToArray(void)
{
    size_t arrIntSize = 4;
    int *arrInt = (int*)calloc(arrIntSize, sizeof(int));
    arrInt[0] = 1;
    arrInt[1] = 2;
    arrInt[2] = 3;
    arrInt[3] = 4;

    size_t newIndex_arrInt = 2;
    int newValue_arrInt = 10;

    size_t arrDoubSize = 3;
    double *arrDoub = (double*)calloc(arrDoubSize, sizeof(double));
    arrDoub[0] = 0.15;
    arrDoub[1] = 1.72;
    arrDoub[2] = 2.24;
    size_t newIndex_arrDoub = 0;
    double newValue_arrDoub = 10.88;

    int *newArrInt = (int*)insertToArray(arrInt, arrIntSize * sizeof(int), newIndex_arrInt * sizeof(int), &newValue_arrInt, sizeof(int));
    printf("New integer array: \n");
    for(size_t i = 0; i <= arrIntSize; i++)
    {
        printf("%d ", newArrInt[i]);
    }
    printf("\n");

    double *newArrDoub = (double*)insertToArray(arrDoub, arrDoubSize * sizeof(double), newIndex_arrDoub * sizeof(double), &newValue_arrDoub, sizeof(double));
    printf("New double array: \n");
    for(size_t i = 0; i <= arrDoubSize; i++)
    {
        printf("%lf ", newArrDoub[i]);
    }
    printf("\n");
}
//------------------------------------------------------------------------------------
// Lesson 94
void* removeFromArray(void *arr, size_t arrSizeBytes, size_t remIndexBytes, size_t remSizeBytes)
{
    if( (NULL == arr) || (remSizeBytes >= arrSizeBytes) || (0 == remSizeBytes) )
    {
        printf("Passing parameters have an error \n");
        return NULL;
    }

    void* newArr = malloc(arrSizeBytes - remSizeBytes);
    if(NULL == newArr)
    {
        printf("Error in allocation");
        return NULL;
    }

    if(0 != remIndexBytes)
    {
        memcpy(newArr, arr, remIndexBytes);
        if(remIndexBytes != arrSizeBytes - remSizeBytes)
        {
            memcpy( (newArr + remIndexBytes), (arr + remIndexBytes + remSizeBytes), (arrSizeBytes - remIndexBytes - remSizeBytes) );
        }
    }
    else
    {
        memcpy(newArr, (arr + remSizeBytes), (arrSizeBytes - remSizeBytes) );
    }
    return newArr;

}

void test_removeFromArray(void)
{
    /* 1: remIndexBytes = 0 */
    size_t arrSize = 5;
    int *arr = (int*)calloc(arrSize, sizeof(int));
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;

    printf("remIndexBytes = 0 \n");
    int* newArr = (int*)removeFromArray(arr, arrSize * sizeof(int), 0, sizeof(int) );
    for(size_t i = 0; i < arrSize - 1; i++)
    {
        printf("%d ", newArr[i]);
    }
    printf("\n");

    printf("remIndexBytes = 1 \n");
    int* newArr1 = (int*)removeFromArray(arr, arrSize * sizeof(int), 1 * sizeof(int), sizeof(int) );
    for(size_t i = 0; i < arrSize - 1; i++)
    {
        printf("%d ", newArr1[i]);
    }
    printf("\n");

    printf("remIndexBytes = arrSize - 1 \n");
    int* newArr2 = (int*)removeFromArray(arr, arrSize * sizeof(int), 4 * sizeof(int), sizeof(int) );
    for(size_t i = 0; i < arrSize - 1; i++)
    {
        printf("%d ", newArr2[i]);
    }
    printf("\n");

    free(arr);
    free(newArr1);
    free(newArr2);
}
//------------------------------------------------------------------------------------
// Lesson 96
void copyingArrayByReference(void *arr, size_t arrSizeBytes, void **newArr)
{
    if(NULL == *newArr)
    {
        printf("There is no newArry");
        return;
    }
    memcpy(*newArr, arr, arrSizeBytes);
}

void test_copyingArrayByReference(void)
{
    int arr[5] = {1, 2, 3, 4, 5};

    int *newArr = (int*)malloc(sizeof(arr));

    if(NULL == newArr)
    {
        printf("Error in allocation");
        return;
    }

    copyingArrayByReference(arr, sizeof(arr), (void**)&newArr);

    for(size_t i = 0; i < sizeof(arr)/sizeof(int); i++)
    {
        printf("%d ", newArr[i]);
    }

    free(newArr);
}
//------------------------------------------------------------------------------------
// Lesson 102
void allocate2DArray(int **arr)
{
    size_t rows, columns;

    printf("enter number of Matrix rows: \n");
    scanf("%d", &rows);

    arr = (int**)calloc(rows, sizeof(int*));
    if(NULL != arr)
    {
        printf("Error in memory allocation! \n");
        return;
    }

    for(size_t i = 0; i < rows; i++)
    {
        printf("enter number of columns for %u row: /n", i);
        scanf("%u", &columns);
        arr[i] = (int*)calloc(columns, sizeof(int));
        if(NULL != arr[i])
        {
            printf("Error in memory allocation! \n");
            return;
            //here should be checked how much memory has been located previously and free al of it
        }
    }
}
void test_allocate2DArray(void)
{
    int **arr = NULL;
    allocate2DArray(arr);
}

int** allocate2DMatrix(size_t rows, size_t columns)
{
    int **arr = (int**)calloc(rows, sizeof(int*));
    if(NULL == arr)
    {
        printf("Error in memory allocation! \n");
        return NULL;
    }

    for(size_t i = 0; i < rows; i++)
    {
        arr[i] = (int*)calloc(columns, sizeof(int));
        if(NULL == arr[i])
        {
            printf("Error in memory allocation! \n");
            return NULL;
            //here should be checked how much memory has been located previously and free all of it
        }
    }
    return arr;
}

void allocate2DMatrixByReference(int ***arr, size_t rows, size_t columns)
{
    *arr = (int**)calloc(rows, sizeof(int*));
    if(NULL == *arr)
    {
        printf("Error in memory allocation! \n");
        return;
    }

    for(size_t i = 0; i < rows; i++)
    {
        (*arr)[i] = (int*)calloc(columns, sizeof(int));
        if(NULL == (*arr)[i])
        {
            printf("Error in memory allocation! \n");
            return;
            //here should be checked how much memory has been located previously and free all of it
        }
    }

}

void test_allocate2Matrix(void)
{
    size_t rows = 3;
    size_t columns = 4;
    int **arr = allocate2DMatrix(rows, columns);

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            printf("%5d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    int **arr1 = NULL;
    size_t rows1 = 3;
    size_t columns1 = 4;
    allocate2DMatrixByReference(&arr1, rows1, columns1);

    for(size_t i = 0; i < rows1; i++)
    {
        for(size_t j = 0; j < columns1; j++)
        {
            printf("%5d ", arr1[i][j]);
        }
        printf("\n");
    }
}
//------------------------------------------------------------------------------------
// Lesson 107
void swapRows(void **array, int row1, int row2)
{
    void* tempPointer = array[row1];
    array[row1] = array[row2];
    array[row2] = tempPointer;
}

void swapColumns(int **array, int column1, int column2, size_t rowNumb)
{
    for(size_t i = 0; i < rowNumb; i++)
    {
        int temp = array[i][column1];
        array[i][column1] = array[i][column2];
        array[i][column2] = temp;
    }
}

void test_swapRowsColumns(void)
{
    // matrix creation
    size_t rowNumb = 3;
    size_t columnNumb = 4;

    int **array = (int**)calloc(rowNumb, sizeof(int*));
    for(size_t i = 0; i < rowNumb; i++)
    {
        array[i] = (int*)calloc(columnNumb, sizeof(int));
    }

    //save rows addresses
    size_t *row0Addresses = (size_t*)calloc(columnNumb, sizeof(size_t));
    size_t *row2Addresses = (size_t*)calloc(columnNumb, sizeof(size_t));

    printf("row0 Addresses || row2 Addresses\n");
    for(size_t i = 0; i < columnNumb; i++)
    {
        row0Addresses[i] = (size_t)(&array[0][i]);
        row2Addresses[i] = (size_t)(&array[2][i]);
        printf("%d          %d\n", row0Addresses[i], row2Addresses[i] );
    }

    // execute
    swapRows((void**)array, 0, 2);

    //check
    printf("row0 new || row2 new\n");
    for(size_t i = 0; i < columnNumb; i++)
    {
        printf("%d      %d\n", &(array[0][i]), &(array[2][i]) );
    }

    // memory freeing
    free(row0Addresses);
    free(row2Addresses);

    for(size_t i = 0; i < rowNumb; i++)
    {
        free(array[i]);
    }
    free(array);
}
//------------------------------------------------------------------------------------
// Lesson 110 & 112

int** lowerTriangularMatrix(size_t rowNumb)
{
    int **trMatrix = (int**)calloc(rowNumb, sizeof(int*));
    if(NULL == trMatrix)
    {
        printf("Lower Triangular Matrix memory allocation error\n");
        return NULL;
    }

    for(size_t i = 0; i < rowNumb; i++)
    {
        trMatrix[i] = (int*)calloc(i + 1, sizeof(int));
        if(NULL == trMatrix[i])
        {
            printf("Lower Triangular Matrix memory allocation error\n");
            return NULL;
        }
    }

    return trMatrix;
}

void lowerTriangularMatrixPrint(int **matrix, size_t rowNumb)
{
    for(size_t i = 0; i < rowNumb; i++)
    {
        for(size_t j = 0; j < i + 1; j++)
        {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");

    }
    printf("\n");
}

void lowerTriangularMatrixZerosPrint(int **matrix, size_t rowNumb)
{
    for(size_t i = 0; i < rowNumb; i++)
    {
        for(size_t j = 0; j < rowNumb; j++)
        {
            if(i < j)
            {
                printf("%3d", 0);
            }
            else
            {
                matrix[i][j] = 1;
                printf("%3d", matrix[i][j]);
            }
        }

        printf("\n");

    }
    printf("\n");
}

int** upperTriangularMatrix(size_t rowNumb)
{
    int **trMatrix = (int**)calloc(rowNumb, sizeof(int*));
    if(NULL == trMatrix)
    {
        printf("Upper Triangular Matrix memory allocation error\n");
        return NULL;
    }

    for(size_t i = 0; i < rowNumb; i++)
    {
        trMatrix[i] = (int*)calloc(rowNumb - i, sizeof(int));
        if(NULL == trMatrix[i])
        {
            printf("Upper Triangular Matrix memory allocation error\n");
            return NULL;
        }
    }

    return trMatrix;
}

void upperTriangularMatrixPrint(int **matrix, size_t rowNumb)
{
    for(size_t i = 0; i < rowNumb; i++)
    {
        for(size_t j = 0; j < rowNumb - i; j++)
        {
            printf("%3d", matrix[i][j]);
        }
        printf("\n");

    }
    printf("\n");
}

void upperTriangularMatrixZerosPrint(int **matrix, size_t rowNumb)
{
    for(size_t i = 0; i < rowNumb; i++)
    {
        for(size_t j = 0; j < rowNumb; j++)
        {
            if(j < i)
            {
                printf("%3d", 0);
            }
            else
            {
                matrix[i][j] = 2;
                printf("%3d", matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void test_triangularMatrix(void)
{
    size_t lowerMatrixRowNum = 7;
    int **lowerMatrix = lowerTriangularMatrix(lowerMatrixRowNum);
    lowerTriangularMatrixZerosPrint(lowerMatrix, lowerMatrixRowNum);

    size_t upperMatrixRowNum = 6;
    int **upperMatrix = upperTriangularMatrix(upperMatrixRowNum);
    upperTriangularMatrixZerosPrint(upperMatrix, upperMatrixRowNum);

    if(NULL != lowerMatrix)
    {
        free(lowerMatrix);
        lowerMatrix == NULL;
    }

    if(NULL != upperMatrix)
    {
        free(upperMatrix);
        upperMatrix == NULL;
    }

}
//------------------------------------------------------------------------------------
// Lesson 114

void allocate2DArrayByRef(int ***array, size_t rowsNumb, size_t columnNumb)
{
    *array = (int**)calloc(rowsNumb, sizeof(int*));
    if(NULL == *array)
    {
        return NULL;
    }

    for(size_t i = 0; i < rowsNumb; i++)
    {
        (*array)[i] = (int*)calloc(columnNumb, sizeof(int));
        if(NULL == (*array)[i])
        {
            // free allocated memory func
            return NULL;
        }
    }
}

void test_allocate2DArrayByRef(void)
{
    int **array = NULL;
    size_t rowsNumb = 3;
    size_t columnNumb = 4;
    allocate2DArrayByRef(&array, rowsNumb, columnNumb);

    if(NULL != array)
    {
        for(size_t i = 0; i < rowsNumb; i++)
        {
            free(array[i]);
        }
        free(array);
        array = NULL;
    }
}
//------------------------------------------------------------------------------------