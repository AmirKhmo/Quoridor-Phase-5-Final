#include <stdio.h>

#define space ' '
#define wall '#'
#define Player1 'A'
#define Player2 'B'
#define Computer 'C'

char board[100][100];

void Board(char walls[][100],int k,int x,int y,int a,int b,int u){ // board preparation
    int i,j;
    char edge = '|';
    for(i=0 ; i<k ; i++){
        for(j=0 ; j<k ; j++){
            if (i==x && j==y) board[i][j]=Player1;
            else if(u==1 && i==a && j==b) board[i][j]=Player2;
            else if(u==2 && i==a && j==b) board[i][j]=Computer;
            else if(walls[i][j]==wall) board[i][j]=wall;
            else if(walls[i][j]==edge) board[i][j]=edge;
            else if(i==0 || i==k-1 || j==0 || j==k-1) board[i][j]=edge;
            else if(i%2==0) board[i][j]=edge;
            else if(j%2==0) board[i][j]=edge;
            else board[i][j]=space;
        }
    }
}


char BoardPrint(int k){
    int i,j,r=1,t=1;
    for(i=0 ; i<=k ; i++){
        for(j=0 ; j<=k ; j++){
            if (j==k&&i%2==1&&i!=k) {
                printf("%d",r);
                r++;
            }
            else if(i==k&&j%2==0&&j<k-1&&j>18){
                printf("%d",t);
                t++;
            }
            else if(i==k&&j%2==0&&j<k-1){
                printf(" %d",t);
                t++;
            }
            else printf("%c",board[i][j]);
        }
        printf("\n");
    }
}