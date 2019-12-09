#include "encryption.h"
#include "tests.h"

void test()
{
    // Test Strings
    char string_test_1[] = "hello, world!";
    char string_test_2[] = "123456";
    char string_test_3[] = "My NaMe iS BaTuHaN!";
    char string_test_4[] = "aAbBcCpPdD";
    char string_test_5[] = "#4$½!2&=?yy";

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

    buffer = matrix_cipher_encrypt(string_test_1, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_1, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_2, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_2, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_3, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_3, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_4, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_4, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    buffer = matrix_cipher_encrypt(string_test_5, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_5, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    char string_test_6[] = "Hello my friend. It is I";

    buffer = matrix_cipher_encrypt(string_test_6, row, col);
    buffer_1 = matrix_cipher_decrypt(buffer, col, row);
    printf("%s -> %s -> %s\n", string_test_6, buffer, buffer_1);
    free(buffer);
    free(buffer_1);

    printf("Only works for strings that have the length that has an integer square root, like 3x3 or 4x4\n\n");

    // RSA Cipher Test

    KeyPair *Keys = generate_keypairs();
    long long int *int_buffer;

    int_buffer = RSA_encrypt(string_test_1, Keys[0]);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_1), Keys[1]);
    printf("%s -> Too many numbers -> %s\n", string_test_1, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_2, Keys[0]);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_2), Keys[1]);
    printf("%s -> Too many numbers -> %s\n", string_test_2, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_3, Keys[0]);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_3), Keys[1]);
    printf("%s -> Too many numbers -> %s\n", string_test_3, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_4, Keys[0]);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_4), Keys[1]);
    printf("%s -> Too many numbers -> %s\n", string_test_4, buffer_1);
    free(int_buffer);
    free(buffer_1);

    int_buffer = RSA_encrypt(string_test_5, Keys[0]);
    buffer_1 = RSA_decrypt(int_buffer, strlen(string_test_5), Keys[1]);
    printf("%s -> Too many numbers -> %s\n", string_test_5, buffer_1);
    free(int_buffer);
    free(buffer_1);

    printf("\n\n\n");
}
