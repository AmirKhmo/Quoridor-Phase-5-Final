#include <stdio.h>
#include <windows.h>
#include <time.h>


void clearScrean(){
    system("cls");
}


void setTextColor(int textColor, int backColor) {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = backColor << 4 | textColor;
    SetConsoleTextAttribute(consoleHandle, colorAttribute);
}


void sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}