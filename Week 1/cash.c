#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    
    do
    {
        change = get_float("Change owed: ");    
    }
    while (change < 0);
    
    int cents = round(change * 100);
    int quarters, dimes, nickels, pennies;
    
    // quarters = 25    
    quarters = round(cents / 25);
    cents -= quarters * 25;

    // dimes = 10
    dimes = round(cents / 10);
    cents -= dimes * 10;

    // nickels = 5
    nickels = round(cents / 5);
    cents -= nickels * 5;

    // pennies = 1
    pennies = round(cents / 1);
    cents -= pennies * 1;

    printf("Min. amount of coins: %i\n", (quarters + dimes + nickels + pennies));
}