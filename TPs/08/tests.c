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
}
