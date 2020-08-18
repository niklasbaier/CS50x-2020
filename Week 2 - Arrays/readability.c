#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    float L = (float) count_letters(text) / (float) count_words(text) * 100;
    float S = (float) count_sentences(text) / (float) count_words(text) * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int index_r = round(index);

    if (index_r < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }
    else if (index_r >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }
    printf("Grade %i\n", index_r);
    
    // printf("sentences: %i\n", count_sentences(text));
    // printf("words: %i\n", count_words(text));
    // printf("letters: %i\n", count_letters(text));
}

int count_letters(string text)
{
    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    int words = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isblank(text[i]) != 0 && (isalpha(text[i + 1]) != 0 || ispunct(text[i + 1]) != 0))
        {
            words++;
        }
    }

    // function omits the first word since it searches for the first space followed by a letter
    return words + 1;
}

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 1, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }

    return sentences;
}