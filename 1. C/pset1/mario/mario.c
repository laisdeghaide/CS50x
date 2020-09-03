#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int height; //value of the height

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); //if the value isn't between 1 and 8, the program will keep asking for a new value

    for (int i = 0; i < height; i++) //for each row I'll compare the value of the row with the value of the column
    {
        for (int j = height - 1; j >= 0; j--) //starting the value of the column
        {
            if (i >= j) //if the value of the row >= value of the column, that means I need to print #
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

}