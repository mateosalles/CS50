//Program that returns the grade of a given text.
# include <cs50.h>
# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

void grade(float l, float w, float s); // c: 50

int main(void)
{
    string text;
    do //Demands text input
    {
        text = get_string("Text: ");
    }
    while (!isalnum(text[0])); //Alphanumeric value condition, only numbers are not accepted in c: 56

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;

            if (!isalpha(text[i + 1]) && text[i + 1] != 39 && text[i + 1] != 45) //Words with ' or - are considered as one
            {
                words++;
            }
            if (text[i + 1] == '\0') //In case closing last sentence is forgotten.
            {
                sentences++;
            }
        }
        else if ((text[i] == 33 || text[i] == 46 || text[i] == 63) && isalpha(text[i - 1])) //Takes into account consecutive symbols
        {
            sentences++;
        }
    }

    grade(letters, words, sentences);

}


//Calculates and prints the grade
void grade(float l, float w, float s)
{
    if (w == 0) //If no alphabetical characters were input
    {
        printf("INVALID\n");
    }
    else
    {
        float L = (l / w) * 100.0f;
        float S = (s / w) * 100.0f;
        float index = 0.0588 * L - 0.296 * S - 15.8;
        if (index < 1.0f)
        {
            printf("Before Grade 1\n");
        }
        else if (index > 16)
        {
            printf("Grade 16+\n");
        }
        else
        {
            printf("Grade %i\n", (int) rint(index));
        }
    }

}



