#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;

// Function to calculate the GCD of p and q
long long gcd(long long p, long long q)
{
    if (p == 0)
        return q;
    return gcd(q % p, p);
}

// Function to check if a number is prime
bool is_prime(long long number)
{
    long long i;
    for (i = 2; i <= sqrt(number); i++)
    {
        if (number % i == 0)
            return false;
    }
    return true;
}

// Function to generate a random prime number
long long generate_random_prime(long long min, long long max)
{
    long long prime;
    do
    {
        prime = (rand() % (max - min + 1)) + min;
    } while (!is_prime(prime));
    return prime;
}

// Function for modular exponentiation
long long modular_exponentiation(long long base, long long exponent, long long modulus)
{
    long long result = 1;
    base = base % modulus;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function for modular inverse using extended Euclidean algorithm
long long modular_inverse(long long a, long long m)
{
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    // Apply extended Euclidean algorithm
    while (a > 1)
    {
        q = a / m;
        t = m;

        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    // Make x1 positive
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main()
{
    // Declare the variables
    long long min = 5000;
    long long max = 15000;
    srand(time(0));
    long long p = generate_random_prime(min, max);
    long long q = generate_random_prime(min, max);
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    long long e = 7;
    long long d = modular_inverse(e, phi);

    // Collect the inputs from the user
    cout << "----- Welcome to the RSA Algorithm Calculator -----" << endl;
    cout << "---------------------------------------------------" << endl;

    // Run the program and observe the output
    cout << "-------------- Display the variables --------------" << endl;
    cout << "The prime numbers are: " << p << ", " << q << endl;
    cout << "The modulus is: " << n << " and phi(n) is: " << phi << endl;
    cout << "The public key is: " << e << ", " << n << endl;
    cout << "The private key is: " << d << ", " << n << endl;
    cout << "------------- Calculating the message -------------" << endl;

    // generate a random number for m
    long long m = (rand() % (n - 1)) + 1;
    cout << "The original message is: " << m << endl;

    // Encrypting the message
    long long c = modular_exponentiation(m, e, n);
    cout << "The encrypted message is: " << c << endl;

    // Decrypting the message
    long long decrypted_message = modular_exponentiation(c, d, n);
    cout << "The decrypted message is: " << decrypted_message << endl;

    return 0;
}
