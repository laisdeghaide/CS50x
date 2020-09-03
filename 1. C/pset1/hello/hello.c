#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //here the user will insert the name that will be stored in the string called name
    string name = get_string("What is your name?\n");
    printf("hello, %s\n", name);
}
