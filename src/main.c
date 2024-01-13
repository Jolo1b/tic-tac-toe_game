#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <pthread.h>
#include "window.h"

void *drawGrid(){
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

        // location calculation
        x = (8 * x) + 4;
        y = (4 * y) + 2;
        
        printf("\x1b[%d;%dH", y, x);
        return 0;
    } else return 1;
}

// the structure in which the data about the winner will be preserved
struct WinnerScore {
    short x;
    short y;
    char player;
};

struct WinnerScore ws;
char grid[3][3] = {
    {' ',' ',' '},
    {' ',' ',' '},
    {' ',' ',' '}
};

char player = 'O';
short ch;
short x = 0;
short y = 0;
pthread_t th1;

void gameOver(short endGame){
    // rendering the result
    if(ws.y == -1 || ws.x == -1){
        for(short i = 0;i<3;i++){
            if(ws.x == -1) setLocation(i, ws.y);
            else setLocation(ws.x, i); 
            printf("\x1b[31m%c\x1b[0m", ws.player);    
        }
    } else if(ws.x == -2){
        for(short i = 0;i<3;i++){
            setLocation(i, i);
            printf("\x1b[31m%c\x1b[0m", ws.player);    
        }
    } else if(ws.y == -2){
        for(short i = 2, j = 0;i>-1&&j<3;i--,j++){
            setLocation(j, i);
            printf("\x1b[31m%c\x1b[0m", ws.player);    
        }
    }

    printf("\x1b[13;1H\x1b[2Kplayer \x1b[32m%c\x1b[0m win!", ws.player);
    getc(stdin);

    if(endGame){
        printf("\x1b[?1049l\x1b[?47l");
        exit(0);
    }
}

void *checkScore(){
    // it is checked whether someone gave a winning combination
    for(short i = 0;i<3;i++){
        if(grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]){
            ws.x = -1;
            ws.y = i;
            ws.player = grid[i][0];
            gameOver(1);
        } else if(grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]){
            ws.y = -1;
            ws.x = i;
            ws.player = grid[0][i];
            gameOver(1);
        }
    }

    if(grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]){
        ws.x = -2;
        ws.player = grid[0][0];
        gameOver(1);
    } else if(grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]){
        ws.y = -2;
        ws.player = grid[0][2];
        gameOver(1);
    }
}


int main(){

    char *title = "tic-tac-toe";
    wTitle(title);

    printf("\x1b[?47h\x1b[?1049h");
    printf("\x1b[1;1H");
    
    drawGrid();
    printf("\x1b[12;1H=======================\n");
    printf("\x1b[0mIt's player \x1b[33m%c\x1b[0m turn.", player);
    setLocation(x, y);


    while(1){
        ch = getch();
        // 224 = arrow
        if(ch == 224){
            printf("\x1b[14;1H\x1b[2K");
            ch = getch();

            if(1 == (y <= 2 && y >= 0) && (x <= 2 && x >= 0)) {
                /*
                  72 = arrow up
                  80 = arrow down
                  77 = arrow right
                */
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
            if(grid[y][x] == ' '){
                grid[y][x] = player;
                if(player == 'O') {
                    printf("\x1b[36m%c\b\x1b[0m", player);
                    player = 'X';
                } else {
                    printf("\x1b[34m%c\b\x1b[0m", player);
                    player = 'O';
                }
             
                pthread_create(&th1, NULL, checkScore, NULL);

            } else {
                printf("\x1b[14;1H\x1b[31myou cannot occupy an occupied square!\x1b[0m");
            }

            printf("\x1b[12;1H=======================\n");
            printf("\x1b[0mIt's player \x1b[33m%c\x1b[0m turn.", player);
            setLocation(x, y);
        } else if(ch == 27){
            printf("\x1b[?1049l\x1b[?47l");
            return 0;
        } 
    } 

    printf("\x1b[?1049h");
    return 0;

}