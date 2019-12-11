#include "encryption.h"
#include "tests.h"

void test()
{
    // Test Strings
    char string_test_1[] = "hello, world!";
    char string_test_2[] = "123456";
    char string_test_3[] = "My NaMe iS BaTuHaN!";
    char string_test_4[] = "aAbBcCpPdD";
    char string_test_5[] = "4½!2&=?yy";

    char *buffer;
    char *buffer_1;
    int offset = 0;
    printf("Enter offset: ");
    scanf("%d", &offset);

    buffer = caesar_cipher_encrypt(string_test_1, offset);
    buffer_1 = caesar_cipher_decrypt(buffer, offset);
    printf("%s -> %s -> %s\n", string_test_1, buffer, buffer_1);
    free(buffer);
    free(buffer_1);
    buffer = caesar_cipher_encrypt(string_test_2, offset);
    buffer_1 = caesar_cipher_decrypt(buffer, offset);
    printf("%s -> %s -> %s\n", string_test_2, buffer, buffer_1);
    free(buffer);
    free(buffer_1);
    buffer = caesar_cipher_encrypt(string_test_3, offset);
    buffer_1 = caesar_cipher_decrypt(buffer, offset);
    printf("%s -> %s -> %s\n", string_test_3, buffer, buffer_1);
    free(buffer);
    free(buffer_1);
    buffer = caesar_cipher_encrypt(string_test_4, offset);
    buffer_1 = caesar_cipher_decrypt(buffer, offset);
    printf("%s -> %s -> %s\n", string_test_4, buffer, buffer_1);
    free(buffer);
    free(buffer_1);
    buffer = caesar_cipher_encrypt(string_test_5, offset);
    buffer_1 = caesar_cipher_decrypt(buffer, offset);
    printf("%s -> %s -> %s\n", string_test_5, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    printf("\n\n\n");
    // Vigenere cipher test

    char encode_text[] = "encode";

    buffer = vignere_cipher_encrypt(string_test_1, encode_text);
    buffer_1 = vignere_cipher_decrypt(buffer, encode_text);
    printf("%s -> %s -> %s\n", string_test_1, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = vignere_cipher_encrypt(string_test_2, encode_text);
    buffer_1 = vignere_cipher_decrypt(buffer, encode_text);
    printf("%s -> %s -> %s\n", string_test_2, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = vignere_cipher_encrypt(string_test_3, encode_text);
    buffer_1 = vignere_cipher_decrypt(buffer, encode_text);
    printf("%s -> %s -> %s\n", string_test_3, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = vignere_cipher_encrypt(string_test_4, encode_text);
    buffer_1 = vignere_cipher_decrypt(buffer, encode_text);
    printf("%s -> %s -> %s\n", string_test_4, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = vignere_cipher_encrypt(string_test_5, encode_text);
    buffer_1 = vignere_cipher_decrypt(buffer, encode_text);
    printf("%s -> %s -> %s\n", string_test_5, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    printf("\n\n\n");
    // Matrix Cipher

    int col = 5, row = 5;

    buffer = matrix_cipher_encrypt(string_test_1);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_1, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_2);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_2, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_3);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_3, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_4);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_4, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_5);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_5, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    char string_test_6[] = "Hello my friend. It is I";

    buffer = matrix_cipher_encrypt(string_test_6);
    buffer_1 = matrix_cipher_decrypt(buffer);
    printf("%s -> %s -> %s\n", string_test_6, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    printf("\n\n\n");
    // RSA Cipher Test

    long double *int_buffer;
    int p = 2, q = 13;

    int_buffer = RSA_encrypt(string_test_1, p, q);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_1), p, q);
    //rsa_print(int_buffer, strlen(string_test_1));
    printf("%s -> Too many numbers -> %s\n", string_test_1, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_2, p, q);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_2), p, q);
    printf("%s -> Too many numbers -> %s\n", string_test_2, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_3, p, q);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_3), p, q);
    printf("%s -> Too many numbers -> %s\n", string_test_3, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_4, p, q);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_4), p, q);
    printf("%s -> Too many numbers -> %s\n", string_test_4, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_5, p, q);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_5), p, q);
    printf("%s -> Too many numbers -> %s\n", string_test_5, buffer_1);
    free(int_buffer);
    free(buffer_1);

    printf("\n\n\n");
}
