#include <stdio.h>
//Definition of game characteristics in the form of structure
struct game{
    int turn,k,x,y,a,b,u,wallCount1,wallCount2;
    char d,player1[30],player2[30],walls[100][100];
}load;


void saveGame(int turn,char walls[100][100],int k,int x,int y,int a,int b,int u,char d,int wallCount1,int wallCount2,char player1[30],char player2[30]){
    int i,j;
    FILE *file;
    file = fopen("saveGame.dax","wb");
    if(!file){
        printf("Can't open file for saving game...\n");
        return;
    }
    fwrite(&turn,sizeof(int),1,file);//Save and write all entries in binary file
    fwrite(&k,sizeof(int),1,file);
    fwrite(&x,sizeof(int),1,file);
    fwrite(&y,sizeof(int),1,file);
    fwrite(&a,sizeof(int),1,file);
    fwrite(&b,sizeof(int),1,file);
    fwrite(&u,sizeof(int),1,file);
    fwrite(&wallCount1,sizeof(int),1,file);
    fwrite(&wallCount2,sizeof(int),1,file);
    fwrite(&d,sizeof(char),1,file);
    fwrite(player1,sizeof(char),30,file);
    fwrite(player2,sizeof(char),30,file);
    fwrite(walls,sizeof(char),10000,file);
    fclose(file);
    return ;
}


void loadGame(){
    int i,j;
    FILE *file;
    file = fopen("saveGame.dax","rb");
    if(!file){
        printf("Can't open file for loading game...\n");
        return;
    }
    fread(&load.turn,sizeof(int),1,file);//Load and read all binary file information
    fread(&load.k,sizeof(int),1,file);
    fread(&load.x,sizeof(int),1,file);
    fread(&load.y,sizeof(int),1,file);
    fread(&load.a,sizeof(int),1,file);
    fread(&load.b,sizeof(int),1,file);
    fread(&load.u,sizeof(int),1,file);
    fread(&load.wallCount1,sizeof(int),1,file);
    fread(&load.wallCount2,sizeof(int),1,file);
    fread(&load.d,sizeof(char),1,file);
    fread(load.player1,sizeof(char),30,file);
    fread(load.player2,sizeof(char),30,file);
    fread(load.walls,sizeof(char),10000,file);
    fclose(file);
    return ;
}