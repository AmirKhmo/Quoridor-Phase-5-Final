#include <stdio.h>
#include "Board.c"

#define space ' '
#define wall '#'
#define Player1 'A'
#define Player2 'B'
#define Computer 'C'

char board[100][100];
int check[100][100];//this global array checkes every part of the board and use it in DFS

int DFS(int c,int d,char walls[][100],int k,int x,int y,int a,int b,int p,int u){// this function tells us that we are allowed to build a wall in a certain location or not
    char edge = '|';
    if(p==1){//It checkes whether we are allowed to construct a vertical wall that does not obstruct 'B' or not.
        int c1=0,c2=0,c3=0;
        if(walls[c][d]==wall)c1=1;
        if(walls[c+1][d]==wall)c2=1;
        if(walls[c+2][d]==wall)c3=1;
        walls[c][d]=wall;
        walls[c+1][d]=wall;
        walls[c+2][d]=wall;
        Board(walls,k,x,y,a,b,u);
        int i,j,s=0;
        i=1;
        for(j=1;j<k;j+=2){
            if(a==i&&b==j) s=1;
        }
        check[a][b]=1;
        if(s==0&&a>2  &&board[a-1][b]!=wall&&check[a-2][b]!=1)  s=DFS(c,d,walls,k,x,y,a-2,b,1,u);
        if(s==0&&b<k-2&&board[a][b+1]!=wall&&check[a][b+2]!=1)  s=DFS(c,d,walls,k,x,y,a,b+2,1,u);
        if(s==0&&b>2  &&board[a][b-1]!=wall&&check[a][b-2]!=1)  s=DFS(c,d,walls,k,x,y,a,b-2,1,u);
        if(s==0&&a<k-2&&board[a+1][b]!=wall&&check[a+2][b]!=1)  s=DFS(c,d,walls,k,x,y,a+2,b,1,u);
        if(c1==0)walls[c][d]=edge;
        if(c2==0)walls[c+1][d]=edge;
        if(c3==0)walls[c+2][d]=edge;
        return s;
    }
    else if(p==2){//It checkes whether we are allowed to construct a horizontal wall that does not obstruct 'B' or not.
        int c1=0,c2=0,c3=0;
        if(walls[c][d]==wall)c1=1;
        if(walls[c][d+1]==wall)c2=1;
        if(walls[c][d+2]==wall)c3=1;
        walls[c][d]=wall;
        walls[c][d+1]=wall;
        walls[c][d+2]=wall;
        Board(walls,k,x,y,a,b,u);
        int i,j,s=0;
        i=1;
        for(j=1;j<k;j+=2){
            if(a==i&&b==j) s=1;
        }
        check[a][b]=1;
        if(s==0&&a>2  &&board[a-1][b]!=wall&&check[a-2][b]!=1)  s=DFS(c,d,walls,k,x,y,a-2,b,2,u);
        if(s==0&&b<k-2&&board[a][b+1]!=wall&&check[a][b+2]!=1)  s=DFS(c,d,walls,k,x,y,a,b+2,2,u);
        if(s==0&&b>2  &&board[a][b-1]!=wall&&check[a][b-2]!=1)  s=DFS(c,d,walls,k,x,y,a,b-2,2,u);
        if(s==0&&a<k-2&&board[a+1][b]!=wall&&check[a+2][b]!=1)  s=DFS(c,d,walls,k,x,y,a+2,b,2,u);
        if(c1==0)walls[c][d]=edge;
        if(c2==0)walls[c][d+1]=edge;
        if(c3==0)walls[c][d+2]=edge;
        return s;
    }
    else if(p==3){//It checkes whether we are allowed to construct a vertical wall that does not obstruct 'A' or not.
        int c1=0,c2=0,c3=0;
        if(walls[c][d]==wall)c1=1;
        if(walls[c+1][d]==wall)c2=1;
        if(walls[c+2][d]==wall)c3=1;
        walls[c][d]=wall;
        walls[c+1][d]=wall;
        walls[c+2][d]=wall;
        Board(walls,k,x,y,a,b,u);
        int i,j,s=0;
        i=k-2;
        for(j=1;j<k;j+=2){
            if(x==i&&y==j) s=1;
        }
        check[x][y]=1;
        if(s==0&&x<k-2&&board[x+1][y]!=wall&&check[x+2][y]!=1)  s=DFS(c,d,walls,k,x+2,y,a,b,3,u);
        if(s==0&&y<k-2&&board[x][y+1]!=wall&&check[x][y+2]!=1)  s=DFS(c,d,walls,k,x,y+2,a,b,3,u);
        if(s==0&&y>2  &&board[x][y-1]!=wall&&check[x][y-2]!=1)  s=DFS(c,d,walls,k,x,y-2,a,b,3,u);
        if(s==0&&x>2  &&board[x-1][y]!=wall&&check[x-2][y]!=1)  s=DFS(c,d,walls,k,x-2,y,a,b,3,u);
        if(c1==0)walls[c][d]=edge;
        if(c2==0)walls[c+1][d]=edge;
        if(c3==0)walls[c+2][d]=edge;
        return s;
    }
    else if(p==4){//It checkes whether we are allowed to construct a horizontal wall that does not obstruct 'A' or not.
        int c1=0,c2=0,c3=0;
        if(walls[c][d]==wall)c1=1;
        if(walls[c][d+1]==wall)c2=1;
        if(walls[c][d+2]==wall)c3=1;
        walls[c][d]=wall;
        walls[c][d+1]=wall;
        walls[c][d+2]=wall;
        Board(walls,k,x,y,a,b,u);
        int i,j,s=0;
        i=k-2;
        for(j=1;j<k;j+=2){
            if(x==i&&y==j) s=1;
        }
        check[x][y]=1;
        if(s==0&&x<k-2&&board[x+1][y]!=wall&&check[x+2][y]!=1)  s=DFS(c,d,walls,k,x+2,y,a,b,4,u);
        if(s==0&&y<k-2&&board[x][y+1]!=wall&&check[x][y+2]!=1)  s=DFS(c,d,walls,k,x,y+2,a,b,4,u);
        if(s==0&&y>2  &&board[x][y-1]!=wall&&check[x][y-2]!=1)  s=DFS(c,d,walls,k,x,y-2,a,b,4,u);
        if(s==0&&x>2  &&board[x-1][y]!=wall&&check[x-2][y]!=1)  s=DFS(c,d,walls,k,x-2,y,a,b,4,u);
        if(c1==0)walls[c][d]=edge;
        if(c2==0)walls[c][d+1]=edge;
        if(c3==0)walls[c][d+2]=edge;
        return s;
    }
}