#include "file_handling.h"
#include "aes.h"




double startTime, endTime;

int directoryChecker(char *location){
	DIR* directory;
	directory=opendir(location);
	if(directory==NULL){
		return 0;
	}
	else{
		return 1;
	}
}

int sourcedirchecker(char *location){
	
	DIR* dirptr;
	dirptr=opendir(location);
	
	if(dirptr==NULL){
		return 0;
	}
	else{
		return 1;
	}
}

int filechecker(char *location){
	
	FILE *fileptr;
	fileptr=fopen(location,"r");
	
	if(fileptr==NULL){
		return 0;
	}
	else{
		return 1;
	}
}

//Reads filenames in directory to encrypt files.
void directoryencrypt(char *location, char *destination,unsigned char *key){
	
	struct dirent *fnameptr;
	
	char fullsourcelocation[512];
	char fulldestlocation[512];
	
	DIR *locptr,*destptr;
	
	locptr=opendir(location);
	destptr=opendir(destination);
	
	int i=0;
	while((fnameptr=readdir(locptr))!= NULL){
		if(i<2){
			++i;
		}
		else{
		locationgenerator(location,destination,fnameptr->d_name,fullsourcelocation,fulldestlocation,1);
		
		fileencryption(fullsourcelocation,fulldestlocation,key);	
		}
	}
	
}

//encrypt files.
void fileencryption(char *location, char *destination, unsigned char *key){
	
	int round=0;
	//unsigned char iv[16];
	
	FILE *loc,*dest;
	
	loc=fopen(location,"r");
	dest=fopen(destination,"w");
	
	if(loc==NULL){
		printf("CAN NOT OPEN THIS FILE: %s\n",location);
	}
	
	unsigned char padd='*';
	
	int padding;   
 	fseek(loc, 0, SEEK_END);   
 	int datalenght = ftell(loc); 
 	rewind(loc);
 	
 	padding=16-(datalenght%16);
	int size=datalenght+padding;
	
 	unsigned char textToEncrypt[size+17];
	unsigned char textPortion[17];

 	fread(&textToEncrypt,sizeof(unsigned char),size,loc);
	
	int i;
	for(i=0;i<padding;i++){
		textToEncrypt[datalenght+i]=padd;	
	}
	
	int rowcounter=0;
	int j;
	for(i=1;i<=size/16;i++){
		for(j=0 ; j<16 ; j++){
			textPortion[j]=textToEncrypt[j+(16*rowcounter)];
		}
			textPortion[16]='\0';
			encrypt(textPortion,key);
		round++;
		for(j=0 ; j<16 ; j++){
			textToEncrypt[j+(16*rowcounter)]=textPortion[j];
		}
		rowcounter++;
		progressBar(size,rowcounter);
	}
	/*
	for(int i=1;i<padding;i++){
		textToEncrypt[datalenght+i]='\0';
	}*/
	/*
	for (int i=0;i<16;i++){
		textToEncrypt[size+i]=iv[i];
	}
	*/
	rowcounter=0;
	round=0;
	
	
	fwrite(textToEncrypt,sizeof(unsigned char),size,dest);
	rewind (loc);
	fclose(dest);
	fclose(loc);
	endTime = clock();

}

//Reads directory file names sends file names to locationgenerator and sends location to decryption.
void directorydecrypt(char *location, char *destination,unsigned char *key){
	
	struct dirent *fnameptr;
	
	char fullsourcelocation[512];
	char fulldestlocation[512];
	
	DIR *locptr,*destptr;
	
	locptr=opendir(location);
	destptr=opendir(destination);
	
	int i=0;
	while((fnameptr=readdir(locptr))!= NULL){//reads filenames in directory.
		if(i<2){//Firs two filenames are ".", ".." as defoult.To skip this part i used if.
			++i;
		}
		else{
		locationgenerator(location,destination,fnameptr->d_name,fullsourcelocation,fulldestlocation,2);
		
		filedecryption(fullsourcelocation,fulldestlocation,key);	
		}
	}
	
}

//Decrypt files.
void filedecryption(char *location, char *destination, unsigned char *key){
	
	//unsigned char iv[16];	
	
	FILE *loc,*dest;
	
	loc=fopen(location,"r");
	dest=fopen(destination,"w");
	
	if(loc==NULL){
		printf("CAN NOT OPEN THIS FILE: %s\n",location);
	}
	unsigned char padd='*';
	int datalength=0;
	int padding;   
 	fseek(loc, 0, SEEK_END);   
 	datalength = ftell(loc); 
 	rewind (loc);
	padding=16-(datalength%16);
	int size=datalength+padding;
	
	unsigned char textToDecrypt[size+1];
	unsigned char textPortion[size+1];
	
	fread(&textToDecrypt,sizeof(unsigned char),size,loc);
	
	/*
	for(int i=15;i>=0;i--){//reading iv
		iv[15-i]=ctext[datalenght-i-1];
	}
	*/
	
	int i, j;
	for(i=0;i<padding;i++){//Adds padding to files.
		textToDecrypt[datalength+i]=padd;	
	}
	
	int rowcounter=0;
	for(i=1;i<=size/16;i++){
		
		for(j=0 ; j<16 ; j++){
			textPortion[j]=textToDecrypt[j+(16*rowcounter)];
		}
		
		decrypt(textPortion,key);
		
		for(j=0 ; j<16 ; j++){
			textToDecrypt[j+(16*rowcounter)]=textPortion[j];
		}
		rowcounter++;
		progressBar(size,rowcounter);
	}
	rowcounter=0;
	//size=size-padding;
	fwrite(textToDecrypt,sizeof(unsigned char),datalength,dest);//writes decrypted data to files.
	fclose(dest);
	fclose(loc);
	endTime = clock();
}

//creates locations suitable to read for "fopen" with directory names.
void locationgenerator(char *location, char *destination, char *filenm, char *source, char *dest, int operationMode){
	
	char space='\\';
	char encrypted_extension[]="encrypted_";
	char decrypted_extension[]="decrypted_";
	
	strcpy(source,location);
	strncat(source,&space,1);
	strncat(source,filenm,256);
	
	strcpy(dest,destination);
	strncat(dest,&space,1);
	
	if(operationMode == 1)
		strncat(dest,encrypted_extension,10);
	else
		strncat(dest,decrypted_extension,10);
	
	strncat(dest,filenm,256);
}
