#include "math.h"
#include <stdio.h>


int modulus(int a, int b)
{  
    if (b == 0)
    {    
        printf("Err.");
        return -1;   
    }
    
    if (a == 0 || b == 1)
    {    
        return 0;
    }
    
    if(b < 0 && a < 0)
    {    
        b = -b;
        a = -a;   
    }
    else if (b < 0)
    {    
        b = -b;
    }
    else if (a < 0)
    {        
        a = -a;   
    }
    
    while(a >= b)
    {    
        a -= b;   
    }
    
    return a;
}