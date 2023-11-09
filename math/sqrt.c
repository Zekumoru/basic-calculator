#include "math.h"

double sqroot(int n)
{
    double result = n;
    int iterations = 10; //could be a constant
    
    if (n < 0)
    {  
        return -1; //it should be treatated as "error"
    }
    
    for (int i = 0; i < iterations; i++) //newton method
    {    
        result = (result + (n / result)) / 2;
    }
    
    return result;
}