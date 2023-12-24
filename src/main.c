#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

void drowGrid(){
    printf("\x1b[1;1H");
    printf("       |       |       \n");
    printf("       |       |       \n");
    printf("       |       |       \n");
    printf("-------+-------+-------\n");
    printf("       |       |       \n");
    printf("       |       |       \n");
    printf("       |       |       \n");
    printf("-------+-------+-------\n");
    printf("       |       |       \n");
    printf("       |       |       \n");
    printf("       |       |       \n");
}

int setLocation(short x, short y){
    if((y <= 2 && y >= 0) && (x <= 2 && x >= 0)) {

        x = (8 * x) + 4;
        y = (4 * y) + 2;
        
        printf("\x1b[%d;%dH", y, x);
        return 0;
    } else return 1;
}

int main(){

    char player = 'O';
    short ch;
    short x = 0;
    short y = 0;

    printf("\x1b[?47h");
    printf("\x1b[1;1H");
    
    drowGrid();
    printf("\x1b[12;1H=======================\n");
    printf("na rade je hrac \x1b[33m%c\x1b[0m", player);
    printf("\x1b[32m");
    setLocation(x, y);

    while(1){
        ch = getch();
        if(ch == 224){
            ch = getch();

            if(1 == (y <= 2 && y >= 0) && (x <= 2 && x >= 0)) {
                if(ch == 72) y--;
                else if(ch == 80) y++;
                else if(ch == 77) x++;
                else x--;

                if(y > 2) y = 2;
                if(y < 0) y = 0;
                if(x > 2) x = 2;
                if(x < 0) x = 0;

                setLocation(x, y);
            } 
            
        } else if(ch == 13) {
            if(player == 'O') {
                printf("\x1b[36m%c\b\x1b[0m", player);
                player = 'X';
            } else {
                printf("\x1b[34m%c\b\x1b[0m", player);
                player = 'O';
            }
            printf("\x1b[12;1H=======================\n");
            printf("\x1b[0mIt's player \x1b[33m%c\x1b[0m turn.", player);
            setLocation(x, y);
        } else if(ch == 27){
            printf("\x1b[?47l");
            return 0;
        } 
    } 

    printf("\x1b[?47l");
    return 0;

}