int lcm(int a, int b)
{
    int result = divide(multiply(a,b), gcd(a,b));
    
    return result;
}