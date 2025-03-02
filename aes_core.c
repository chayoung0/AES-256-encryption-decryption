#include "aes.h"
#include "lookup_tables.h"

#include <string.h>

unsigned char previousState[16];

void AddRoundKey(unsigned char *state, unsigned char *roundKey){
	//XORing the state with the round key
	for(int i = 0; i < 16; i++){
		state[i] ^= roundKey[i];
	}
}

void SubBytes(unsigned char *state){ 
	//substitute bytes from rijndael s-box
	for(int i = 0; i < 16; i++){
		state[i]=sbox[state[i]];
	}
}

void ShiftRows(unsigned char *state){
	
	unsigned char temp[16];
	
	// First row - no shift
	temp[0] = state[0];
	temp[1] = state[5];
	temp[2] = state[10];
	temp[3] = state[15];
	
	// Second row - shift by 1
	temp[4] = state[4];
	temp[5] = state[9];
	temp[6] = state[14];
	temp[7] = state[3];
	
	// Third row - shift by 2
	temp[8] = state[8];
	temp[9] = state[13];
	temp[10] = state[2];
	temp[11] = state[7];
	
	// Fourth row - shift by 3
	temp[12] = state[12];
	temp[13] = state[1];
	temp[14] = state[6];
	temp[15] = state[11];

	memcpy(state, temp, 16);
	/*
	for(int i=0; i<16; i++){
		state[i]=temp[i];
	}*/
	
}

void MixColumns(unsigned char *state){
	
	/* 
		Multiply the state by the following matrix:
	   2 3 1 1
	   1 2 3 1
	   1 1 2 3
	   3 1 1 2
	*/	
	
	unsigned char tmp[16];
	
	tmp[0] = (unsigned char)(mul2[state[0]] ^ mul3[state[1]] ^ state[2] ^ state[3]);
	tmp[1] = (unsigned char)(state[0] ^ mul2[state[1]] ^ mul3[state[2]] ^ state[3]);
	tmp[2] = (unsigned char)(state[0] ^ state[1] ^ mul2[state[2]] ^ mul3[state[3]]);
	tmp[3] = (unsigned char)(mul3[state[0]] ^ state[1] ^ state[2] ^ mul2[state[3]]);

	tmp[4] = (unsigned char)(mul2[state[4]] ^ mul3[state[5]] ^ state[6] ^ state[7]);
	tmp[5] = (unsigned char)(state[4] ^ mul2[state[5]] ^ mul3[state[6]] ^ state[7]);
	tmp[6] = (unsigned char)(state[4] ^ state[5] ^ mul2[state[6]] ^ mul3[state[7]]);
	tmp[7] = (unsigned char)(mul3[state[4]] ^ state[5] ^ state[6] ^ mul2[state[7]]);

	tmp[8] = (unsigned char)(mul2[state[8]] ^ mul3[state[9]] ^ state[10] ^ state[11]);
	tmp[9] = (unsigned char)(state[8] ^ mul2[state[9]] ^ mul3[state[10]] ^ state[11]);
	tmp[10] = (unsigned char)(state[8] ^ state[9] ^ mul2[state[10]] ^ mul3[state[11]]);
	tmp[11] = (unsigned char)(mul3[state[8]] ^ state[9] ^ state[10] ^ mul2[state[11]]);

	tmp[12] = (unsigned char)(mul2[state[12]] ^ mul3[state[13]] ^ state[14] ^ state[15]);
	tmp[13] = (unsigned char)(state[12] ^ mul2[state[13]] ^ mul3[state[14]] ^ state[15]);
	tmp[14] = (unsigned char)(state[12] ^ state[13] ^ mul2[state[14]] ^ mul3[state[15]]);
	tmp[15] = (unsigned char)(mul3[state[12]] ^ state[13] ^ state[14] ^ mul2[state[15]]);
 
 	memcpy(state, tmp, 16);
	/*
	for(int i=0; i<16; i++){
		state[i]=temp[i];
	}*/
	
}

void InvSubBytes(unsigned char *state){
	//substitute bytes from the reverse s-box
	for(int i = 0; i < 16; i++){
		state[i] = rs_box[state[i]];
	}
}

void InvShiftRows(unsigned char *state){
	
	//shift to right
	
	/*
		 ____________		 	 ____________
		 
		|  0 4 8 12 |			|  0 4 8 12 |
		|  1 5 9 13 | 	-->		|  13 1 5 9 |
		| 2 6 10 14 |			| 10 14 2 6 |
		| 3 7 11 15 |			| 7 11 15 3 |
		____________			____________
	*/
	
	unsigned char temp[16];
	
	// First row - no shift
	temp[0] = state[0];
	temp[1] = state[13];
	temp[2] = state[10];
	temp[3] = state[7];
	
	// Second row - shift right by 1
	temp[4] = state[4];
	temp[5] = state[1];
	temp[6] = state[14];
	temp[7] = state[11];
	
	// Third row - shift right by 2
	temp[8] = state[8];
	temp[9] = state[5];
	temp[10] = state[2];
	temp[11] = state[15];
	
	// Fourth row - shift right by 3
	temp[12] = state[12];
	temp[13] = state[9];
	temp[14] = state[6];
	temp[15] = state[3];
	
	memcpy(state, temp, 16);
	/*
	for(int i=0; i<16; i++){
		state[i]=temp[i];
	}*/
	
}

