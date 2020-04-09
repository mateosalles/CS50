//Code to build Mario pyramids with hashes
#include <cs50.h>
#include <stdio.h>

void front_spaces(int row, int height); //c: 27
void hashes(int row); //c: 36
void print_line(int r, int h); //c: 45

int main(void)
{
    int height = 0;
    do
    {
        height = get_int("Enter height of the pyramid between 1 - 8 inclusive:\n");
    }
    while (1 > height || height > 8); //Try changing the || for a && to make bigger pyramids!!
    
    for (int r = 1; r <= height; r++)
    {
        print_line(r, height); 
    }
}



//Calculates and prints front spaces for a given row && height 
void front_spaces(int row, int height)
{
    for (int i = 0; i < height - row; i++)
    {
        printf(" ");
    }
}

//Prints the correct amount of hasshes for a given line
void hashes(int row)
{
    for (int i = 0; i < row; i++)
    {
        printf("#");
    } 
}

//Prints the line for a row in a given height :)
void print_line(int r, int h)
{
    front_spaces(r, h);
    hashes(r);
    printf("  ");
    hashes(r);
    printf("\n");
}
