#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#include "rand.c"
#include "DFS.c"
#include "sys.c"
#include "Saveandload.c"
//when player1 should enter sth , Board's color will be yellow
//when player2 should enter sth , Board's color will be blue
//when they should enter sth that related to both of them, Board's color will be white

int main(){
	int n,k;
	int i,j;
	int h,v;//h&v are two variavbles which scan every wall's coordinates
	int p,q,random;
	int ascii,sw=0;//if player chose to build wall , sw will change to 1
	int x,y,a,b;// Variables that  show coordinates of player1 and player2's character
	int xx,yy,aa,bb;//copy of original variables
	int wallCount,wallCount1,wallCount2;//count of the walls for each player
	int e,t,u,randbox;
	char d,r,turn=1;
	char player1[30],player2[30],Bug[30];//each player's nickname
	char walls[100][100];// an array to put # as wall and match it with board
	char wallDirection;// vertical or horizontal
	char wallcount[20],nn[20],hh[20],vv[20];
	
	do{
		printf("If you want to play a new game enter 'N'...\nelse if you want to continue the pervious game enter 'P'...");
		scanf("%c",&r);
		clearScrean();
	}while(r!='n'&&r!='N'&&r!='p'&&r!='P');
	
	if(r=='n'||r=='N'){
		do{
			printf("If you want to play with computer enter 'C'...\nelse if you want to play with your friend enter 'F'... ");
			scanf("%c",&d);
			clearScrean();
		}while(d!='c'&&d!='C'&&d!='f'&&d!='F');
	}
	else {
		n=(k-1)/2;
		loadGame();
		turn=load.turn;
		k=load.k;
		x=load.x;
		y=load.y;
		a=load.a;
		b=load.b;
		u=load.u;
		wallCount1=load.wallCount1;
		wallCount2=load.wallCount2;
		d=load.d;
		for(i=0;i<30;i++){
		player1[i]=load.player1[i];
		}
		for(i=0;i<30;i++){
			player2[i]=load.player2[i];
		}
		for(i=0;i<100;i++){
			for(j=0;j<100;j++){
				walls[i][j]=load.walls[i][j];
			}
		}
	}
	if(d=='F'||d=='f'){
		u=1;//used in DFS function for recognizing the way of player2 or computer
		if(r=='n'||r=='N'){
			do{//receive 'n' as dimention of the board which will be n*n
				sleep(500);
				printf("Please enter dimension of the board : ");
				scanf("%s",nn);
				n=0;
				for(i=0;nn[i];i++){
					n=n*10+(nn[i]-48);
				}
				clearScrean();
			}while(n<4 || n>25);
			k=2*n+1;
		
			if(n%2==0){x=1 , y=n-1;}// determining where should player 1&2's characters locate
			else { x=1 , y=n;}
			if(n%2==0){	a=k-2 , b=n-1;}
			else { a=k-2 , b=n;}
		
		//when player1 should enter sth , Board's color will be yellow
		//when player2 should enter sth , Board's color will be blue
		
			//scanning the nickname of player1
			sleep(400);
			setTextColor(6,0);
			gets(Bug);
			printf("<< player1 >> \n");// board's printing
			printf("Remained walls: \n\n");
			Board(walls,k,x,y,a,b,u);
			BoardPrint(k);
			printf("\nRemained walls: \n");
			printf("<< player2 >> \n");// end of board's printing
			printf("\nPlayer1...! enter a nickname for yourself : ");
			gets(player1);
			clearScrean();
		
			//scanning the nickname of player2
			sleep(400);
			setTextColor(11,0);
			printf("<< %s >>\n",player1);// board's printing
			printf("Remained walls: \n\n");
			Board(walls,k,x,y,a,b,u);
			BoardPrint(k);
			printf("\nRemained walls: \n");
			printf("<< player2 >> \n");// end of board's printing
			printf("\nPlayer2...! enter a nickname for yourself : ");
			gets(player2);
			clearScrean();
		
			do{//scanning the number of their walls
				wallCount=0;
				clearScrean();
				sleep(400);
				setTextColor(15,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: \n\n");
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: \n");
				printf("<< %s >>\n",player2);// end of board's printing
				printf("\nHow many walls would you like to have? ");
				scanf("%s",wallcount);
				wallCount=0;
				for(i=0;wallcount[i];i++){
					wallCount=wallCount*10+(wallcount[i]-48);
				}
				wallCount1=wallCount;
				wallCount2=wallCount;
				clearScrean();
			}while(wallCount>=n*n/4);// we use do...while because wallCount for each player shouldn't be more than n*n/4
		}
	
		do{//game started , Until someone reaches the other side, this loop will repeat
			if(turn==1){
				clearScrean();
				sleep(400);
				setTextColor(6,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: %d\n\n",wallCount1);
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: %d\n",wallCount2);
				printf("<< %s >>\n",player2);// end of board's printing
				printf("\nYour magic box in this turn is... ");
				sleep(800);
				srand(time(0));
				randbox=randBox();
				if(randbox==1){
					printf("Oops! All walls of the game will be erased!");
					for(e=0;e<100;e++){
						for(t=0;t<100;t++){
							walls[e][t]=space;
						}
					}
				}
				else if(randbox==2){
					printf("Oops! You lost two walls!");
					wallCount1-=2;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==3){
					printf("Oops! You lost three walls!");
					wallCount1-=3;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==4){
					printf("Oops! You lost five walls!");
					wallCount1-=5;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==5){
					printf("Oops! You are blocked for one turn!");
					turn=0;
				}
				else if(randbox==6){
					printf("Wow! You earned two walls!");
					wallCount1+=2;
				}
				else if(randbox==7){
					printf("Wow! You earned three walls!");
					wallCount1+=3;
				}
				else if(randbox==8){
					printf("Wow! You earned five walls!");
					wallCount1+=5;
				}
				else if(randbox==9){
					printf("Wow! You earned one of your friend's walls!");
					wallCount1++ , wallCount2--;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==10){
					printf("Wow! You earned two of your friend's walls!");
					wallCount1+=2 , wallCount2-=2;
					if(wallCount2<0) wallCount2=0;
				}
				saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
				sleep(2500);
				if(turn==1){
					do{//player1's next move...
						turn=0;
						xx=x , yy=y;
						clearScrean();
						sleep(400);
						setTextColor(6,0);
						printf("<< %s >>\n",player1);// board's printing
						printf("Remained walls: %d\n\n",wallCount1);
						Board(walls,k,x,y,a,b,u);
						BoardPrint(k);
						printf("\nRemained walls: %d\n",wallCount2);
						printf("<< %s >>\n",player2);// end of board's printing
						printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",player1);//asking the player1's next move...
			   			printf("%c",getch());
						ascii=getch();//scanning the player1's next move...
						if(ascii==80 && a==xx+2 && yy==b && board[a+1][b]!=wall) xx+=4;// ASCII code of up & down & left & right button
						else if(ascii==80) xx+=2;
						else if(ascii==75 && b==yy-2 && xx==a && board[a][b-1]!=wall) yy-=4;
						else if(ascii==75) yy-=2;
						else if(ascii==77 && b==yy+2 && xx==a && board[a][b+1]!=wall) yy+=4;
						else if(ascii==77) yy+=2;
						else if(ascii==72 && a==xx-2 && yy==b && board[a-1][b]!=wall) xx-=4;
						else if(ascii==72) xx-=2;
						else{//player chose to build a wall
							if(wallCount1>0){
								do{
			    					sw=1;
									clearScrean();
									setTextColor(6,0);
									printf("<< %s >>\n",player1);// board's printing
									printf("Remained walls: %d\n\n",wallCount1);
									Board(walls,k,x,y,a,b,u);
									BoardPrint(k);
									printf("\nRemained walls: %d\n",wallCount2);
									printf("<< %s >>\n",player2);// end of board's printing
									printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
									scanf("%c",&wallDirection);
									clearScrean();
								}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters
			
								if(wallDirection=='v' || wallDirection=='V'){
									do{
										do{
											setTextColor(6,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< %s >>\n",player2);// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h-1,2*v,walls,k,x,y,a,b,3,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h-1,2*v,walls,k,x,y,a,b,1,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h-1;
									v=2*v;
									walls[h][v]=wall;
									walls[h+1][v]=wall;
									walls[h+2][v]=wall;
									wallCount1--;
								}
			
								if(wallDirection=='h' || wallDirection=='H'){
									do{
										do{
											setTextColor(6,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< %s >>\n",player2);// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
			      						for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h,2*v-1,walls,k,x,y,a,b,4,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h,2*v-1,walls,k,x,y,a,b,2,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h;
									v=2*v-1;
									walls[h][v]=wall;
									walls[h][v+1]=wall;
									walls[h][v+2]=wall;
									wallCount1--;
								}
								printf("<< %s >>\n",player1);// board's printing
								printf("Remained walls: %d\n\n",wallCount1);
								Board(walls,k,x,y,a,b,u);
								BoardPrint(k);
								printf("\nRemained walls: %d\n",wallCount2);
								printf("<< %s >>\n",player2);// end of board's printing
							}
							else{
								clearScrean();
								sleep(400);
								printf("<< %s >>\n",player1);// board's printing
								printf("Remained walls: %d\n\n",wallCount1);
								Board(walls,k,x,y,a,b,u);
								BoardPrint(k);
								printf("\nRemained walls: %d\n",wallCount2);
								printf("<< %s >>\n",player2);// end of board's printing
								printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
								scanf("%d",&p);
							}
						}
					}while((board[xx][yy]!=space || board[(x+xx)/2][(yy+y)/2]==wall) && sw==0);
					sw=0;
					x=xx , y=yy;
					saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
					if(x==k-2) break;
				}
			}
			else if (turn==0){
				clearScrean();
				sleep(400);
				setTextColor(11,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: %d\n\n",wallCount1);
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: %d\n",wallCount2);
				printf("<< %s >>\n",player2);// end of board's printing
				printf("\nYour magic box in this turn is... ");
				sleep(1000);
				srand(time(0));
				randbox=randBox();
				if(randbox==1){
					printf("Oops! All walls of the game will be erased!");
					for(e=0;e<100;e++){
						for(t=0;t<100;t++){
							walls[e][t]=space;
						}
					}
				}
				else if(randbox==2){
					printf("Oops! You lost two walls!");
					wallCount2-=2;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==3){
					printf("Oops! You lost three walls!");
					wallCount2-=3;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==4){
					printf("Oops! You lost five walls!");
					wallCount2-=5;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==5){
					printf("Oops! You are blocked for one turn!");
					turn=1;
				}
				else if(randbox==6){
					printf("Wow! You earned two walls!");
					wallCount2+=2;
				}
				else if(randbox==7){
					printf("Wow! You earned three walls!");
					wallCount2+=3;
				}
				else if(randbox==8){
					printf("Wow! You earned five walls!");
					wallCount2+=5;
				}
				else if(randbox==9){
					printf("Wow! You earned one of your friend's walls!");
					wallCount2++ , wallCount1--;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==10){
					printf("Wow! You earned two of your friend's walls!");
					wallCount2+=2 , wallCount1-=2;
					if(wallCount1<0) wallCount1=0;
				}
				saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
				sleep(2500);
				if(turn==0){
					do{//player2's next move...
						turn=1;
						aa=a , bb=b;
						clearScrean();
						sleep(400);
						setTextColor(11,0);
						printf("<< %s >>\n",player1);// board's printing
						printf("Remained walls: %d\n\n",wallCount1);
						Board(walls,k,x,y,a,b,u);
						BoardPrint(k);
						printf("\nRemained walls: %d\n",wallCount2);
						printf("<< %s >>\n",player2);// end of board's printing
						printf("\n %s if you want to build a wall enter any button\n else move 'B' character...! ",player2);//asking the player1's next move...
						printf("%c",getch());
						ascii=getch();//scanning the player2's next move...
						if(ascii==80 && x==aa+2 && bb==y) aa+=4;// ASCII code of up & down & left & right button
						else if(ascii==80) aa+=2;
						else if(ascii==75 && bb==y-2 && aa==x) bb-=4;
						else if(ascii==75) bb-=2;
						else if(ascii==77 && y==bb+2 && x==aa) bb+=4;
						else if(ascii==77) bb+=2;
						else if(ascii==72 && x==aa-2 && y==bb) aa-=4;
						else if(ascii==72) aa-=2;
						else{//player chose to build a wall
							if(wallCount2>0){
								do{
			    					sw=1;
									clearScrean();
									setTextColor(11,0);
									printf("<< %s >>\n",player1);// board's printing
									printf("Remained walls: %d\n\n",wallCount1);
									Board(walls,k,x,y,a,b,u);
									BoardPrint(k);
									printf("\nRemained walls: %d\n",wallCount2);
									printf("<< %s >>\n",player2);// end of board's printing
									printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
									scanf("%c",&wallDirection);
									clearScrean();
								}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters
			
								if(wallDirection=='v' || wallDirection=='V'){
									do{
										do{
											setTextColor(11,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< %s >>\n",player2);// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h-1,2*v,walls,k,x,y,a,b,3,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h-1,2*v,walls,k,x,y,a,b,1,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h-1;
									v=2*v;
									walls[h][v]=wall;
									walls[h+1][v]=wall;
									walls[h+2][v]=wall;
									wallCount2--;
								}
			
								if(wallDirection=='h' || wallDirection=='H'){
									do{
										do{
											setTextColor(11,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< %s >>\n",player2);// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h,2*v-1,walls,k,x,y,a,b,4,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h,2*v-1,walls,k,x,y,a,b,2,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h;
									v=2*v-1;
									walls[h][v]=wall;
									walls[h][v+1]=wall;
									walls[h][v+2]=wall;
									wallCount2--;
								}
								printf("<< %s >>\n",player1);// board's printing
								printf("Remained walls: %d\n\n",wallCount1);
								Board(walls,k,x,y,a,b,u);
								BoardPrint(k);
								printf("\nRemained walls: %d\n",wallCount2);
								printf("<< %s >>\n",player2);// end of board's printing
							}
							else{
								clearScrean();
								sleep(400);
								printf("<< %s >>\n",player1);// board's printing
								printf("Remained walls: %d\n\n",wallCount1);
								Board(walls,k,x,y,a,b,u);
								BoardPrint(k);
								printf("\nRemained walls: %d\n",wallCount2);
								printf("<< %s >>\n",player2);// end of board's printing
								printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
								scanf("%d",&p);
							}
						}
					}while((board[aa][bb]!=space || board[(a+aa)/2][(bb+b)/2]==wall) && sw==0);
					sw=0;
					a=aa , b=bb;
					saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
				}
			}
		}while(a!=1 && x!=k-2);
	
		clearScrean();
		sleep(500);
		setTextColor(15,0);
		printf("<< %s >>\n",player1);// board's printing
		printf("Remained walls: %d\n\n",wallCount1);
		Board(walls,k,x,y,a,b,u);
		BoardPrint(k);
		printf("\nRemained walls: %d\n",wallCount2);
		printf("<< %s >>\n",player2);// end of board's printing
		//determining winner
		if(x==k-2) printf("\nThe winner is << %s >>...!",player1);
		else if(a==1) printf("\nThe winner is << %s >>...!",player2);
	}
	else if(d=='C'||d=='c'){
		u=2;
		if(r=='n'||r=='N'){
			do{//receive 'n' as dimention of the board which will be n*n
				sleep(500);
				printf("Please enter dimension of the board : ");
				scanf("%s",nn);
				n=0;
				for(i=0;nn[i];i++){
					n=n*10+(nn[i]-48);
				}
				clearScrean();
			}while(n<4 || n>25);
			k=2*n+1;
		
			if(n%2==0){x=1 , y=n-1;}// determining where should player&Computer's characters locate
			else { x=1 , y=n;}
			if(n%2==0){	a=k-2 , b=n-1;}
			else { a=k-2 , b=n;}
		
		//when player1 should enter sth , Board's color will be yellow
		//when it's Computer's turn , Board's color will be blue
		
			//scanning the nickname of player
			sleep(400);
			setTextColor(6,0);
			gets(Bug);
			printf("<< player1 >> \n");// board's printing
			printf("Remained walls: \n\n");
			Board(walls,k,x,y,a,b,u);
			BoardPrint(k);
			printf("\nRemained walls: \n");
			printf("<< Computer >> \n");// end of board's printing
			printf("\n Enter a nickname for yourself : ");
			gets(player1);
			clearScrean();
		
			do{//scanning the number of their walls
				wallCount=0;
				clearScrean();
				sleep(400);
				setTextColor(15,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: \n\n");
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: \n");
				printf("<< Computer >>\n");// end of board's printing
				printf("\nHow many walls would you like to have? ");
				scanf("%s",wallcount);
				wallCount=0;
				for(i=0;wallcount[i];i++){
					wallCount=wallCount*10+(wallcount[i]-48);
				}
				wallCount1=wallCount;
				wallCount2=wallCount;
				clearScrean();
			}while(wallCount>=n*n/4);// we use do...while because wallCount for each player shouldn't be more than n*n/4
		}
	
		do{//game started , Until someone reaches the other side, this loop will repeat
			if(turn==1){
				clearScrean();
				sleep(400);
				setTextColor(6,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: %d\n\n",wallCount1);
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: %d\n",wallCount2);
				printf("<< Computer >>\n");// end of board's printing
				printf("\nYour magic box in this turn is... ");
				sleep(800);
				srand(time(0));
				randbox=randBox();
				if(randbox==1){
					printf("Oops! All walls of the game will be erased!");
					for(e=0;e<100;e++){
						for(t=0;t<100;t++){
							walls[e][t]=space;
						}
					}
				}
				else if(randbox==2){
					printf("Oops! You lost two walls!");
					wallCount1-=2;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==3){
					printf("Oops! You lost three walls!");
					wallCount1-=3;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==4){
					printf("Oops! You lost five walls!");
					wallCount1-=5;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==5){
					printf("Oops! You are blocked for one turn!");
					turn=0;
				}
				else if(randbox==6){
					printf("Wow! You earned two walls!");
					wallCount1+=2;
				}
				else if(randbox==7){
					printf("Wow! You earned three walls!");
					wallCount1+=3;
				}
				else if(randbox==8){
					printf("Wow! You earned five walls!");
					wallCount1+=5;
				}
				else if(randbox==9){
					printf("Wow! You earned one of computer's walls!");
					wallCount1++ , wallCount2--;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==10){
					printf("Wow! You earned two of your computer's walls!");
					wallCount1+=2 , wallCount2-=2;
					if(wallCount2<0) wallCount2=0;
				}
				saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
				sleep(2000);
				if(turn==1){
					do{//player's next move...
						turn=0;
						xx=x , yy=y;
						clearScrean();
						sleep(200);
						setTextColor(6,0);
						printf("<< %s >>\n",player1);// board's printing
						printf("Remained walls: %d\n\n",wallCount1);
						Board(walls,k,x,y,a,b,u);
						BoardPrint(k);
						printf("\nRemained walls: %d\n",wallCount2);
						printf("<< Computer >>\n");// end of board's printing
						printf("\n %s  if you want to build a wall enter any button\n else move 'A' character...! ",player1);//asking the player1's next move...
			   			printf("%c",getch());
						ascii=getch();//scanning the player1's next move...
						if(ascii==80 && a==xx+2 && yy==b && board[a+1][b]!=wall) xx+=4;// ASCII code of up & down & left & right button
						else if(ascii==80) xx+=2;
						else if(ascii==75 && b==yy-2 && xx==a && board[a][b-1]!=wall) yy-=4;
						else if(ascii==75) yy-=2;
						else if(ascii==77 && b==yy+2 && xx==a && board[a][b+1]!=wall) yy+=4;
						else if(ascii==77) yy+=2;
						else if(ascii==72 && a==xx-2 && yy==b && board[a-1][b]!=wall) xx-=4;
						else if(ascii==72) xx-=2;
						else{//player chose to build a wall
							if(wallCount1>0){
								do{
			    					sw=1;
									clearScrean();
									setTextColor(6,0);
									printf("<< %s >>\n",player1);// board's printing
									printf("Remained walls: %d\n\n",wallCount1);
									Board(walls,k,x,y,a,b,u);
									BoardPrint(k);
									printf("\nRemained walls: %d\n",wallCount2);
									printf("<< Computer >>\n");// end of board's printing
									printf("\nIf the wall is vertical enter 'V' else enter 'H' : ");
									scanf("%c",&wallDirection);
									clearScrean();
								}while(wallDirection!='H' && wallDirection!='V' && wallDirection!='v' && wallDirection!='h');// we use do...while because wallDirection should be just one of these characters
			
								if(wallDirection=='v' || wallDirection=='V'){
									do{
										do{
											setTextColor(6,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< Computer >>\n");// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h-1,2*v,walls,k,x,y,a,b,3,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h-1,2*v,walls,k,x,y,a,b,1,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h-1;
									v=2*v;
									walls[h][v]=wall;
									walls[h+1][v]=wall;
									walls[h+2][v]=wall;
									wallCount1--;
								}
			
								if(wallDirection=='h' || wallDirection=='H'){
									do{
										do{
											setTextColor(6,0);
											printf("<< %s >>\n",player1);// board's printing
											printf("Remained walls: %d\n\n",wallCount1);
											Board(walls,k,x,y,a,b,u);
											BoardPrint(k);
											printf("\nRemained walls: %d\n",wallCount2);
											printf("<< Computer >>\n");// end of board's printing
											printf("\nEnter the wall's coordinates : ");
											scanf("%s",hh);
											scanf("%s",vv);
											h=0,v=0;
											for(i=0;hh[i];i++){
												h=h*10+(hh[i]-48);
											}
											for(i=0;vv[i];i++){
												v=v*10+(vv[i]-48);
											}
											clearScrean();	
										}while(h<1 || h>=n || v<1 || v>=n);
			      						for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h,2*v-1,walls,k,x,y,a,b,4,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h,2*v-1,walls,k,x,y,a,b,2,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h;
									v=2*v-1;
									walls[h][v]=wall;
									walls[h][v+1]=wall;
									walls[h][v+2]=wall;
									wallCount1--;
								}
							}
							else{
								clearScrean();
								sleep(400);
								printf("<< %s >>\n",player1);// board's printing
								printf("Remained walls: %d\n\n",wallCount1);
								Board(walls,k,x,y,a,b,u);
								BoardPrint(k);
								printf("\nRemained walls: %d\n",wallCount2);
								printf("<< Computer >>\n");// end of board's printing
								printf("\nNo wall has remained for you!\nEnter 'B' to get back... ");
								scanf("%d",&p);
							}
						}
					}while((board[xx][yy]!=space || board[(x+xx)/2][(yy+y)/2]==wall) && sw==0);
					sw=0;
					x=xx , y=yy;
					if(x==k-2) break;
				}
			}
			if(turn==0){
				clearScrean();
				sleep(400);
				setTextColor(11,0);
				printf("<< %s >>\n",player1);// board's printing
				printf("Remained walls: %d\n\n",wallCount1);
				Board(walls,k,x,y,a,b,u);
				BoardPrint(k);
				printf("\nRemained walls: %d\n",wallCount2);
				printf("<< Computer >>\n");// end of board's printing
				printf("\nComputer's magic box in this turn is... ");
				sleep(1000);
				srand(time(0));
				randbox=randBox();
				if(randbox==1){
					printf("Oops! All walls of the game will be erased!");
					for(e=0;e<100;e++){
						for(t=0;t<100;t++){
							walls[e][t]=space;
						}
					}
				}
				else if(randbox==2){
					printf("Oops! Computer lost two walls!");
					wallCount2-=2;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==3){
					printf("Oops! Computer lost three walls!");
					wallCount2-=3;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==4){
					printf("Oops! Computer lost five walls!");
					wallCount2-=5;
					if(wallCount2<0) wallCount2=0;
				}
				else if(randbox==5){
					printf("Oops! Computer is blocked for one turn!");
					turn=1;
				}
				else if(randbox==6){
					printf("Wow! Computer earned two walls!");
					wallCount2+=2;
				}
				else if(randbox==7){
					printf("Wow! Computer earned three walls!");
					wallCount2+=3;
				}
				else if(randbox==8){
					printf("Wow! Computer earned five walls!");
					wallCount2+=5;
				}
				else if(randbox==9){
					printf("Wow! Computer earned one of your walls!");
					wallCount2++ , wallCount1--;
					if(wallCount1<0) wallCount1=0;
				}
				else if(randbox==10){
					printf("Wow! Computer earned two walls of yours !");
					wallCount2+=2 , wallCount1-=2;
					if(wallCount1<0) wallCount1=0;
				}
				sleep(2500);
				if(turn==0){
					turn=1;
					clearScrean();
					sleep(400);
					setTextColor(11,0);
					printf("<< %s >>\n",player1);// board's printing
					printf("Remained walls: %d\n\n",wallCount1);
					Board(walls,k,x,y,a,b,u);
					BoardPrint(k);
					printf("\nRemained walls: %d\n",wallCount2);
					printf("<< Computer >>\n");// end of board's printing
					sleep(1000);
					
					do{//Computer's next move...
						aa=a , bb=b;
						srand(time(0));
						random=randomDecide();
						if(random%3!=0){
							random=randomMove();
							if(random==1 && x==aa+2 && bb==y) aa+=4;
							else if(random==1) aa+=2;
							else if(random==3 && bb==y-2 && aa==x) bb-=4;
							else if(random==3) bb-=2;
							else if(random==2 && y==bb+2 && x==aa) bb+=4;
							else if(random==2) bb+=2;
							else if(random==4 && x==aa-2 && y==bb) aa-=4;
							else if(random==4) aa-=2;
						}
						else{//computer is going to build a wall
							if(wallCount2>0){
			    				sw=1;
								clearScrean();
								setTextColor(11,0);
								random=rand() % 2 + 1;
								if(random%2==0)wallDirection='v';
								else wallDirection='h';
			
								if(wallDirection=='v' || wallDirection=='V'){
									do{
										do{
											h=randCoordinates(n);
											v=randCoordinates(n);
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h-1,2*v,walls,k,x,y,a,b,3,u);
										Board(walls,k,x,y,a,b,u);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h-1,2*v,walls,k,x,y,a,b,1,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h-1;
									v=2*v;
									walls[h][v]=wall;
									walls[h+1][v]=wall;
									walls[h+2][v]=wall;
									wallCount2--;
								}
			
								if(wallDirection=='h' || wallDirection=='H'){
									do{
										do{
											h=randCoordinates(n);
											v=randCoordinates(n);	
										}while(h<1 || h>=n || v<1 || v>=n);
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
										q=DFS(2*h,2*v-1,walls,k,x,y,a,b,4,u);
										Board(walls,k,x,y,a,b,u);
										clearScrean();
										for(e=0;e<100;e++){
											for(t=0;t<100;t++){
												check[e][t]=0;
											}
										}
									}while(DFS(2*h,2*v-1,walls,k,x,y,a,b,2,u)!=1 || q!=1);// we use do...while because wall's coordinates should be in the board and should be in the free places
									h=2*h;
									v=2*v-1;
									walls[h][v]=wall;
									walls[h][v+1]=wall;
									walls[h][v+2]=wall;
									wallCount2--;
								}
							}
						}
					}while((board[aa][bb]!=space || board[(a+aa)/2][(bb+b)/2]==wall) && sw==0);
					sw=0;
					a=aa , b=bb;
					saveGame(turn,walls,k,x,y,a,b,u,d,wallCount1,wallCount2,player1,player2);
				}
			}
		}while(a!=1 && x!=k-2);

		clearScrean();
		sleep(500);
		setTextColor(15,0);
		printf("<< %s >>\n",player1);// board's printing
		printf("Remained walls: %d\n\n",wallCount1);
		Board(walls,k,x,y,a,b,u);
		BoardPrint(k);
		printf("\nRemained walls: %d\n",wallCount2);
		printf("<< Computer >>\n");// end of board's printing
		//determining winner
		if(x==k-2) printf("\nThe winner is << %s >>...!",player1);
		else if(a==1) printf("\nThe winner is << Computer >>...!");
	}
}