void InvMixColumns(unsigned char *state){
	
	/* Multiply state by the matrix:
	0E 0B 0D 09
	09 0E 0B 0D
	0D 09 0E 0B 
	0B 0D 09 0E
	*/
	
	unsigned char tmp[16];
	
	tmp[0] = (unsigned char)(mul14[state[0]] ^ mul11[state[1]] ^ mul13[state[2]]^ mul9[state[3]]);
	tmp[1] = (unsigned char)(mul9[state[0]] ^ mul14[state[1]] ^ mul11[state[2]] ^ mul13[state[3]]);
	tmp[2] = (unsigned char)(mul13[state[0]] ^ mul9[state[1]] ^ mul14[state[2]] ^ mul11[state[3]]);
	tmp[3] = (unsigned char)(mul11[state[0]] ^ mul13[state[1]] ^ mul9[state[2]] ^ mul14[state[3]]);

	tmp[4] = (unsigned char)(mul14[state[4]] ^ mul11[state[5]] ^ mul13[state[6]]^ mul9[state[7]]);
	tmp[5] = (unsigned char)(mul9[state[4]] ^ mul14[state[5]] ^ mul11[state[6]] ^ mul13[state[7]]);
	tmp[6] = (unsigned char)(mul13[state[4]] ^ mul9[state[5]] ^ mul14[state[6]] ^ mul11[state[7]]);
	tmp[7] = (unsigned char)(mul11[state[4]] ^ mul13[state[5]] ^ mul9[state[6]] ^ mul14[state[7]]);
	
	tmp[8] = (unsigned char)(mul14[state[8]] ^ mul11[state[9]] ^ mul13[state[10]]^ mul9[state[11]]);
	tmp[9] = (unsigned char)(mul9[state[8]] ^ mul14[state[9]] ^ mul11[state[10]] ^ mul13[state[11]]);
	tmp[10] = (unsigned char)(mul13[state[8]] ^ mul9[state[9]] ^ mul14[state[10]] ^ mul11[state[11]]);
	tmp[11] = (unsigned char)(mul11[state[8]] ^ mul13[state[9]] ^ mul9[state[10]] ^ mul14[state[11]]);

	tmp[12] = (unsigned char)(mul14[state[12]] ^ mul11[state[13]] ^ mul13[state[14]]^ mul9[state[15]]);
	tmp[13] = (unsigned char)(mul9[state[12]] ^ mul14[state[13]] ^ mul11[state[14]] ^ mul13[state[15]]);
	tmp[14] = (unsigned char)(mul13[state[12]] ^ mul9[state[13]] ^ mul14[state[14]] ^ mul11[state[15]]);
	tmp[15] = (unsigned char)(mul11[state[12]] ^ mul13[state[13]] ^ mul9[state[14]] ^ mul14[state[15]]);
 
 	memcpy(state, tmp, 16);
	/*
	for(int i=0; i<16; i++){
		state[i]=temp[i];
	}*/
}

void encrypt(unsigned char *textPortion, unsigned char *key){
	
	// int numberOfRounds = 13;
	
	//copying the 16 byte text to state matrix
	unsigned char state[16];

 	for(int i=0; i < 16; i++)
        state[i] = textPortion[i];
        
    /*
	if(round == 0){	//generating initial vector iv
	
		generateIV(iv);
		for(int i=0; i<16; i++) //xoring plain text with iv
			state[i] ^= iv[i];
	}
	else{
		for(int i=0; i<16; i++) //xoring plain text with previous state
			state[i] ^= previousState[i];
	}
	*/
        
	unsigned char expandedKey[240]; //declaring expanded key array. This is where the newly generated keys are stored.
	
	KeyExpansion(expandedKey, key);	//Key expansion step of the aes
	
	// initial round
	AddRoundKey(state, expandedKey);
	
	// main rounds
	for(int round = 1; round <= 13; round++){
		SubBytes(state); 
		ShiftRows(state);
		MixColumns(state);
		AddRoundKey(state, expandedKey + 16*round); 
		//Every round uses a different key. Because keys are 16 bytes length, I increment the pointer by 16 in each round.
	}
	
	//final round
	SubBytes(state);
	ShiftRows(state);
	AddRoundKey(state, expandedKey + 224);  
	
	memcpy(textPortion, state, 16); //copying the state to text
	memcpy(previousState, state, 16);
}

void decrypt(unsigned char* encryptedText, unsigned char* key){
	
	// int numberOfRounds = 13;
	unsigned char state[16];
	unsigned char expandedKey[240];

	memcpy(state, encryptedText, 16);
	
	KeyExpansion(expandedKey, key);
	
	// initial round
	AddRoundKey(state, expandedKey + 224); 
	InvShiftRows(state);
	InvSubBytes(state);
	
	// main rounds
	for(int round = 13; round >= 1; round--){
		AddRoundKey(state, expandedKey + (16*round)); //Here, the steps proceed in the reverse order of encrypting. AddRoundKey remains the same.
		InvMixColumns(state);						// But for other steps, inversed version of the functions are needed.
		InvShiftRows(state);
		InvSubBytes(state); 
	}
	
	//final round
	AddRoundKey(state, expandedKey);
	
	//lastly, combine with iv
/*	for(int i=0; i<16; i++) 
		state[i] ^= iv[i];
*/	
	
	/*for(int i = 0; i < 16; i++)
        encryptedText[i] = state[i];*/
	memcpy(encryptedText, state, 16);
	
}