#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{

    // prompt user for input
    long number = get_long("Number: ");

    // checksum
    long result = 0;
    long result2 = 0;
    long temp;

    for (long i = 100; i < 100000000000000000; i *= 100)
    {
        temp = number % i / (i / 10) * 2;
        if (temp > 9)
        {
            result += temp / 10;
            result += temp % 10;
        } 
        else
        {
            result += temp;
        }
    }

    for (long i = 10; i < 10000000000000000; i *= 100)
    {
        temp = number % i / (i / 10);
        result2 += temp;
    }

    long total = result + result2;
    bool valid = false;
    if (total % 10 == 0)
    {
        valid = true;
    }

    /* check for card length and starting digits
    AMEX        15 digits, starting with 34 or 37
    MASTERCARD  16 digits, starting with 51, 52, 53, 54 or 55
    VISA        13 and 16 digits, starting with 4
    */
    int length = floor(log10(number)) + 1;
    
    if (length == 15 && (number / 10000000000000 == 34 || number / 10000000000000 == 37) && (valid == true))
    {
        printf("AMEX\n");
    } 
    else if (length == 16 && (number / 100000000000000 == 51 || number / 100000000000000 == 52 || number / 100000000000000 == 53
                              || number / 100000000000000 == 54 || number / 100000000000000 == 55) && (valid == true))
    {
        printf("MASTERCARD\n");
    } 
    else if ((length == 13 && (number / 1000000000000 == 4) && (valid == true)) || (length == 16 && (number / 1000000000000000 == 4)
             && (valid == true)))
    {
        printf("VISA\n");
    } 
    else
    {
        printf("INVALID\n");
    }

}