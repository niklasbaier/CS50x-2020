#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    
    do
    {
        height = get_int("How tall should the pyramid be? (1 to 8 inclusive): ");
    }
    while (height < 1 || height > 8);
    
    for (int i = 1; i < height + 1; i++) 
    {
        // print empty space before the #
        for (int k = 0; k < height - i; k++) 
        {
            
            printf(" ");
        }
        // print the # left side
        for (int j = 0; j < i; j++) 
        {
            
            printf("#");
        }
        // print the space in the middle
        printf("  ");
        // print the # right side
        for (int j = 0; j < i; j++) 
        {
            
            printf("#");
        }
        // move to next line
        printf("\n");
    }
    
}