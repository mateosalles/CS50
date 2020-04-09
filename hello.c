//Greeting the user
#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool isEmpty(string input); //c:20 
string askName(void); //c:33

int main(void)
{
    printf("Hello, %s!\n", askName());
}






//checks if a string is empty
bool isEmpty(string input)
{
    if (strncmp(input, "\0", 1) != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//asks for the user's name
string askName(void)
{
    string answer;
    do
    {
        answer = get_string("What's your name?\n");
    }
    while (isEmpty(answer)); 
    return answer;   
}

