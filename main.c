/*

References:
https://en.wikipedia.org/wiki/Advanced_Encryption_Standard
https://en.wikipedia.org/wiki/Block_cipher_mode_of_operation#Cipher_Block_Chaining_(CBC)
https://cryptography.fandom.com/wiki/Rijndael_S-box
https://cboard.cprogramming.com/c-programming/87805-[tutorial]-implementing-advanced-encryption-standard.html
https://www.youtube.com/watch?v=bERjYzLqAfw&list=PLKK11LigqitiRH57AbtyJyzsfbNfA8nb-&index=4
https://www.youtube.com/watch?v=5PHMbGr8eOA

*/


#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdio.h>

#include "aes.h"
#include "file_handling.h"
#include "ui.h"

/*int keyChecker(char* key){	//checks if the input key is in valid format. 
	
	for(int i=0;i<32;i++){
		if( isxdigit(key[i]) == 0)
			return 0;	
	}
	
	if(strlen((char*)key)!=32)
		return 0;
		
	return 1;
}*/






int main(){
	
	print_logo();
	
	unsigned char key[33] = ""; //as plaintext
	
	int dirorfile;
	int operationMode;
	char sourceLocation[256];
	char destination[256];
	
	printf("What do you want to encrypt or decrypt? Enter 1 for file, 2 for directory: ");
	while (1) {
    	scanf("%d", &dirorfile);
    	if (dirorfile == 1 || dirorfile == 2) {
        break;
    	}
    	printf("\nEnter a valid option: ");
	}
	
	if(dirorfile==1){
		printf("\nEnter the file location: ");
		while(1){   //Asking the user for input until they give a valid response
    		scanf(" %s",sourceLocation);
    		if(filechecker(sourceLocation) == 1 ) break;
    		printf("\nFile not found. Enter a valid directory: ");
		}
		printf("\nEnter the full path to store decrypted data (please don't forget to add .txt): ");
		scanf(" %s",destination);	//this does not check if the input is valid, because testing if it was a directory is HARD
	}
	
	else if(dirorfile==2){
			printf("\nEnter the directory location: ");
		while(1){   //Asking the user for input until they give a valid response
			scanf(" %s",sourceLocation);
    		if(sourcedirchecker(sourceLocation) == 1 ) break;
    		printf("\nDirectory not found. Enter a valid directory: ");
		}
		printf("\nEnter the directory to store decrypted files: ");
		while(1){   //Asking the user for input until they give a valid response
    	scanf(" %s",destination);
    	if(sourcedirchecker(destination) == 1 ) break;
    	printf("Directory not found. Enter a valid directory:");
		}
	}
	
	printf("\nEnter operation mode: 1 for encrypt / 2 for decrypt: ");
	while(1){   //Asking the user for input until they give a valid response
    	scanf(" %d", &operationMode);
    	if(operationMode == 1 || operationMode == 2) break;
    	printf("\nEnter a valid operation mode, 1 or 2.\n");
	}
	
	printf("\nEnter your 256-bit plain text key: ");
	while(1){   //Asking the user for input until they give a valid response
		scanf("%32s", key);
    	if( (sizeof(key)/sizeof(unsigned char) ) == 33 ) break;
    	printf("\nInvalid key. Enter a valid key: ");
	}
	
	startTime = clock();
	operationdeck(sourceLocation,destination,key,dirorfile,operationMode);
	
	printf("\nTime elapsed: %.2f ms\n", endTime - startTime);
	
	return 0;
}

void operationdeck(char *location, char *destination, unsigned char *key, int dirorfile, int option){
	system("cls");
	if(dirorfile==1){//If choosen option crypt file this function works.
		if(option==1){
			fileencryption(location,destination,key);	
		}
		else if(option==2){
			filedecryption(location,destination,key);
		}
	}
	
	else if(dirorfile==2){//If choosen option crypt directory this function works.
		if(option==1){
			directoryencrypt(location,destination,key);
		}
		else if(option==2){
			directorydecrypt(location,destination,key);
		}
	}
}

