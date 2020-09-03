#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int is_letter(string a);
int count_differents(string a);

int main(int argc, string argv[])
{
    if (argc != 2) //if the user passes more than 2 cla
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) //if the cla doesnt have 26 characteres
    {
        printf("Key must contain 26 characteres.\n");
        return 1;
    }
    else if ((count_differents(argv[1])) == 1) //if there is any repeated character
    {
        printf("Key must contain different characteres.\n");
        return 1;
    }
    else
    {
        if (is_letter(argv[1]) == 1) //if there is any value that isnt letter
        {
            printf("Key must contain only characteres.\n");
            return 1;
        }
        else
        {
            string key = argv[1];
            string plaintext = get_string("plaintext: ");

            printf("ciphertext: ");
            for (int i = 0; i < strlen(plaintext); i++)
            {
                if (isalpha(plaintext[i])) //if the char is a letter
                {
                    if (islower(plaintext[i])) //if it is lower case
                    {
                        int pi = plaintext[i] - 'a'; //get the index value corresponding to the letter in plaintext[i]
                        plaintext[i] = key[pi]; //find the corresponding letter in the key string and attributes to the plaintext
                        printf("%c", tolower(plaintext[i])); //print the letter
                    }
                    else
                    {
                        int pi = plaintext[i] - 'A'; //if it is lower case
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
    }
}

int count_differents(string a)
{
    int count = 0, k = 0;
    for (int i = 0; i < strlen(a); i++) //transversing the string
    {
        for (int j = 0; j < i; j++) //and comparing the character with the next ones
        {
            if ((tolower(a[j])) == (tolower(a[i])))
            {
                k = 1;
                break;
            }
        }
    }
    return k; //means that there isnt any repeate value
}


int is_letter(string a)
{
    for (int i = 0; i < strlen(a); i ++)
    {
        if ((tolower(a[i])) < 'a' || (tolower(a[i]) > 'z')) //if it isn't 97 and 122
        {
            return 1;   //then it isn't a letter
            break;
        }
    }
    return 0; //it is a letter
}