#pragma once
#include <iostream>

class Tetris{
private:
    bool isAlive;
    int hold=0;
    int combo=0;
    int liste[17][10]{  };
    int currPiece[3][3]{  };
    int nextPiece[3][3]{  };
    int holdPiece[3][3]={  };
    int score=0;
    char block='X';
    int isStart=0;
    int colour=7;
    std::string colour_="WHITE";
    int currPieceNum=8;
    int pieces[30][3][3]={
            {1,1,0,{1,1,0},{0,0,0}}, // Square
            {1,0,0,{1,1,0},{0,0,0}}, // Corner
            {1,0,0,{1,0,0},{1,0,0}}, // Tower
            {0,1,1,{1,1,0},{0,0,0}}, // Zigzag
            {1,0,1,{1,1,1},{0,0,0}}, // U
            {1,0,0,{1,1,0},{0,1,0}}, // Step
            {1,0,0,{1,1,1},{0,0,1}}, // Double Zigzag
            {0,1,0,{1,1,1},{0,0,0}}, // Pyramid
    };

    bool checkLine();
    bool down();
    bool Move(int x);
    void crBoard();
    void prBoard(int h);
    void randomPiece();
    void placePiece();
    void turnPiece();
    void turnPiece_();
    void holdPiece_();
    bool mainMenu();
    void theme();
    void addPiece();
    void changeHeight();

public:
    Tetris();
    void runGame();

};
#include "Tetris.cpp"
//If the code gives ‘redefinition’ error, then delete ‘#include "Tetris.cpp"’