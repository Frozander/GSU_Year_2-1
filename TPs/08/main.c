#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// Color Codes
#define C_RESET "\033[0m"
#define C_RED "\033[0;31m"
#define C_GREEN "\033[0;32m"
#define C_MAGENTA "\033[01;35m"
#define C_YELLOW "\033[0;33m"

#include "encryption.h"
#include "tests.h"

int main(int argc, char const *argv[])
{
    if (argc == 2 && !strcmp(argv[1], "--test"))
        test();
    else if (argc == 1)
    {
        printf("You can also add the flag '--test' to see each encoding and see its shortcomings...\n");

        char input_str[256];
        printf("Enter your message: ");
        scanf("%[^\n]s", input_str);

        int offset;
        printf("Enter an offset for ceasar cipher: ");
        scanf("%d", &offset);

        char key[256];
        printf("Enter a key for vigenere cipher: ");
        scanf("%s", key);
        char *ext_key = generate_vigenere_key(key, strlen(input_str));

        int p = 2, q = 13;
        printf("Enter p for RSA (recommended: 2): ");
        scanf("%d", &p);
        printf("Enter q for RSA (recommended: 13): ");
        scanf("%d", &q);

        char *out_caesar = caesar_cipher_encrypt(input_str, offset);
        char *dec_caesar = caesar_cipher_decrypt(out_caesar, offset);

        char *out_vigenere = vignere_cipher_encrypt(input_str, ext_key);
        char *dec_vigenere = vignere_cipher_decrypt(out_vigenere, ext_key);

        char *out_matrix = matrix_cipher_encrypt(input_str);
        char *dec_matrix = matrix_cipher_decrypt(out_matrix);

        long double *out_RSA = RSA_encrypt(input_str, p, q);
        char *dec_RSA = RSA_decrypt(out_RSA, strlen(input_str), p, q);

        // Printing
        printf("\n\n");

        printf("\033[0;32mCaesar  :\033[0m %s -> %s -> %s\n", input_str, out_caesar, dec_caesar);
        printf("\033[0;32mVigenere:\033[0m %s -> %s -> %s\n", input_str, out_vigenere, dec_vigenere);
        printf("\033[0;32mMatrix  :\033[0m %s -> %s -> %s\n", input_str, out_matrix, dec_matrix);

        printf("\033[0;32mRSA     :\033[0m %s -> ", input_str);
        rsa_print(out_RSA, strlen(input_str));
        printf("> %s\n", dec_RSA);
    } else {
        printf("Usage: program [--test]\n");
        return 1;
    }

    return 0;
}
