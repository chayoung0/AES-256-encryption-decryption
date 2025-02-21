#include "aes.h"
#include "lookup_tables.h"

#include <time.h>


unsigned char iv[17];

void keyExpansionCore(unsigned char *word, int iteration){
	
	// rotate 8 bits to the left
	unsigned char temp = word[0];
	word[0]=word[1];
	word[1]=word[2];
	word[2]=word[3];
	word[3]=temp;
	
	// sbox substitution
	word[0]=sbox[word[0]];
	word[1]=sbox[word[1]];
	word[2]=sbox[word[2]];
	word[3]=sbox[word[3]];
	
	// XORing with round constant
	word[0]^=Rcon[iteration];
}

void KeyExpansion(unsigned char *expandedKey, unsigned char *key){
	
	//This step is beyond me, so just for this function, I modified an existing code, which can be found in references.
	
	/* current expanded keySize, in bytes */
    int currentSize = 0;
    int rconIteration = 1;
    int i;
    unsigned char t[4] = {0};   // temporary 4-byte variable
     
    /* set the 16,24,32 bytes of the expanded key to the input key */
    for (i = 0; i < 32; i++)
        expandedKey[i] = key[i];
    currentSize += 32;
     
    while (currentSize < 240)
    {
        /* assign the previous 4 bytes to the temporary value t */
        for (i = 0; i < 4; i++)
        {
            t[i] = expandedKey[(currentSize - 4) + i];
        }
         
        /* every 32 bytes we apply the core schedule to t and increment rconIteration afterwards */
        if(currentSize % 32 == 0)
        {
            keyExpansionCore(t, rconIteration++);
        }
 
        /* For 256-bit keys, we add an extra sbox to the calculation */
        if((currentSize % 32) == 16) {
            for(i = 0; i < 4; i++) 
                t[i] = sbox[t[i]];
        }
         
        /* We XOR t with the four-byte block 32 bytes before the new expanded key.
         * This becomes the next four bytes in the expanded key.
         */
        for(i = 0; i < 4; i++) {
            expandedKey[currentSize] = expandedKey[currentSize - 32] ^ t[i];
            currentSize++;
        }
    }
}

void generateIV(unsigned char* iv){
	//generating initial vector
	srand(time(NULL));
	int i;
 	for(i=0; i<16;i++)
		iv[i]=rand()%16;
	
}