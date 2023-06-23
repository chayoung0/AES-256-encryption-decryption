# AES-256-encryption-decryption
### Implementation of AES 256 encryption algorithm with C. 

AES 256 uses a 256-bit key, to encrypt a 128-bit text. If the text is larger than 128 bits, it is divided into 128-bit pieces, and each piece gets encrypted one by one. The encryption process consists of 14 rounds. 
As the first step, based on the first key, 14 new keys are generated. This is the Key Expansion step. Each round uses a different 128-bit key. Generated keys are sent to a 240-byte array. 
In CBC mode, a 128-bit random initialization vector (IV) is generated. This IV is XORed with text that is also 128-bit. 

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/fecc1b4e-7d15-491f-858d-34b57717ddd0)
Figure 1. Combining the plain text with IV

As the initial round, the state is XORed with the round key, that is, the first 16 byte of the expanded key array. 
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/9505379f-6c51-422e-8015-fe6cfbfd6566)
Figure 2. Add Round Key step algorithm

Round Steps
Sub Bytes Step: Each element of the state array is replaced by the corresponding value at the Rijndael S-box (S is for substitution). For example, if the value in state[i] is equal to 0x2A, the corresponding value is at the 2nd row and the 10th columns of the s-box, that is, 0xE5.
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/f3d4b9ae-4988-4662-a247-1d0a350a6b4e)
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/481f1f59-1122-4c9d-802b-293c170119f7)
Figure 3. Replace state’s elements using Sbox.

Shift Rows Step: The second, third and fourth rows are shifted to the right by 1, 2, 3 respectively. The first row remains unchanged.
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/fb5b1897-9d21-4de7-b858-885313b13318)
Figure 4. Shift rows step algorithm.

Mix Columns Step: This step requires advanced mathematical calculations. To make it easier, the state matrix is multiplied by a matrix, see:
■(2&3&1&1@1&2&3&1@1&1&2&3@3&1&1&1) 	    ×	[state]
