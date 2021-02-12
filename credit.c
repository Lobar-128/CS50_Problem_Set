#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char digit_array[20];
    long k = 10;
    int i = 0, sum = 0, sum2 = 0;
    int count, total;
    long b, c, d;
    long a = get_long("Number: \n");
    
    //get digits of number
    while(a>0)
    { 
        b = a/k; 
        c = b*k;
        d = a - c;
        d = d/(k/10);
        digit_array[i] = d;
        i++;
        a = c;
        k = k*10;
    };
    count = i;
    
    for(i=1; i<count; i=i+2)
    {   int s;
        //multplication by 2 
        s = digit_array[i]*2;
        
     
        //check if multiplication  is less/more than 10, and get the digits
        if (s>=10)
        {
            a = s % 10;
            b = 1;
            sum = sum + a + b;
        }
        else 
        {
            sum = sum + s;
        };
    }
    //let’s add that sum to the sum of the digits that weren’t multiplied by 2 
    for (i=0; i<count; i=i+2)
    { 
        sum2 = sum2 + digit_array[i];
    }
    total = sum + sum2;
    
    if (total % 10 == 0)
    {   
        if (count==15 && digit_array[count-1]==3 && (digit_array[count-2]==4 || digit_array[count-2]==7))
        {
            printf("AMEX\n");
        }
        else if ((count==16 && digit_array[count-1]==5) && (digit_array[count-2]==1 || digit_array[count-2]==2 || digit_array[count-2]==3 || digit_array[count-2]==4 || digit_array[count-2]==5))
        {
            printf("MASTERCARD\n");
        }
        else if ((count==16 || count==13) && digit_array[count-1]==4)
        {
            printf("VISA\n");
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
