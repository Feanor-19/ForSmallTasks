#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

size_t get_number_of_lines(void);

void print_text(char *text[], size_t nLines);

void free_arr_elems( void *arr[], size_t arr_size );

void inline clear_inp_buf(FILE *inp_stream)
{
    while (getc(inp_stream) != '\n')
        ;
}

int main()
{
    size_t nLines = 5;
    const size_t BUF_SIZE = 100;

    nLines = get_number_of_lines();

    char **text = (char **) calloc( nLines, sizeof( char * ) );

    char buf[BUF_SIZE] = {};
    for (size_t ind = 0; ind < nLines; ind++)
    {
        if (fgets(buf, BUF_SIZE, stdin) == NULL) break;

        size_t str_in_buf_len = strlen(buf);

        text[ind] = (char *) calloc( str_in_buf_len + 1, sizeof(char) );

        strncpy( text[ind], buf, (str_in_buf_len + 1) - 1 );
        text[ind][str_in_buf_len] = '\0'; //< in case read line is bigger than buf
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
