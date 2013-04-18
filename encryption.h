#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/aes.h>

#define BLOCKSIZE	1024

int encrypt(FILE* in, FILE* out, char* str);
int decrypt(FILE* in, FILE* out, char* str);

#endif
