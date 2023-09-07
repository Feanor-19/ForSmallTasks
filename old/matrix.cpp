#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

int *matrix_create(size_t sizeRows, size_t sizeCols);

void matrix_delete( int *matrix );

int matrix_get_elem( const int *arr, size_t indRow, size_t indCol );

int matrix_set_elem( int *arr, size_t indRow, size_t indCol, int new_value );

int *matrix_get_ptr_elem( int *arr, size_t indRow, size_t indCol );

void matrix_print( int *arr );

size_t matrix_get_width(const int* arr );

size_t matrix_get_height(const int* arr );

size_t matrix_get_fact_len( size_t sizeRows, size_t sizeCols );

size_t find_maximum_elem_width(const int *arr);

size_t find_num_width(int num);

inline size_t matrix_get_index__(const int *arr, size_t indRow, size_t indCol )
{
    return indRow*matrix_get_width(arr) + indCol + 2;
}

int main()
{
    size_t rows = 0, cols = 0;

    scanf("%d %d", &rows, &cols);

    int *arr2d = matrix_create(rows, cols);

    for (size_t indRow = 0; indRow < rows; indRow++)
    {
        for (size_t indCol = 0; indCol < cols; indCol++)
        {
            matrix_set_elem(arr2d, indRow, indCol, (indRow*cols + indCol)*(indRow*cols + indCol) );
        }
    }

    matrix_print(arr2d);

    matrix_delete(arr2d);

    return 0;
}

int *matrix_create(size_t sizeRows, size_t sizeCols)
{
    assert(sizeRows > 0);
    assert(sizeCols > 0);

    int *p_arr = (int *) calloc( matrix_get_fact_len(sizeRows, sizeCols), sizeof(int) );

    p_arr[0] = sizeRows;
    p_arr[1] = sizeCols;

    return p_arr;
}

void matrix_delete( int *matrix )
{
    assert( matrix != NULL );

    free(matrix);
}

int matrix_get_elem( const int *arr, size_t indRow, size_t indCol )
{
    assert(arr != NULL);
    assert(indRow < matrix_get_height(arr));
    assert(indCol < matrix_get_width(arr));

    return arr[ matrix_get_index__(arr, indRow, indCol) ];
}

int matrix_set_elem( int *arr, size_t indRow, size_t indCol, int new_value )
{
    assert(arr != NULL);
    assert(indRow < matrix_get_height(arr));
    assert(indCol < matrix_get_width(arr));

    int old_value = arr[matrix_get_index__(arr, indRow, indCol)];
    arr[matrix_get_index__(arr, indRow, indCol)] = new_value;
    return old_value;
}

int *matrix_get_ptr_elem( int *arr, size_t indRow, size_t indCol )
{
    assert(arr != NULL);
    assert(indRow < matrix_get_height(arr));
    assert(indCol < matrix_get_width(arr));

    return &arr[matrix_get_index__(arr, indRow, indCol)];
}

void matrix_print( int *arr )
{
    assert(arr != NULL);

    size_t max_width = find_maximum_elem_width( arr );

    for (size_t indRow = 0; indRow < matrix_get_height(arr); indRow++)
    {
        for (size_t indCol = 0; indCol < matrix_get_width(arr); indCol++)
        {
            printf("%*d ", max_width, matrix_get_elem(arr, indRow, indCol));
        }
        printf("\n");
    }
}

size_t matrix_get_width(const int* arr )
{
    assert(arr != NULL);

    return (size_t) arr[1];
}

size_t matrix_get_height(const int* arr )
{
    assert(arr != NULL);

    return (size_t) arr[0];
}

size_t matrix_get_fact_len( size_t sizeRows, size_t sizeCols )
{
    return sizeRows*sizeCols + 2;
}

size_t find_maximum_elem_width(const int *arr)
{
    assert(arr != NULL);

    size_t ans = 0;
    for (size_t indRow = 0; indRow < matrix_get_height(arr); indRow++)
    {
        for (size_t indCol = 0; indCol < matrix_get_width(arr); indCol++)
        {
            size_t res = find_num_width( matrix_get_elem( arr, indRow, indCol ) );
            if (res > ans) ans = res;
        }
    }
    return ans;
}

size_t find_num_width(int num)
{
    size_t res = 0;

    if (num < 0)
    {
        res++;
        num = -num;
    }

    while( num > 0 )
    {
        res++;
        num = num/10;
    }

    return res;
}
