#include "math.h"

int prime(int n)
{
    int check;
    
    for (int i = n-1; i > 1; i--)
    { 
        check = modulus(n, i);

        if (check == 0)
        {
            return 0;
        }
    }
    return 1;
}