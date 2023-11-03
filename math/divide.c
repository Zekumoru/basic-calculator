#include "math.h"
#include <stdio.h>

int divisione(int a, int b)
{
    
    int res = 0;
    int resNegative = 0;
    
    if (b == 0) 
    {  
        printf("Inf ");
        return -1;    
    }
    
    if (a == 0)
    {    
        return res;
    }
    
    if (b == 1)
    {
        return a;
    }
    
    if(b < 0 && a < 0)
    {    
        b = -b;
        a = -a;    
    }
    else if (b < 0)
    {
        b = -b;
        resNegative = 1;
    }
    else if (a < 0)
    {
        a = -a;
        resNegative = 1;
    }

    do
    {    
        a -= b;
        res++;   
    }
    while (b <= a);
    
    if (resNegative)
    {    
        return -res;   
    }
    
    return res;
}