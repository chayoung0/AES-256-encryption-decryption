#include "ui.h"



void print_logo(){
	
	printf("                ___      _             \n");
	printf("  _______ _ __ / _ \\  __| | __ _ _   _ \n");
	printf(" |_  / _ \\ '__| | | |/ _` |/ _` | | | |\n");
	printf("  / /  __/ |  | |_| | (_| | (_| | |_| |\n");
	printf(" /___\\___|_|   \\___/ \\__,_|\\__,_|\\__, |\n");
	printf("                                 |___/ \n\n");

}

void gotoxy(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void progressBar(int size, int rowcounter){
	//print_logo();
	float percentage = (rowcounter*1600/size);
	
	if((rowcounter+1)==(size/16))
		percentage = 100;
	
	gotoxy(45,8);
	printf("status: %%%.f complete.\n", percentage);
	
	gotoxy(30+(percentage/2),10);
	int i;
	for(i=(percentage/2); i<50; i++){
		printf("%c", 177);
	}
	
	gotoxy(30,10);
	for(i=0; i<(percentage/2); i++){
		printf("%c", 178);
	}
	gotoxy(30,12);
}
