#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int count_letters(string text, int lenght);
int count_words(string text, int lenght);
int count_sentences(string text, int lenght);

int main(void)
{
    string text = get_string("Text: "); //string that will be calculated
    int lenght = strlen(text);
    int letter = count_letters(text, lenght); //call the function that will count the number of letters
    int word = count_words(text, lenght); //call the function that will count the number of words
    int sentence = count_sentences(text, lenght); //call the function that will count the number of sentences
    double L = ((float) letter / (float) word) * 100; //estimated number of letter per 100 words
    double S = ((float) sentence / (float)word) * 100; //estimated number of letter per 100 words
    int index = round(0.0588 * L - 0.296 * S - 15.8); //Coleman-Liau formula
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

int count_letters(string text, int lenght)
{
    int sum_letters = 0;
    for (int i = 0; i < lenght; i ++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            sum_letters ++; //it will only sum if it's a letter (upper or lowercase)
        }
    }
    return sum_letters;
}

int count_words(string text, int lenght)
{
    int sum_words = 1;
    for (int i = 0; i < lenght; i++)
    {
        if (text[i] == ' ')
        {
            sum_words ++; //it will only sum if it's a space
        }
    }
    return sum_words;
}

int count_sentences(string text, int lenght)
{
    int sum_sentences = 0;
    for (int i = 0; i < lenght; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sum_sentences ++; //it will only sum if it's a . ? or ! (meaning that is the end of the sentence)
        }
    }
    return sum_sentences;
}