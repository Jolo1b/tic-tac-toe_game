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

void gameOver(){
    if(ws.y == -1){
        for(short i = 0;i<3;i++){
            setLocation(ws.x, i);
            printf("\x1b[31m%c\x1b[0m", ws.player);    
        }
    } else if(ws.x == -1){
        for(short i = 0;i<3;i++){
            setLocation(i, ws.y);
            printf("\x1b[31m%c\x1b[0m", ws.player);   
        }
    }
}

int main(){

    printf("\x1b[?47h\x1b[?1049h");
    printf("\x1b[1;1H");
    
    drowGrid();
    printf("\x1b[12;1H=======================\n");
    printf("\x1b[0mIt's player \x1b[33m%c\x1b[0m turn.", player);
    setLocation(x, y);

    while(1){
        ch = getch();
        if(ch == 224){
            printf("\x1b[14;1H\x1b[2K");
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
            if(grid[y][x] == ' '){
                grid[y][x] = player;
                if(player == 'O') {
                    printf("\x1b[36m%c\b\x1b[0m", player);
                    player = 'X';
                } else {
                    printf("\x1b[34m%c\b\x1b[0m", player);
                    player = 'O';
                }
             
                for(short i = 0;i<3;i++){
                    if(grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]){
                        ws.x = -1;
                        ws.y = i;
                        ws.player = grid[i][0];
                        gameOver();
                        printf("\x1b[13;1H\x1b[2Kplayer \x1b[32m%c\x1b[0m win!", grid[i][0]);
                        getch();
                        printf("\x1b[?1049l\x1b[?47l");
                        return 0;
                    }
                }

                for(short i = 0;i<3;i++){
                    if(grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]){
                        ws.y = -1;
                        ws.x = i;
                        ws.player = grid[0][i];
                        gameOver();
                        printf("\x1b[13;1H\x1b[2Kplayer \x1b[32m%c\x1b[0m win!", grid[0][i]);
                        getch();
                        printf("\x1b[?1049l\x1b[?47l");
                        return 0;
                    }
                }

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