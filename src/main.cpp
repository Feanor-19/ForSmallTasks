#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void print_text(char *text[], size_t nLines);

int main()
{
    const size_t nLines = 5;
    const size_t BUF_SIZE = 100;

    char *text[nLines] = {};

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

    return 0;
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
