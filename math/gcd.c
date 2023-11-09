int gcd(int a, int b) {
    
    int potentialGcd;
    
    while (b != 0){
        
        potentialGcd = b;
        b = modulus(a, b);
        a = potentialGcd;
    }
    
    return a;
}