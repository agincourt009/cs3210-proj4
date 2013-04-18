#include "encryption.h"
#define BLOCKSIZE	1024
int encrypt(FILE* in, FILE* out, char* str){
	
	int instream_len, outstream_len, write_len;
	unsigned char input_buff[BLOCKSIZE];
	unsigned char output_buff[BLOCKSIZE + EVP_MAX_BLOCK_LENGTH];
	int count_key = 10; 
	unsigned char key[32], iv[32];
	int temp;
	EVP_CIPHER_CTX ctx;
	
	EVP_CIPHER_CTX_init(&ctx);
	temp = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, (unsigned char*)str, 
				strlen(str), count_key, key, iv);
	if(temp != 32){
		printf("error when generate key\n");
		return 0;
	}
	EVP_EncryptInit(&ctx, EVP_aes_256_cbc(), key, iv);
	
	for(;;){
		instream_len = fread(input_buff, sizeof(*input_buff), BLOCKSIZE, in);
		if(instream_len <= 0){
			break;
		}
		EVP_EncryptUpdate(&ctx, output_buff, &outstream_len,
						input_buff, instream_len);
		write_len = fwrite(output_buff, sizeof(*output_buff), outstream_len, out);
	}
	EVP_EncryptFinal(&ctx, output_buff, &outstream_len);
	fwrite(output_buff, sizeof(*output_buff), outstream_len, out);
	EVP_CIPHER_CTX_cleanup(&ctx);
	return 1;
}

int decrypt(FILE* in, FILE* out, char* str){
	
	int instream_len, outstream_len, write_len;
	unsigned char input_buff[BLOCKSIZE];
	unsigned char output_buff[BLOCKSIZE + EVP_MAX_BLOCK_LENGTH];
	int count_key = 10; 
	unsigned char key[32], iv[32];
	int temp;
	EVP_CIPHER_CTX ctx;
	
	EVP_CIPHER_CTX_init(&ctx);
	temp = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, (unsigned char*)str, 
				strlen(str), count_key, key, iv);
	if(temp != 32){
		printf("error when generate key\n");
		return 0;
	}
	EVP_DecryptInit(&ctx, EVP_aes_256_cbc(), key, iv);
	
	for(;;){
		instream_len = fread(input_buff, sizeof(*input_buff), BLOCKSIZE, in);
		if(instream_len <= 0){
			break;
		}
		EVP_DecryptUpdate(&ctx, output_buff, &outstream_len,
						input_buff, instream_len);
		write_len = fwrite(output_buff, sizeof(*output_buff), outstream_len, out);
	}
	EVP_DecryptFinal(&ctx, output_buff, &outstream_len);
	fwrite(output_buff, sizeof(*output_buff), outstream_len, out);
	EVP_CIPHER_CTX_cleanup(&ctx);
	return 1;
	
}
