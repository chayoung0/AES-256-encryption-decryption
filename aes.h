#ifndef AES_H
#define AES_H

#include <stddef.h>

void encrypt(unsigned char *textPortion, unsigned char *key);
void decrypt(unsigned char* encryptedText, unsigned char* key);
void generateIV(unsigned char* iv);

void keyExpansionCore(unsigned char *word, int iteration);
void KeyExpansion(unsigned char *expandedKey, unsigned char *key);

void AddRoundKey(unsigned char *state, unsigned char *roundKey);

void SubBytes(unsigned char *state);
void ShiftRows(unsigned char *state);
void MixColumns(unsigned char *state);

void InvSubBytes(unsigned char *state);
void InvShiftRows(unsigned char *state);
void InvMixColumns(unsigned char *state);

// Claude

void prepare_key(const char* input_key, unsigned char* output_key);
void to_hex(const unsigned char* data, size_t len, char* hex_out);
void print_block(const char* label, const unsigned char* block);

#endif