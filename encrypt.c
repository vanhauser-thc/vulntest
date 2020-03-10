#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <string.h>

int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
  EVP_CIPHER_CTX *ctx;
  int len;
  int ciphertext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    exit(-1);

  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_des_ecb(), NULL, key, iv))
    exit(-1);

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    exit(-1);
  ciphertext_len = len;

  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    exit(-1);
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int main(int argc, char *argv[]) {
  /*
   * Set up the key and iv. Do I need to say to not hard code these in a
   * real application? :-)
   */
  if (argc < 3)
    exit(-1);

  /* A 256 bit key */
  unsigned char *key = argv[1];

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)"0123456789012345";

  /* Message to be encrypted */
  unsigned char *plaintext = argv[2];

  /*
   * Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, depending on the
   * algorithm and mode.
   */
  unsigned char ciphertext[1024];

  int ciphertext_len;

  /* Encrypt the plaintext */
  ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv, ciphertext);

  /* Do something useful with the ciphertext here */
  BIO_dump_fp(stdout, (const char *)ciphertext, ciphertext_len);

  return ciphertext_len;
}
