#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("How would you like to be called?\n");
    printf("Hello, %s! Nice to meet you :-)\n", name);
}