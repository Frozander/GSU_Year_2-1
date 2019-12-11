#include "encryption.h"

char to_lower(char c)
{
    if (isalpha(c))
        c += 'a' - 'A';
    return c;
}

char to_upper(char c)
{
    if (isalpha(c))
        c -= 'a' - 'A';
    return c;
}

// In C % is not a modulo operator but a remainder operator.
// So I had to use a custom mod function
int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

// Caesar
char *caesar_cipher_encrypt(char *input, int offset)
{
    char* new_str = strdup(input);
    int str_len = strlen(input);

    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            if (isupper(new_str[i]))
                new_str[i] = (mod((new_str[i] + offset - 'A'), 26)) + 'A';
            else
                new_str[i] = (mod((new_str[i] + offset - 'a'), 26)) + 'a';
        }
    return new_str;
}

char *caesar_cipher_decrypt(char *input, int offset)
{
    return caesar_cipher_encrypt(input, -offset);
}

// Vigenere

char *generate_vigenere_key(char *input, int msg_len)
{
    char *new_key = malloc(sizeof(char) * msg_len);
    int key_len = strlen(input);
    int j = 0;
    for (size_t i = 0; i < msg_len; ++i, ++j)
    {
        if (j == key_len) j = 0;
        new_key[i] = input[j];
    }
    return new_key;
}

char *vignere_cipher_encrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    char *key = generate_vigenere_key(ref, str_len);
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] + key[i]);
            if(isupper(new_str[i]))
                new_val = mod(new_val - 'A', 26) + 'A';
            else
                new_val = mod(new_val - 'a', 26) + 'a';
            new_str[i] = new_val;
        }
    free(key);
    return new_str;
}

char *vignere_cipher_decrypt(char *input, char *ref)
{
    char *new_str = strdup(input);
    int str_len = strlen(input);

    char *key = generate_vigenere_key(ref, str_len);
    for (int i = 0; i < str_len; ++i)
        if (isalpha(new_str[i]))
        {
            int new_val = (input[i] - key[i]);
            if(isupper(new_str[i]))
                new_val = mod(new_val - 'A', 26) + 'A';
            else
                new_val = mod(new_val - 'a', 26) + 'a';
            new_str[i] = new_val;
        }
    free(key);
    return new_str;
}

// Matrix Cipher

int is_square(int x)
{
    int r = sqrt(x);
    if ((r * r) == x) return r;
    else return r + 1;
}

char *matrix_cipher_encrypt(char *input)
{
    int str_len = strlen(input);
    for (int c = 0; c < str_len; ++c)
        if (c == PADDING){
            printf("Padding character detected in the string: %c", PADDING);
            return input;
        }
    int size = is_square(str_len);
    char *new_str = malloc(size * size * sizeof(char));
    int matrix[size][size];
    size_t i;

    int cur = 0;
    for (i = 0; i < size * size; ++i, ++cur)
    {
        if (cur < str_len)
            matrix[i / size][i % size] = input[cur];
        else
            matrix[i / size][i % size] = PADDING;
    }

    for (i = 0; i < size * size; ++i)
        new_str[i] = matrix[i % size][i / size];

    return new_str;
}

char *matrix_cipher_decrypt(char *input)
{
    int str_len = strlen(input);
    int size = is_square(str_len);
    char *new_str = malloc(size * size * sizeof(char));
    int matrix[size][size];
    size_t i;

    int cur = 0;
    for (i = 0; i < size * size; ++i, ++cur)
    {
        if (cur < str_len)
            matrix[i / size][i % size] = input[cur];
        else
            matrix[i / size][i % size] = PADDING;
    }

    for (i = 0; i < size * size; ++i)
    {
        if(matrix[i % size][i / size] == PADDING) continue;
        new_str[i] = matrix[i % size][i / size];
    }
    
    return new_str;
}

int gcd(int a, int b)
{
    int tmp;
    while(1)
    {
        tmp = a % b;
        if (tmp == 0)
            return b;
        a = b;
        b = tmp;
    }
}

