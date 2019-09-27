#include "headers.h"

void echo_func(char *sentence[], int length)
{
    for(int i = 1; i < length; i++)
    {
        printf("%s ",sentence[i]);
    }
    printf("\n");
}
