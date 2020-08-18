#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }

        int k = atoi(argv[1]);

        string p = get_string("plaintext: ");
        string c = p;

        for (int i = 0, n = strlen(p); i < n; i++)
        {
            // A (65) to Z (90)
            if (isupper(p[i]) != 0)
            {
                c[i] = (p[i] - 65 + k) % 26 + 65;
            }
            // a (97) to z (122)
            else if (islower(p[i]) != 0)
            {
                c[i] = (p[i] - 97 + k) % 26 + 97;
            }
            // leave punctuation as is
            else
            {
                c[i] = p[i];
            }
        }

        printf("ciphertext: %s\n", c);
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}