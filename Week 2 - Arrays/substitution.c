#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Get Key
    if (argc == 2)
    {
        int n = strlen(argv[1]);

        // Check key length
        if (n == 26)
        {
            // Check for non alphabetic characters
            for (int i = 0; i < n; i++)
            {
                if (isalpha(argv[1][i]) == 0)
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
            }

            // Check for repeated characters
            for (int i = 0; i < n; i++)
            {
                int count = 0;

                for (int j = 0; j < n; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        count++;
                    }
                }

                if (count > 1)
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }

            // Key is valid
            string key = argv[1];

            // Get plaintext
            string plain = get_string("plaintext: ");

            // Encipher
            string cipher = plain;

            for (int i = 0, m = strlen(plain); i < m; i++)
            {
                // A (65) to Z (90)
                if (isupper(plain[i]) != 0)
                {

                    int pos = plain[i] - 65;
                    if (isupper(key[pos]) == 0)
                    {
                        cipher[i] = key[pos] - 32;
                    }
                    else
                    {
                        cipher[i] = key[pos];
                    }
                }
                // a (97) to z (122)
                else if (islower(plain[i]) != 0)
                {
                    int pos = plain[i] - 97;
                    if (islower(key[pos]) == 0)
                    {
                        cipher[i] = key[pos] + 32;
                    }
                    else
                    {
                        cipher[i] = key[pos];
                    }
                }
                // leave punctuation as is
                else
                {
                    cipher[i] = plain[i];
                }
            }

            // Print ciphertext
            printf("ciphertext: %s\n", cipher);
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}