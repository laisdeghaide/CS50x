#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int is_digit(string a);

int main(int argc, string argv[])
{
    if (argc != 2 || (is_digit(argv[1]) == 1)) //if the cla is different than 2 or the key isn't a number
    {
        printf("Usage: ./caesar key\n"); //then is not valid
        return 1;
    }
    else
    {
        int k = atoi(argv[1]);  //convert the key passed as string to int

        string plaintext = get_string("plaintext: "); //input string
        int length = strlen(plaintext);

        printf("ciphertext: ");

        for (int i = 0; i < length; i++)
        {
            if (isalpha(plaintext[i])) //if the char is a letter
            {
                int convert_char = islower(plaintext[i]) ? 97 : 65;
                int pi = plaintext[i] - convert_char; //convert ascii to alphabetical index
                int ci = (pi + k) % 26; //calculate ciphertext
                printf("%c", (ci + convert_char)); //print the convert result back in ascii
            }
            else
            {
                printf("%c", plaintext[i]); //if it is not a letter, then maintain the same
            }
        }
    }
    printf("\n");

    return 0;
}

int is_digit(string a) //function tha checks if the input string (key) is a number
{
    for (int i = 0; i < strlen(a); i ++)
    {
        if (a[i] <= '0' || a[i] >= '9') //if it isn't between o and 9
        {
            return 1;   //then it isn't a number
            break;
        }
    }
    return 0; //it is a number
}