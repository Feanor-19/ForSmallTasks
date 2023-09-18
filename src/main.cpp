#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "mystring.h"

size_t get_number_of_lines(void);

/*!
    @brief Allocates memory and sets pointers (elements of text[])
    to corresponding blocks of memory.
    @param [in] text[] Array of pointers to char. All pointers will point to
    corresponding blocks of allocated memory.
    @param [in] nLines Number of elements in text[], and also number of lines
    to be stored.
    @param [in] line_size Size (in chars) of one block of memory to allocate.
    Later this block will be changed by my_getline() if needed, but my_getline()
    requires some memory to start with. line_size must be > 2.
    @return text[] if no errors occurred, NULL otherwise.
*/
char ** initialize_text(char *text[], size_t nLines, size_t line_size);

void print_text(char *text[], size_t nLines);

void free_arr_elems( void *arr[], size_t arr_size );

void inline clear_inp_buf(FILE *inp_stream)
{
    while (getc(inp_stream) != '\n')
        ;
}

int main()
{
    const size_t START_LINE_SIZE = 10;

    size_t nLines = get_number_of_lines();

    char **text = (char **) calloc( nLines, sizeof( char * ) );

    initialize_text(text, nLines, START_LINE_SIZE);

    for (size_t ind = 0; ind < nLines; ind++)
    {
        size_t n_bytes = START_LINE_SIZE;
        size_t read_bytes = my_getline(&text[ind], &n_bytes, stdin);

        if (read_bytes == EOF)
        {
            printf("EOF! Stop.\n");
            break;
        }

        printf("!   For line at index %u %u bytes were read. "
        "It takes %u bytes in memory.\n", ind, read_bytes, n_bytes);
    }

    print_text(text, nLines);

    free_arr_elems( (void **) text, nLines);

    free(text);

    return 0;
}

size_t get_number_of_lines(void)
{
    size_t nLines = 0;

    printf("Please, enter number of lines in the text.\n");

    while ( scanf("%u", &nLines) != 1 || nLines == 0 )
    {
        printf("Please, try again!\n");

        clear_inp_buf(stdin);
    }

    clear_inp_buf(stdin);

    return nLines;
}

char ** initialize_text(char *text[], size_t nLines, size_t line_size)
{
    assert(text != NULL);
    assert(nLines > 0);
    assert(line_size > 2);

    for (size_t ind = 0; ind < nLines; ind++)
    {
        text[ind] = (char *) calloc( line_size, sizeof(char) );

        if ( text[ind] == NULL ) return NULL; // вероятно не хватило памяти
    }

    return text;
}

void print_text(char *text[], size_t nLines)
{
    assert(text != NULL);
    assert(nLines > 0);

    for (size_t ind = 0; ind < nLines; ind++)
    {
        if (text[ind] != NULL)
        {
            printf("At address %p lies string: <%s>\n", text[ind], text[ind]);
        }
        else
        {
            printf("At index %ud lies nullptr!\n", ind);
        }

    }
}

void free_arr_elems( void *arr[], size_t arr_size )
{
    assert(arr != NULL);

    for (size_t ind = 0; ind < arr_size; ind++)
    {
        if ( arr[ind] != NULL )
        {
            free( arr[ind] );
            arr[ind] = NULL;
        }
    }
}
