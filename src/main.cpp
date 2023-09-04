#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>

int *create_2Darr(size_t sizeX, size_t sizeY);

int get_elem_2Darr( const int *arr, size_t indX, size_t indY );

int set_elem_2Darr( int *arr, size_t indX, size_t indY, int new_value );

int *get_pointer_2Darr( int *arr, size_t indX, size_t indY );

void print_2Darr( int *arr );

size_t get_2Darr_x(const int* arr );

size_t get_2Darr_y(const int* arr );

size_t get_2Darr_len( size_t sizeX, size_t sizeY );

size_t find_maximum_elem_width(const int *arr);

size_t find_num_width(int num);

int main()
{
    size_t x = 0, y = 0;

    scanf("%d %d", &x, &y);

    int *arr2d = create_2Darr(x, y);


    for (size_t indX = 0; indX < x; indX++)
    {
        for (size_t indY = 0; indY < y; indY++)
        {
            set_elem_2Darr(arr2d, indX, indY, (indX*x + indY)*(indX*x + indY) );
        }
    }

    /*
    int askX = 0, askY = 0;
    scanf("%d %d", &askX, &askY);

    printf("Here is the value in the array: %d\n", get_elem_2Darr(arr2d, askX, askY));
    */

    size_t indX = 1;
    size_t indY = 2;

    set_elem_2Darr(arr2d, indX, indY, 19 );

    print_2Darr(arr2d);

    free(arr2d);

    return 0;
}

int *create_2Darr(size_t sizeX, size_t sizeY)
{
    assert(sizeX > 0);
    assert(sizeY > 0);

    int *p_arr = (int *) calloc( get_2Darr_len(sizeX, sizeY), sizeof(int) );

    p_arr[0] = sizeX;
    p_arr[1] = sizeY;

    return p_arr;
}

int get_elem_2Darr( const int *arr, size_t indX, size_t indY )
{
    assert(arr != NULL);
    assert(indX < get_2Darr_x(arr));
    assert(indY < get_2Darr_y(arr));

    return arr[indX*get_2Darr_x(arr) + indY + 2];
}

int set_elem_2Darr( int *arr, size_t indX, size_t indY, int new_value )
{
    assert(arr != NULL);
    assert(indX < get_2Darr_x(arr));
    assert(indY < get_2Darr_y(arr));

    int old_value = arr[indX*get_2Darr_x(arr) + indY + 2];
    arr[indX*get_2Darr_x(arr) + indY + 2] = new_value;
    return old_value;
}

int *get_pointer_2Darr( int *arr, size_t indX, size_t indY )
{
    assert(arr != NULL);
    assert(indX < get_2Darr_x(arr));
    assert(indY < get_2Darr_y(arr));

    return &(arr[indX*get_2Darr_x(arr) + indY + 2]);
}

void print_2Darr( int *arr )
{
    assert(arr != NULL);

    size_t max_width = find_maximum_elem_width( arr );

    for (size_t indX = 0; indX < get_2Darr_x(arr); indX++)
    {
        for (size_t indY = 0; indY < get_2Darr_y(arr); indY++)
        {
            printf("%*d ", max_width, get_elem_2Darr(arr, indX, indY));
        }
        printf("\n");
    }
}

size_t get_2Darr_x(const int* arr )
{
    assert(arr != NULL);

    return (size_t) arr[0];
}

size_t get_2Darr_y(const int* arr )
{
    assert(arr != NULL);

    return (size_t) arr[1];
}

size_t get_2Darr_len( size_t sizeX, size_t sizeY )
{
    return sizeX*sizeY + 2;
}

size_t find_maximum_elem_width(const int *arr)
{
    assert(arr != NULL);

    size_t ans = 0;
    for (size_t indX = 0; indX < get_2Darr_x(arr); indX++)
    {
        for (size_t indY = 0; indY < get_2Darr_y(arr); indY++)
        {
            size_t res = find_num_width( get_elem_2Darr( arr, indX, indY ) );
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
