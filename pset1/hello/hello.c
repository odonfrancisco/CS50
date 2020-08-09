#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's thy name?\n");
    printf("hello, %s\n", name);
}