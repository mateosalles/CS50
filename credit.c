// Credit card validation 
// Ignores leading zeros
# include <stdio.h>
# include <stdlib.h>
# include <cs50.h>
# include <math.h>

bool check_sum(long input); //c: 73
int sum_digits(long input); //c: 116
int get_length(long input); //c: 102
void get_company(long input); //c:28

int main(void)
{
    long input = get_long("Enter credit a credit card number:\n"); 
    if (input == labs(input)) //Avoids negative numbers
    {
        if (check_sum(input))
        {
            get_company(input);
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




//Validates credit card's company
void get_company(long input)
{
    int digits = input / pow(10, (get_length(input) - 2)); //Gets the two first digits
    if (digits == 34 || digits == 37)
    {
        if (get_length(input) == 15)
        {
            printf("VALID AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (digits == 51 || digits == 52 || digits == 53 || digits == 54 || digits == 55)
    {
        if (get_length(input) == 16)
        {
            printf("VALID MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (digits / 10 == 4) //Only first digit for Visa
    {
        if (get_length(input) == 13 || get_length(input) == 16)
        {
            printf("VALID VISA\n");
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


//Verifies Luhn's Algorithm
bool check_sum(long input)
{
    int counter = 1; //To do every other number alternation
    int sum = 0;
    while (input)
    {
        if (counter % 2 == 0)  
        {
            sum += sum_digits((input % 10) * 2); //Adds the digits of the product
        } 
        else
        {
            sum += input % 10;
        }    
        input /= 10;
        counter ++;
    }
    if (sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


//Gets the amount of characters in a positive number
int get_length(long input)
{
    if (input > 0) //Avoids log0
    {
        return floor((log10(input))) + 1;
    }
    else
    {
        return 0;
    }     
}


//Returns the sum of the digits
int sum_digits(long input)
{
    int sum = 0;
    while (input)
    {
        sum += input % 10;
        input /= 10; 
    }
    return sum;   
}
