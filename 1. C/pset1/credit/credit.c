#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long int number = get_long("Number: ");
    long int numbert = number;
    long int checksum[18];
    long int others[18]; //checksum is the vector containing the numbers that will be multiplied by 2, ///checksum is the vector containing the other numbers
    int i = 0, sum = 0, newsum = 0, first_digit, second_digit, lenght = 0;

    //long int numbert = number; //create a new variable to store the value, so I wont loose it

    while (number > 0)
    {
        long int u = number % 10; //get the last digit of the number
        others[i] = u; //and store it on the vector other
        number = number / 10; //divide the number
        lenght++;
        long int v = number % 10; //and get the new last digit (which is the second last digit that will want multiply)
        checksum[i] = v; //store it on checksum
        number = number / 10;
        i ++; //increment i to pass to the nex place of the vector
        lenght++;
    }

    while (numbert >= 10) //get the first two digits of the card
    {
        first_digit = numbert / 10;
        second_digit = numbert % 10;
        numbert = numbert / 10;
    }

    for (int j = 0; j < i; j++)
    {
        checksum[j] = checksum[j] * 2;  //multiply the numbers by 2
        if (checksum[j] > 9) //if the number has to 2 places, I need to get each and multiply by 2 too
        {
            int division = checksum[j] / 10; //here I get the first place
            int module = checksum[j] % 10; //here I get the second place, which is the rest of the division
            sum = sum + division + module; //and the I sum these two numbers with the sum
        }
        else
        {
            sum = sum + checksum[j];
        }
    }

    for (int j = 0; j < i; j++)
    {
        newsum = newsum + others[j];  //newsum is the sum of the numbers that werent mutiplied by 2
    }

    newsum = newsum + sum; //and then sum the two results of each vector

    if (newsum % 10 == 0) //if the last digit of the number is 0, then is valid, and I'll check the if it's VISA, MASTER, etc.
    {
        if ((lenght - 1) == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
        }

        else if (lenght == 16 && first_digit == 5 && (second_digit >= 1 && second_digit <= 5))
        {
            printf("MASTERCARD\n");
        }
        else if ((lenght == 16 || lenght == 13) && first_digit == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}

