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
#include "cli.h"

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
	
	unsigned char key[32] = ""; // 32 bytes = 256 bits
	// Corrected in second version!! You don't need null terminator for unsigned chars. Array size changed 33 -> 32.
	
	char sourceLocation[256];
	char destination[256];

	system("cls");
    int operation_mode = display_menu();
	
	if (operation_mode == 0 || operation_mode == 2){
		printf("\nEnter the file location: ");
		while(1){   //Asking the user for input until they give a valid response
    		scanf(" %s",sourceLocation);
    		if(filechecker(sourceLocation) == 1 ) break;
    		printf("\nFile not found. Enter a valid directory: ");
		}
		printf("\nEnter the full path to store encrypted data (don't forget to add .txt): ");
		scanf(" %s",destination);	//this does not check if the input is valid, because testing if it was a directory is HARD
	}
	
	else if (operation_mode == 1 || operation_mode == 3){
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
	
	char text_key[33] = "";
    unsigned char binary_key[32];
	printf("\nEnter your key (up to 32 characters): ");

	// TODO make the input key invisible
	while(1){   //Asking the user for input until they give a valid response
		scanf("%32s", text_key);
    	if( (sizeof(key)/sizeof(unsigned char) ) == 32 ) break;
    	printf("\nInvalid key. Enter a valid key: ");
	}
	
	system("cls");
	startTime = clock();
	switch(operation_mode){
		case 0:
			fileencryption(sourceLocation, destination, key);
			break;
		case 1:
			directoryencrypt(sourceLocation, destination, key);
			break;
		case 2:
			filedecryption(sourceLocation, destination, key);
			break;
		case 3:
			directorydecrypt(sourceLocation, destination, key);
			break;
	}
	
	printf("\nTime elapsed: %.2f ms\n", endTime - startTime);

	printf("\nPress any key to exit...");
	_getch();  // Waits for key press
	
	return 0;
}