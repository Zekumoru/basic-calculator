#include "math.h"
#include <stdio.h>

int divide(int a, int b)
{
    int res = 0;         //result output
    int resNegative = 0; //flag for negative result
    
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
    
    if(b < 0 && a < 0)  //change of sign for negative values
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
    
    if (resNegative) //if flag then negative result
    {    
        return -res;   
    }
    
    return res;
}