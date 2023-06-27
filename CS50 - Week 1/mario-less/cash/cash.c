#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}

int get_cents(void)
{
    // Prompt user for cents required:
    int cents = 0;
    do
    {
        cents = get_int("How many cents do you need?");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    // Calculate how many qaurters are needed:
    int quarter = 25;
    int quarters = 0;
    while (cents >= quarter)
    {
        quarters++;
        cents = cents - quarter;
    }
    return quarters;
}

int calculate_dimes(int cents)
{
    // Calculate how many dimes are needed:
    int dime = 10;
    int dimes = 0;
    while (cents >= dime)
    {
        dimes++;
        cents = cents - dime;
    }
    return dimes;
}

int calculate_nickels(int cents)
{
    // Calculate how many qaurters are needed:
    int nickel = 5;
    int nickels = 0;
    while (cents >= nickel)
    {
        nickels++;
        cents = cents - nickel;
    }
    return nickels;
}

int calculate_pennies(int cents)
{
    // Calculate how many pennies are needed:
    int penny = 1;
    int pennies = 0;
    while (cents >= penny)
    {
        pennies++;
        cents = cents - penny;
    }
    return pennies;
}
