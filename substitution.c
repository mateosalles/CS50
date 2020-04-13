//Encryption using a substitution key
# include <stdio.h>
# include <stdlib.h>
# include <cs50.h>
# include <string.h>
# include <ctype.h>

string cipher(string plain, string key); //c: 55

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        if (strlen(argv[1]) == 26)
        {
            for (int i = 0; i < 26; i++)
            {
                if (isalpha(argv[1][i]))
                {
                    for (int n = 0; n < i; n++)
                    {
                        if (argv[1][i] == argv[1][n])
                        {
                            printf("Letters can't be repeated\n");
                            return 1; //End program
                        } 
                    }
                }
                else
                {
                    printf("Key must be only letters\n");
                    return 1; //End program
                }
            }
        }
        else
        {
            printf("The key must have 26 letters\n");
            return 1; //End program
        }

        string plain = get_string("plaintext: ");
        printf("ciphertext: %s\n", cipher(plain, argv[1]));
        return 0;
    }
    else
    {
        printf("Usage ./substitution KEY\n");
        return 1; //End program
    }
}

//Encrypts input text with given key
//"A" = 65 in ASCII Code. If the letter being encrypted is "A" (65 - 65) would be position 0 in the key string
string cipher(string plain, string key)
{
    for (int i = 0; i < strlen(plain); i++)
    {
        if (isalpha(plain[i]))
        {
            if (islower(plain[i]))
            {
                plain[i] = tolower(key[toupper(plain[i]) - 65]); //Maintains lower case
            }
            else
            {
                plain[i] = toupper(key[toupper(plain[i]) - 65]); //Maintains upper case
            }
        }
    }
    return plain;
}


