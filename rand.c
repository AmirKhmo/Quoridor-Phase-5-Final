#include <stdio.h>
#include <stdlib.h>

int randomDecide() {// random decision of computer to build a wall or make a move
    return rand() % 3 + 1;
}


int randomMove() {//random decision of computer for moving in which way
    return rand() % 4 + 1;
}


int randCoordinates(int n){
    return rand() % n + 1;
}


int randBox(){//random box , a reward or a curse
    return rand() % 10 + 1;
}