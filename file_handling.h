#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H


#include <time.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <windows.h>

extern double startTime, endTime;

void fileencryption(char *location, char *destination, unsigned char *key);
void filedecryption(char *location, char *destination, unsigned char *key);
void directoryencrypt(char *location, char *destination,unsigned char *key);
void directorydecrypt(char *location, char *destination,unsigned char *key);
void locationgenerator(char *location, char *destination, char *filenm, char *sourceloc, char *destloc, int operationMode);
void operationdeck(char *location, char *destination,unsigned char *key, int dirorfile, int option);
int sourcedirchecker(char *location);
int filechecker(char *location);
int directoryChecker(char *location);

void cryptionloop(char* sourceLocation, char* destinationLocation, int operationMode, char* key);
int dirfilenumber(char*location);
void findfilename(char*location,char *filename,int number);
void fileLocationgenerator(char *location, char *filename, char *fileloc);
void filetester(char*fileloc);
int stringlenght(char *fileloc);
int stringlenght2(char *fileloc);
void cryptdatagenerator(unsigned char *text,char* location,int forpadd);
void ivadder(unsigned char *iv,unsigned char *fulltext,int forlenght);
void filewriter(unsigned char *text,char *dest, char *name,int forlenght);
void ivsub(unsigned char*text,unsigned char *iv,int forlenght);

#endif