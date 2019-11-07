#include <string.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    char* s = "Al";
    char* ss = "All";
    printf("%d\n", strcmp(s, ss));
    return 0;
}