#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void ciphertext (string text,int keyInt[100], int lenght_array);

int main(int argc, string argv[])
{   
    int flag = 0;
    int keyInt[26];
    char keyUp[26];
    char keyLow[26];
    int k=0;
    char Up = 'A';
    char Low = 'a';

    for(int i=0; i<26; i++)
    {
        keyUp[i] = Up;
        keyLow[i] = Low;
        Up++;
        Low++;
    }
    if (argc==2)
    {  
       for (int i= 1; i < argc; i++)
       {   
            int len = strlen(argv[i]);
        
        //conversion from character to integer
            for (int j = 0; j<len; j++)
            {   
                if(isdigit(argv[i][j])==0 || (argv[i][j]!=' '))
                {  
                    flag = 1;
                   for(int l=0; l<26; l++)
                   {
                       if (argv[i][j]==keyUp[l]
                        || argv[i][j]==keyLow[l])
                        {
                           keyInt[k] = l;
                           k++;
                        }
                   }   
                }
            } 
        }   
    }
    else
    {
      printf("Usage: ./vigenere keyword\n");
      return 1; 
    }
    
    if(flag==1)
    {
        string text = get_string("plaintext: ");
        ciphertext (text,keyInt,k);
    }
    else
    {
        printf("Usage: /caesar key\n");
        return 1;
    } 
}


    void ciphertext (string text,int keyInt[], int length_array)
    {   
        char Up = 'A';
        char Upper[26];
        char Low = 'a';
        char Lower[26];
        int l = 0;
        int len = strlen(text);
  
        //Array of Uppercase and Lowercase letters
        for (int i=0; i<26; i++)
        {
            Upper[i] = Up;
            Up = Up+1;
            Lower[i] = Low;
            Low = Low+1;
        }
        
        // cryption of the text
        printf("ciphertext: ");
        for (int i=0; i<len; i++) //for each character of the text
        {     
             if(l<length_array)
            {
                for (int j=0; j<26; j++)       
                {            
                    if (text[i]==Upper[j])
                    {
                        //printf("keyInt: %d ", keyInt[l]);
                        printf("%c", Upper[(j+keyInt[l])%26]);
                        l++;
                    }
                    else if (text[i]==Lower[j])
                    {
                        //printf("keyInt: %d ", keyInt[l]);
                        printf("%c", Lower[(j+keyInt[l])%26]);
                        l++;
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
            else 
            {
                l=0;
                i--;
            }

        }
        printf("\n"); 
    }

