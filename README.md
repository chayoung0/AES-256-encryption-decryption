# AES-256-encryption-decryption
### Implementation of AES 256 encryption algorithm with C. 

#### Building and Running
First, the program will ask for the type of the target file(s). Enter "1" if you want to encrypt a single .txt file, or enter "2" if you want to encrypt a folder.

Next, it will prompt you to enter the source and destination directories. For folders, please enter the format as "C:\Users\Desktop". For files, remember to include the .txt file extension. Spaces are not accepted.

After that, the program will ask for the operating mode: enter "1" for encryption or "2" for decryption.

Finally, it will prompt you to enter the encryption/decryption key. The key should be in plain text format.

Please note that this program was developed in the Dev-C++ environment.

#### Implementation

AES-256 uses a 256-bit key to encrypt a 128-bit text. If the text is larger than 128 bits, it is divided into 128-bit pieces, and each piece is encrypted one by one. The encryption process consists of 14 rounds.

The first step involves generating 14 new keys based on the initial key. This is known as the Key Expansion step, where each round uses a different 128-bit key. The generated keys are stored in a 240-byte array.

In CBC mode, a 128-bit random initialization vector (IV) is generated. This IV is XORed with the text, which is also 128-bit.


![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/fecc1b4e-7d15-491f-858d-34b57717ddd0)

Figure 1. Combining the plain text with IV

In the initial round, the state is XORed with the round key, which corresponds to the first 16 bytes of the expanded key array.
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/9505379f-6c51-422e-8015-fe6cfbfd6566)

Figure 2. Add Round Key step algorithm

#### Round Steps
##### Sub Bytes Step: Each element of the state array is replaced by the corresponding value in the Rijndael S-box (S is for substitution). For example, if the value in state[i] is equal to 0x2A, the corresponding value in the S-box is found at the 2nd row and the 10th column, which is 0xE5.

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/f3d4b9ae-4988-4662-a247-1d0a350a6b4e)

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/481f1f59-1122-4c9d-802b-293c170119f7)

Figure 3. Replace state’s elements using Sbox.

##### Shift Rows Step: The second, third, and fourth rows are shifted to the right by 1, 2, and 3 positions, respectively. The first row remains unchanged.

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/fb5b1897-9d21-4de7-b858-885313b13318)

Figure 4. Shift rows step algorithm.

##### Mix Columns Step: This step involves advanced mathematical calculations. To simplify it, the state matrix is multiplied by a matrix as follows:

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/a7034f7d-441b-4291-8c54-2e9f64b3cc03)

In this multiplication, dot products are calculated in a different way. Normally, each element would be multiplied by the corresponding element, then these products would be added, resulting the dot product. Here, to find the multiplication with for example, 2, we look at the corresponding lookup table, called mul2. The lookup table is referenced to calculate each product, then these products are XORed rather than summed.

#### Rounds
These steps are repeated for 13 rounds, starting with the Sub Bytes step:

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/dc1ff4c8-9ab2-4e01-817a-88c3984f49a8)

Figure 5. Illustration of the main rounds of encryption.

The final round is a little different. Final round does not have Mix Colums step. 
![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/59a4f032-92e1-4947-9324-c0e4b7dcbe4f)

Figure 6. Steps of the final round.

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/d9e977ad-bdeb-4f3b-862a-2047799b5137)

Figure 7. All steps of the AES encryption algorithm

For decryption, the steps are almost the same but in reversed order. Firstly, the same key is expanded. The Add Round Key step, which was the last step in the encryption process, becomes the first step in decryption. It should be noted that for the last Add Round Key step, the last 16 bytes of the Expanded Key Array are used. The Expanded Key Array should be treated as if it consists of 15 keys, and we start using the keys from the last one.

In the Shift Rows step, where the state matrix's rows were shifted to the right during encryption, the inverse version, Inv Shift Rows, shifts the rows to the left using the same offsets.

In the Inverse Mix Columns step, the state is multiplied by the matrix:

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/4446b294-8596-4a79-b808-13043f18eb69)

with the help of multiplication lookup tables.

In the Inverse Substitute Bytes step, the state's elements are substituted in the same manner as before, but using the reversed version of the Rijndael Lookup Table, called R_Sbox.

Lastly, the state is combined with the IV.

![image](https://github.com/chayoung0/AES-256-encryption-decryption/assets/79144571/d2da1b3d-a0f2-4012-9e82-0934c70e29fa)

Figure 8. All steps of AES decryption



### Discussion
This program assumes that the key is entered in plain text form. It works fine when the key is in plain text, and it can encrypt and retrieve the encrypted file by decrypting it. However, if the key is entered in hexadecimal form, the encrypted text may not match with online AES tools. Therefore, it is recommended to use plain text keys.

The program may leave padding at the end of the text.
