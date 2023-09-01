#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* read_triangle_array(FILE *stream);

void print_triangle_array(size_t triangle_side, const int *data);

size_t find_maximum_elem_width(size_t array_size, const int *data);

size_t find_num_width(int num);

size_t full_triangle_array_length( size_t triangle_side );

int main()
{
    const int data[] =
                    {
                        0,
                        1, -200,
                        3, 4, 5,
                        68, 7, 8, 90
                    };
    const size_t triangle_side = 4;

    print_triangle_array(triangle_side, data);

    //printf("!!! %d\n", find_maximum_elem_width(full_triangle_array_length(4), data));

    return 0;
}

int* read_triangle_array(FILE *stream)
{
    assert(stream != NULL);

    size_t triangle_side = 0;
    if (fscanf(stream, "%d", &triangle_side) != 1) return NULL;

    size_t array_size = full_triangle_array_length(triangle_side);

    int *p_array = (int *) calloc( array_size, sizeof(int) );

    for ( size_t ind = 0; ind < array_size; ind++)
    {
        int buf = 0;

        if (fscanf(stream, "%d", &buf) != 1) return NULL;
    }

}

void print_triangle_array(size_t triangle_side, const int *data)
{
    assert(data != NULL);

    for (size_t i = 0; i < triangle_side; i++)
    {
        for (size_t j = 0; j < i + 1; j++)
        {
            //printf("debug: offset on row %d is %d.\n", i, (1+i)*i/2 + j);
            printf("%*d ",  find_maximum_elem_width( full_triangle_array_length(4), data ),
                            *(data + (1+i)*i/2 + j) );
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
