#include "cli.h"

void print_banner(){
	
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
	
	// TODO center the progress bar dynamically

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

int display_menu(){

    int number_of_options = 4;

    const char* options[] = {"Encrypt a file", "Encrypt a directory", "Decrypt a file", "Decrypt a directory"};

    int selected_option = 0;
    int selector;

    while(1){

        system("cls");
        print_banner();
        printf("Use UP/DOWN arrow keys to navigate. Hit ENTER to select.\n\n");

        for(int i=0; i<number_of_options; i++){
            if(i == selected_option){
                printf(">> %s <<\n", options[i]);
            } else {
                printf("   %s \n", options[i]);
            }
        }

        selector = _getch();

        if(selector == 72){ // up arrow
            selected_option = (selected_option - 1 + number_of_options) % number_of_options;
        }else if(selector == 80){ // down arrow
            selected_option = (selected_option + 1) % number_of_options;
        }else if(selector == 13){ // enter
            break;
        }
    }

    return selected_option;

}
