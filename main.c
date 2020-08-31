/*
 * Snack.c
 *
 *  Created on: 2015年10月2日
 *      Author: Eric
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define YMAX 16
#define XMAX 35


char table[XMAX][YMAX];
int x_obj = 0;
int y_obj = 0;
int dir_obj = 1;
int DIFF = 10;
clock_t start, finish;

void init(void);
void sqprint(void);
void xymove(int dir);
void fire(void);
void printtank(void);
void cleartank(void);
void dirchange(int dir);
void rand_box(void);
void if_win(void);


int main(void){
    init();
    while(1){
        /*printf("INPUT: ");
        char dir = getchar();*/
        char dir;
        read(0,&
             dir,1);
        //getchar();
        switch (dir) {
            case 'w':
                xymove(3);
                break;
            case 's':
                xymove(4);
                break;
            case 'a':
                xymove(1);
                break;
            case 'd':
                xymove(2);
                break;
            case 'f':
                fire();
                break;
            case 'i':
                dirchange(1);
                break;
            case 'k':
                dirchange(2);
                break;
            case 'j':
                dirchange(4);
                break;
            case 'l':
                dirchange(3);
                break;
            case 'Q':
                exit(0);
                break;
            default:
                break;
        }
    }
    return 0;
}

void init(void){
    system("clear");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\
■                                         ■\n\
■  ▓▓▓▓▓▓▓    ▓▓▓▓▓    ▓▓    ▓   ▓    ▓   ■\n\
■     ▓      ▓     ▓   ▓ ▓   ▓   ▓  ▓     ■\n\
■     ▓      ▓ ▓▓▓ ▓   ▓  ▓  ▓   ▓▓       ■\n\
■     ▓      ▓     ▓   ▓   ▓ ▓   ▓  ▓     ■\n\
■     ▓      ▓     ▓   ▓    ▓▓   ▓    ▓   ■\n\
■                                         ■\n\
■                        V1.0    BY ERIC  ■\n\
■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("DIFF(DIFF<450):");
    scanf("%d",&DIFF);
    if(DIFF > 450) DIFF = 450;
    system("clear");
    printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\
■                                         ■\n\
■  ▓▓▓▓▓▓▓    ▓▓▓▓▓    ▓▓    ▓   ▓    ▓   ■\n\
■     ▓      ▓     ▓   ▓ ▓   ▓   ▓  ▓     ■\n\
■     ▓      ▓ ▓▓▓ ▓   ▓  ▓  ▓   ▓▓       ■\n\
■     ▓      ▓     ▓   ▓   ▓ ▓   ▓  ▓     ■\n\
■     ▓      ▓     ▓   ▓    ▓▓   ▓    ▓   ■\n\
■                                         ■\n\
■                        V1.0    BY ERIC  ■\n\
■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n");
    printf("ANT KEY TO START...");
    getchar();
    getchar();
    start = clock();
    for (int i = 0; i < XMAX; i++)
        for (int j = 0; j < YMAX; j++)
            table[i][j] = '.';
    for (int i = 0; i < YMAX; i++){
        table[0][i] = '#';
        table[XMAX-1][i] = '#';
    }
    for (int i = 0; i < XMAX; i++){
        table[i][0] = '#';
        table[i][YMAX-1] = '#';
    }
    rand_box();
    x_obj = 2; y_obj = 2;
    dir_obj = 1;
    printtank();
    sqprint();
}
void printtank(void){
    switch (dir_obj) {
        case 1:
            table[x_obj][y_obj-1] = '@';
            table[x_obj][y_obj] = '@';
            table[x_obj+1][y_obj] = '@';
            table[x_obj-1][y_obj] = '@';
            table[x_obj-1][y_obj+1] = '@';
            table[x_obj+1][y_obj+1] = '@';
            break;
        case 2:
            table[x_obj][y_obj+1] = '@';
            table[x_obj][y_obj] = '@';
            table[x_obj+1][y_obj] = '@';
            table[x_obj-1][y_obj] = '@';
            table[x_obj-1][y_obj-1] = '@';
            table[x_obj+1][y_obj-1] = '@';
            break;
        case 3:
            table[x_obj+1][y_obj] = '@';
            table[x_obj][y_obj] = '@';
            table[x_obj][y_obj+1] = '@';
            table[x_obj][y_obj-1] = '@';
            table[x_obj-1][y_obj+1] = '@';
            table[x_obj-1][y_obj-1] = '@';
            break;
        case 4:
            table[x_obj-1][y_obj] = '@';
            table[x_obj][y_obj] = '@';
            table[x_obj][y_obj+1] = '@';
            table[x_obj][y_obj-1] = '@';
            table[x_obj+1][y_obj+1] = '@';
            table[x_obj+1][y_obj-1] = '@';
            break;
        default:
            break;
    }
}
void fire(void){
    if (dir_obj == 1) {
        for (int i = y_obj; i > 3; i--){
            if (table[x_obj][i-3] == '^'){
                table[x_obj][i-3] = '.';
                table[x_obj][i-2] = '.';
                break;
            }
            table[x_obj][i-3] = '*';
            table[x_obj][i-2] = '.';
            sqprint();
            usleep(20000);
        }
        table[x_obj][1] = '.';
        sqprint();
    }
    else if (dir_obj == 2){
        for (int i = y_obj; i < YMAX-4; i++){
            if (table[x_obj][i+3] == '^'){
                table[x_obj][i+3] = '.';
                table[x_obj][i+2] = '.';
                break;
            }
            table[x_obj][i+3] = '*';
            table[x_obj][i+2] = '.';
            sqprint();
            usleep(20000);
        }
        table[x_obj][YMAX-2] = '.';
        sqprint();
    }
    else if (dir_obj == 3)
    {
        for (int i = x_obj; i < XMAX-4; i++){
            if (table[i+3][y_obj] == '^'){
                table[i+3][y_obj] = '.';
                table[i+2][y_obj] = '.';
                break;
            }
            table[i+3][y_obj] = '*';
            table[i+2][y_obj] = '.';
            sqprint();
            usleep(20000);
        }
        table[XMAX-2][y_obj] = '.';
        sqprint();
    }
    else if (dir_obj == 4){
        for (int i = x_obj; i > 3; i--){
            if (table[i-3][y_obj] == '^'){
                table[i-3][y_obj] = '.';
                table[i-2][y_obj] = '.';
                break;
            }
            table[i-3][y_obj] = '*';
            table[i-2][y_obj] = '.';
            sqprint();
            usleep(20000);
        }
         table[1][y_obj] = '.';
        sqprint();
    }
    else{
        
    }
}
void sqprint(void){
    system("clear");
    if_win();
    for (int i = 0; i < YMAX; i++){
        for (int j = 0; j < XMAX; j++){
            if (table[j][i] == '#') printf("■");
            if (table[j][i] == '.') printf(" ");
            if (table[j][i] == '@') printf("▓");
            if (table[j][i] == '^') printf("█");
            if (table[j][i] == '*') printf("◎");
        }
        printf("\n");
    }
}
void cleartank(void){
    switch (dir_obj) {
        case 1:
            table[x_obj][y_obj-1] = '.';
            table[x_obj][y_obj] = '.';
            table[x_obj+1][y_obj] = '.';
            table[x_obj-1][y_obj] = '.';
            table[x_obj-1][y_obj+1] = '.';
            table[x_obj+1][y_obj+1] = '.';
            break;
        case 2:
            table[x_obj][y_obj+1] = '.';
            table[x_obj][y_obj] = '.';
            table[x_obj+1][y_obj] = '.';
            table[x_obj-1][y_obj] = '.';
            table[x_obj-1][y_obj-1] = '.';
            table[x_obj+1][y_obj-1] = '.';
            break;
        case 3:
            table[x_obj+1][y_obj] = '.';
            table[x_obj][y_obj] = '.';
            table[x_obj][y_obj+1] = '.';
            table[x_obj][y_obj-1] = '.';
            table[x_obj-1][y_obj+1] = '.';
            table[x_obj-1][y_obj-1] = '.';
            break;
        case 4:
            table[x_obj-1][y_obj] = '.';
            table[x_obj][y_obj] = '.';
            table[x_obj][y_obj+1] = '.';
            table[x_obj][y_obj-1] = '.';
            table[x_obj+1][y_obj+1] = '.';
            table[x_obj+1][y_obj-1] = '.';
            break;
        default:
            break;
    }
}
void xymove(int dir){
    cleartank();
    int ifnot = 1;
    switch (dir) {
        case 1:
            for (int i = y_obj-1; i <= y_obj+1; i++)
                if(table[x_obj-2][i] == '^') ifnot = 0;
            if ((x_obj>2)&&(ifnot == 1)){
                x_obj-=1;
            }
            break;
        case 2:
            for (int i = y_obj-1; i <= y_obj+1; i++)
                if(table[x_obj+2][i] == '^') ifnot = 0;
            if ((x_obj<XMAX-3)&&(ifnot == 1)){
                x_obj+=1;
            }
            break;
        case 3:
            for (int i = x_obj-1; i <= x_obj+1; i++)
                if(table[i][y_obj-2] == '^') ifnot = 0;
            if ((y_obj>2)&&(ifnot == 1)){
                y_obj-=1;
            }
            break;
        case 4:
            for (int i = x_obj-1; i <= x_obj+1; i++)
                if(table[i][y_obj+2] == '^') ifnot = 0;
            if ((y_obj<YMAX-3)&&(ifnot == 1)){
                y_obj+=1;
            }
            break;
        default:
            break;
    }
    printtank();
    sqprint();
}

