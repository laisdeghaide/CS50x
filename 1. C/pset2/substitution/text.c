#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


bool is_letter(string a);

int main(int argc, string argv[])
{
    if (argc == 2)  //if the cla equals 2
    {
        string key = argv[1];   //key is the string written in cla

        if(is_letter(key) == true) //only if its length equals 26
        {
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            string alphabet = "abcdefghijklmnopqrstuvwxyz";
            for(int i = 0; i < strlen(plaintext); i++)
            {
                if (isalpha(plaintext[i])) //if the char is a letter
                {
                    if(islower(plaintext[i]))
                    {
                        int pi = plaintext[i] - 'a';
                        plaintext[i] = key[pi];
                        printf("%c", tolower(plaintext[i]));
                    }
                    else
                    {
                        int pi = plaintext[i] - 'A';
                        plaintext[i] = key[pi];
                        printf("%c", toupper(plaintext[i]));
                    }
                }
                else
                {
                    printf("%c", plaintext[i]); //if it is not a letter, then maintain the same
                }
            }
            printf("\n");
            return 0;
        }
        else
        {
            is_letter(argv[1]);
        }
    }
    else
    {
        is_letter(argv[1]);
    }
}

bool is_letter(string a)
{
    if(strlen(a) == 26)
    {
        int count = 0;
        for (char c = 'a'; c <= 'z'; c++)
        {
            for(int i = 0; i < 26; i++)
            {
                if(tolower(a[i]) == c)
                {
                    count ++;
                }
            }
        }
        if (count == 26)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}