int is_prime(long double n)
{
    long double sqr = sqrtl(n);
    for(int i= 2; i <= sqr; ++i)
        if(fmodl(n, i)==0)
            return 0;
    return 1;
}
/*

long double generate_prime()
{
    long double lower = rand() %  (INT16_MAX/2);
    long double upper = INT16_MAX;
    int flag;

    printf("Generating Prime... This might take long...\n");
    while (lower < upper)
    {
        if (lower++ % 2 == 0) continue;
        flag = is_prime(lower);
        if (flag == 1) return lower;
        ++lower;
    }
}

long double is_coprime(long double n, long double m)
{
    return gcd(n, m) == 1;
}

long double generate_coprime(long double n)
{
    uint64_t coprime;
    printf("Generating Coprime... This might take long...\n");
    while (1)
    {
        coprime = (rand() % RAND_MAX - 2) + 2;
        if (is_coprime(coprime, n))
            return coprime;
    }
}

long double mod_inverse_naive(long double n, long double m)
{
    n = n % m;

    for (int d = 1; d < m; ++d)
        if ((n * d) % m == 1)
            return d;
}

long double mod_inverse(long double n, long double m)
{
    long double m1 = m;
    long double y = 0;
    long double x = 1;

    if (m == 1) return 0;

    while(n > 1)
    {
        long double quotient = n / m;

        // Default euclid algorithm for gcd
        long double t = m;
        m = n % m;
        n = t;

        y = x - quotient * y;
        x = t;
    }

    if (x < 0) x += m1;
    return x;
}

KeyPair *generate_keypairs()
{
    // Public and private keys
    KeyPair *Keys = malloc(sizeof(KeyPair) * 2);

    long double p = generate_prime();
    long double q = generate_prime();
    printf("%LF\n", p);
    printf("%LF\n", q);

    long double n = p * q;

    long double totient = (p - 1) * (q - 1);
    long double e = generate_coprime(totient);
    printf("%LF\n", e);

    long double d = mod_inverse_naive(e, totient);

    Keys[0].type = PUBLIC_KEY;
    Keys[0].key_part_1 = e;
    Keys[0].key_part_2 = n;

    Keys[1].type = PRIVATE_KEY;
    Keys[1].key_part_1 = d;
    Keys[1].key_part_2 = n;

    return Keys;
}
*/
// So almost all the functions above are useless...

long double *RSA_encrypt(char *input, int p, int q)
{
    if (!is_prime(p) || !is_prime(q)) return NULL;

    long double str_len = strlen(input);

    long double n = p * q;
    long double e = 2;   // I tried to do this all randomly but
    long double totient; // C doesn't have enough randomness/math functions built-in
    totient = (p - 1) * (q - 1);

    while (e++ < totient)
        if(gcd(e, totient) == 1) break;
    
    long double d = (1 + (2 * totient)) / e;

    long double *rsa_values = malloc(str_len * sizeof(long double));
    for (size_t i = 0; i < str_len; ++i)
        rsa_values[i] = fmodl(pow(tolower(input[i]) - 96, e), n);
    return rsa_values;
}

char *RSA_decrypt(long double *input, size_t size, int p, int q)
{
    if (!is_prime(p) || !is_prime(q)) return NULL;

    long double n = p * q;
    long double e = 2;   // I tried to do this all randomly but
    long double totient; // C doesn't have enough randomness/math functions built-in
    totient = (p - 1) * (q - 1);

    while (e++ < totient)
        if(gcd(e, totient) == 1) break;
    
    long double d = (1 + (2 * totient)) / e;

    char *new_str = malloc(sizeof(char) * size);
    for (size_t i = 0; i < size; ++i)
        new_str[i] = fmodl(pow(tolower(input[i]), d), n) + 96;
    return new_str;
}

void rsa_print(long double *input, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        printf("%.0LF-", input[i]);
}