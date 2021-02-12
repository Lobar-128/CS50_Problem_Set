#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void ciphertext (string text,int k);

int main(int argc, string argv[])
{   
    int flag = 0;
    int key = 0;
    
    for (int i = 1; i < argc; i++)
    {   int x; 
        int len = strlen(argv[i]);
        int m = len-1;
        //conversion from character to integer
        for (int j = 0; j<len; j++)
        {   
            char c = argv[i][j];    
            if (c>='0' && c<='9')
            {   
                x =  (c-'0')*pow(10,m); 
                key = key + x;
                m--;
            }
            else
            {
                flag = 1;
            }
        }  
    }
    if(flag==1)
    {
        printf("Usage: /caesar key\n");
        return 1;
    }
    else
    {
        string text = get_string("plaintext: ");
       
        
        
        ciphertext (text,key);
        
    }
    //printf("ciphertext: %c\n", text[1]);

    return 0;
}




    void ciphertext (string text,int k)
    {   
        char Up = 'A';
        char Upper[26];
        char Low = 'a';
        char Lower[26];
    
        //Array of Uppercase letters
        for (int i=0; i<26; i++)
        {
            Upper[i] = Up;
            Up = Up+1;
        }
         // Array of lowercase letters
        for (int i=0; i<26; i++)
        {
            Lower[i] = Low;
            Low = Low+1;
        }
        
        // cryption of the text
        printf("ciphertext: ");
        for (int i=0; i<strlen(text); i++)
        {
            for (int j=0; j<26; j++)
            {
                if (text[i]==Upper[j])
                {
                    printf("%c", Upper[(j+k)%26]);
                }
                else if (text[i]==Lower[j])
                {
                    printf("%c", Lower[(j+k)%26]);
                }
                else if (text[i]==' ')
                {
                    printf("%c", ' ');
                    i++;
                }
                else if (text[i]==',')
                {
                    printf("%c", ',');
                    i++;
                }
                else if (text[i]=='.')
                {
                    printf("%c", '.');
                    i++;
                }
                else if (text[i]=='!')
                {
                    printf("%c", '!');
                    i++;
                }
            }  
        }
        printf("\n"); 
    }
