#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float dollars; //amount of change
    int tcoins = 0; // total coins

    do
    {
        dollars = get_float("Change owed: ");
    }
    while (dollars < 0); //if the chage is <0, then the user will have to insert a new value

    int cents = round(dollars * 100);

    while (cents >= 25)
    {
        cents = cents - 25; //decrement the total amount owed
        tcoins ++; //increment the counter
    }

    //same thing for the other coins

    while (cents >= 10)
    {
        cents = cents - 10;
        tcoins ++;
    }

    while (cents >= 5)
    {
        cents = cents - 5;
        tcoins ++;
    }

    while (cents >= 1)
    {
        cents = cents - 1;
        tcoins ++;
    }

    printf("%i\n", tcoins);
}