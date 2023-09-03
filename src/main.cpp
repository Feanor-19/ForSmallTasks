#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct TriangleArray
{
    size_t triangle_side;
    int *data;
};

const size_t MAX_FILE_NAME_LEN = 100;

TriangleArray read_triangle_array(FILE *stream);

void print_triangle_array(TriangleArray arr);

size_t find_maximum_elem_width(size_t array_size, const int *data);

size_t find_num_width(int num);

size_t full_triangle_array_length( size_t triangle_side );

int main()
{
    /*
    // вариант с печатью "константы"
    int data[] =
                    {
                        0,
                        1, -200,
                        3, 4, 5,
                        68, 7, 8, 90
                    };
    const size_t triangle_side = 4;

    TriangleArray tr_arr = {triangle_side, data};
    */

    // вариант с чтением из потока
    //TriangleArray tr_arr = read_triangle_array(stdin);

    // вариант с чтением из файла
    printf("Enter file's name:\n");
    char file_name[MAX_FILE_NAME_LEN];
    if (scanf("%s", file_name) != 1 )
    {
        fprintf(stderr, "Something went wrong. Please, restart and try again.\n");
        return 1;
    }
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Can not open file: %s. Please, restart and try again.\n", file_name);
        return 1;
    }

    TriangleArray tr_arr = read_triangle_array(file);
    if (tr_arr.data == NULL)
    {
        fprintf(stderr, "Some error occurred during reading the array.\n");
        return 1;
    }

    print_triangle_array(tr_arr);

    free(tr_arr.data);

    return 0;
}

TriangleArray read_triangle_array(FILE *stream)
{
    assert(stream != NULL);

    size_t triangle_side = 0;
    if (fscanf(stream, "%d", &triangle_side) != 1) return {0, NULL};

    size_t array_size = full_triangle_array_length(triangle_side);

    int *p_array = (int *) calloc( array_size, sizeof(int) );

    for ( size_t ind = 0; ind < array_size; ind++ )
    {
        int buf = 0;

        if (fscanf(stream, "%d", &buf) != 1) return {0, NULL};

        p_array[ ind ] = buf;
    }

    return {triangle_side, p_array};
}

void print_triangle_array(TriangleArray arr)
{
    assert(arr.data != NULL);

    for (size_t i = 0; i < arr.triangle_side; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            size_t width = find_maximum_elem_width( full_triangle_array_length(arr.triangle_side),
                                                    arr.data );

            printf("%*d ", width, *(arr.data + (1+i)*i/2 + j) );
            //Дед сказал написать без [] для усиления понимания
        }
        printf("\n");
    }
}

size_t find_maximum_elem_width(size_t array_size, const int *data)
{
    assert(data != NULL);

    size_t ans = 0;
    for (size_t ind = 0; ind < array_size; ind++)
    {
        size_t res = find_num_width( data[ind] );
        if (res > ans) ans = res;
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

size_t full_triangle_array_length( size_t triangle_side )
{
    return (1+triangle_side)*triangle_side/2;
}
