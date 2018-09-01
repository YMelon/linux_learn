#include <stdio.h>

int main(int argc, char* argv[])
{
    int n;
    n = argv[1] - '0';
    
    printf("argv[1]: %c\n", argv[1]);
    printf("n = %d\n", n);

    return 0;
}
