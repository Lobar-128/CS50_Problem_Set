#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    
    do
    {
        n = get_int("Type the height of pyramid, between 1 and 8\n: ");
    }
    while (n<1 || n>8);
    
    for (int i=1; i<=n; i++)
    {
        for (int j=1; j<=i; j++)
        {   
            if (j==1)
            {
                for (int k=1; k<=(n-i); k++)
                {
                        printf(" ");
                }
         
            }
                 printf("#");
        }
        
        printf("  ");
        
        for (int j=1; j<=i; j++)
        {
            printf("#");
        }   
        
        printf("\n");
    }
    
}
