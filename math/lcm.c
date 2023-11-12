#include "math.h"
#include <stdlib.h>

int lcm(int a, int b)
{
    int result = divide(abs(multiply(a,b)), gcd(a,b));
    
    return result;
}