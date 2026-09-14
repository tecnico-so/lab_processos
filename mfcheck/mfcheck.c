#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("Number of arguments: %d\n", argc - 1);

    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    // TODO
    
    return 0;
}
