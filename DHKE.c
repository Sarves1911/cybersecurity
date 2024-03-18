#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int power(long long int a, long long int b, long long int P)
 {
    if (b == 1)
        return a;

    else
        return (((long long int)pow(a, b)) % P);
}

int main() {
    long long int P, G, x, a, y, b, ka, kb;

    printf("value of prime number P: ");
    scanf("%lld", &P);
    printf("value of primitive root G: ");
    scanf("%lld", &G);

    printf("private key for Alice (a): ");
    scanf("%lld", &a);

    x = power(G, a, P);

    printf("private key for Bob (b): ");
    scanf("%lld", &b);

    y = power(G, b, P);

    ka = power(y, a, P);                            

    kb = power(x, b, P);

    printf("Secret key for Alice: %lld\n", ka);
    printf("Secret key for Bob: %lld\n", kb);

    return 0;
}