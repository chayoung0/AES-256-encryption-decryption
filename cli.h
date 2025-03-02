#ifndef CLI_H
#define CLI_H

#include <conio.h>
#include <windows.h>
#include <stdio.h>

void print_banner();
void gotoxy(short x, short y);
void progressBar(int size, int rowcounter);
int display_menu();

#endif