void dirchange(int dir){
    cleartank();
    dir_obj = dir;
    printtank();
    sqprint();
}
void rand_box(void){
    srand((unsigned int)time(0));
    for(int i = 0; i < DIFF; i++) table[(rand()%(XMAX-4))+2][(rand()%(YMAX-4))+2] = '^';
}
void if_win(void){
    int ifnot = 1;
    for (int i = 0; i < YMAX; i++){
        for (int j = 0; j < XMAX; j++){
            if (table[j][i] == '^') ifnot = 0;
        }
    }
    finish = clock();
    double times = (double)(finish-start)/1000;
    if (ifnot == 1){
        system("clear");
        printf("■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n\
■                                           ■\n\
■   ▓     ▓     ▓   ▓ ▓ ▓ ▓ ▓   ▓▓      ▓   ■\n\
■    ▓   ▓ ▓   ▓        ▓       ▓ ▓▓    ▓   ■\n\
■    ▓   ▓ ▓   ▓        ▓       ▓   ▓   ▓   ■\n\
■     ▓ ▓   ▓ ▓         ▓       ▓     ▓ ▓   ■\n\
■     ▓▓     ▓▓     ▓ ▓ ▓ ▓ ▓   ▓      ▓▓   ■\n\
■                                           ■\n\
                   TIME IN TOTAL: %3.2f s    \n\
■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■\n",times);
        printf("ANY KEY TO END...");
        getchar();
        getchar();
        exit(0);
    }
}