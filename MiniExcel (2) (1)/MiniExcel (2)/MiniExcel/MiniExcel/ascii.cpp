#pragma once
#include <cmath>
#include <iostream>
#include <Windows.h>
#include "ascii.h"
using namespace std;

char leftUpperCorner = char(218); // ┌
char rightUpperCorner = char(191); // ┐
char leftBottomCorner = char(192); // └
char rightBottomCorner = char(217); // ┘
char upwardT = char(193); // ┴
char downwardT = char(194); // ┬
char rightwardT = char(195); // ├
char leftwardT = char(180); // ┤
char cross = char(197); // ┼
char nDash = char(196); // ─
char pipe = char(179); // │

void gotoxy(int x, int y)
{
    COORD coordinates;
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void setColor(int k) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), k);
}

void printBoxAt(int x, int y, int len, string s) {
    int l = s.length();

    for (int i = 0; i < (len - l); i++) {
        s += ' ';
    }

    gotoxy(x, y);
    cout << leftUpperCorner;
    for (int i = 0; i < len; i++) {
        cout << nDash;
    }
    cout << rightUpperCorner;

    gotoxy(x, y + 1);

    cout << pipe;

    for (int i = 0; i < len; i++) {
        cout << s[i];
    }
    cout << pipe;

    gotoxy(x, y + 2);

    cout << leftBottomCorner;

    for (int i = 0; i < len; i++) {
        cout << nDash;
    }
    cout << rightBottomCorner;
}

void printInBox(string s){
    int l = s.length();

    cout << leftUpperCorner;
    for(int i = 0; i < l; i++){
        cout << nDash;
    }
    cout << rightUpperCorner << endl << pipe;

    for(int i = 0; i < l; i++){
        cout << s[i];
    }
    cout << pipe << endl << leftBottomCorner;

    for(int i = 0; i < l; i++){
        cout << nDash;
    }
    cout << rightBottomCorner << endl;
}

void printInGrid(string s, int gridSize, int contentLen){
    int l = s.length();
    int lines = ceil((float)l / gridSize);
    int printedLines = 0;
    int currentLine = 0;

    for(int i = 0; i < (lines * gridSize - l); i++){
        s += ' ';
    }

    // top line
    cout << leftUpperCorner << nDash;

    for (int i = 0; i < contentLen; i++) {
        cout << nDash;
    }

    cout << nDash;
    for(int i = 0; i < gridSize - 1; i++){
        cout << downwardT << nDash << nDash << nDash;
    }
    cout << rightUpperCorner << endl;
    currentLine++;

    cout << pipe;
    for(int i = 0; i < gridSize; i++){
        cout << " " << s[printedLines * gridSize + i] << " " << pipe;
    }
    cout << endl;
    printedLines++;


    for(; currentLine < lines; currentLine++){
        cout << rightwardT << nDash << nDash << nDash;
        for(int j = 0; j < gridSize - 1; j++){
            cout << cross << nDash << nDash << nDash;
        }
        cout << leftwardT << endl;

        cout << pipe;
        for(int i = 0; i < gridSize; i++){
            cout << " " << s[printedLines * gridSize + i] << " " << pipe;
        }
        cout << endl;
        printedLines++;
    }

    cout << leftBottomCorner << nDash << nDash << nDash;
    for(int i = 0; i < gridSize - 1; i++){
        cout << upwardT << nDash << nDash << nDash;
    }
    cout << rightBottomCorner << endl;
}
