#include "Tetris.h"
#include <iostream>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <random>
#include <chrono>

using namespace std;

int currx,curry,speed=10,height=16;

Tetris::Tetris() = default;

void Tetris::crBoard() {
    for (int i = 0; i < 16; i++) {
        for (int m = 0; m < 10; m++) {
            liste[i][m] = 0;
        }
    }
    for (int m = 0; m < 10; m++) {
        liste[16][m] = 2;
    }
}

void Tetris::prBoard(int h) {
    cout<<"____________"<<'\t'<<"SCORE: "<<score<<'\t'<<"COMBO: "<<combo<<endl;
    for(int i=0;i<h;i++){
        cout<<"|";
        for(int m=0;m<10;m++){
            if(liste[i][m]==0) cout<<" ";
            else cout<<block;
        }
        cout<<"|"<<endl;
    }
    cout<<"############"<<endl<<endl<<"NEXT PIECE"<<'\t'<<"HOLDING PIECE"<<endl<<"   ";

    for (int i = 0; i < 3; ++i) {
        for (int m = 0; m < 3; ++m) {
            if (nextPiece[i][m] == 0) cout <<" ";
            else cout << block;
        }
        cout<<'\t'<<'\t'<<"      ";
        for (int m = 0; m < 3; ++m){
            if (holdPiece[i][m] == 0) cout <<" ";
            else cout << block;
        }
        cout<<endl<<"   ";}
    cout<<endl;
}

void Tetris::randomPiece() {
    static int rand1=-1;
    unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());
    mt19937 gen(seed);
    uniform_int_distribution<int> distribution(0, currPieceNum-1);
    int randPiece = distribution(gen);
    if(rand1==-1) distribution(gen);
    while(randPiece==rand1) randPiece = distribution(gen);
    rand1=randPiece;
    for (int i = 0; i < 3; ++i)
        for (int m = 0; m < 3; ++m) nextPiece[i][m]=pieces[randPiece][i][m];
}

void Tetris::addPiece() {
    int a=1;
    system("CLS");
    currPieceNum++;
    int num;
    cout<<"HOW TO ADD PIECE:"<<endl<<"YOU HAVE TO ENTER 9 INPUTS AND ALL OF THE 9 INPUT MUST BE 0 OR 1(IF YOU DON' CODE WILL CRASH)"<<
        endl<<"YOUR FIRST INPUT WILL BE '0,0' OF THE PIECE"<<endl<<"YOUR FOURTH WILL BE INPUT '1,0' OF THE PIECE."<<endl;
    for(int i=0;i<3;i++){
        for(int m=0;m<3;m++){
            cout<<a<<".INPUT: ";cin>>num;
            pieces[currPieceNum-1][i][m]=num;
            a++;
        }
    }
}

void Tetris::placePiece() {
    static int x = 0;
    currx = 4;
    curry = 0;
    if (x == 0) {
        randomPiece();
        for (int i = 0; i < 3; ++i)
            for (int m = 0; m < 3; ++m)
                currPiece[i][m] = nextPiece[i][m];
        x++;
    } else {
        for (int i = 0; i < 3; ++i)
            for (int m = 0; m < 3; ++m) {
                currPiece[i][m] = nextPiece[i][m];
                x++;
            }
    }

    randomPiece();
    for (int i = 0; i < 3; i++)
        for (int m = 0; m < 3; m++)
            if (currPiece[i][m] == 1){
                if (liste[curry + i][currx + m] != 0) isAlive = false;
                liste[curry + i][currx + m] = currPiece[i][m];}
}

bool Tetris::down(){
    for(int i=0;i<3;i++) {
        if (currPiece[2][i] == 1) {
            if (liste[curry + 3][currx + i] != 0) return false;
        } else if (currPiece[1][i] == 1) {
            if (liste[curry + 2][currx + i] != 0) return false;
        } else if (currPiece[0][i] == 1) {
            if (liste[curry + 1][currx + i] != 0) return false;
        }
    }
    for(int i=2;i>=0;i--){
        for(int m=2;m>=0;m--){
            if(currPiece[i][m]!=0){
                liste[curry+i][currx+m]=0;
                liste[curry+i+1][currx+m]=1;
            }
        }
    }
    curry++;
    score+=5;
    return true;
}

bool Tetris::Move(int x) {
    if(x==-1){
        for(int i=0;i<3;i++){
            if(currPiece[i][0]==1){
                if(liste[curry+i][currx-1]!=0 || currx-1<0) return false;}
            else if(currPiece[i][1]==1){
                if(liste[curry+i][currx]!=0 || currx<0) return false;}
            else if(currPiece[i][2]==1){
                if(liste[curry+i][currx+1]!=0 || currx+1<0) return false;}
        }
        for(int i=0;i<3;i++){
            for(int m=0;m<3;m++){
                if(currPiece[m][i]!=0){
                    liste[curry+m][currx+i]=0;
                    liste[curry+m][currx+i-1]=1;
                }
            }
        }
        currx--;
        return true;
    }
    else if(x==1){
        for(int i=0;i<3;i++){
            if(currPiece[i][2]==1){
                if(liste[curry+i][currx+3]!=0 || currx+3>9) return false;}
            else if(currPiece[i][1]==1){
                if(liste[curry+i][currx+2]!=0 || currx+2>9) return false;}
            else if(currPiece[i][0]==1){
                if(liste[curry+i][currx+1]!=0 || currx+1>9) return false;}
        }
        for(int i=2;i>=0;i--){
            for(int m=0;m<3;m++){
                if(currPiece[m][i]!=0){
                    liste[curry+m][currx+i]=0;
                    liste[curry+m][currx+i+1]=1;
                }
            }
        }
        currx++;
        return true;
    }
    else{
        while(down());
        return true;
    }
}

bool Tetris::checkLine() {
    int numClear = 0;
    for (int i = 15; i >= 3; i--) {
        bool isClear = true;
        for (int m = 0; m < 10; m++) {
            if (liste[i][m] != 1) {
                isClear = false;
                break;
            }
        }
        if (isClear) {
            numClear++;
            combo++;
            for (int n = i; n >= 1; n--) {
                for (int m = 0; m < 10; m++) {
                    liste[n][m] = liste[n - 1][m];
                }
            }

            if (currPiece[2][0] == 1 || currPiece[2][1] == 1 || currPiece[2][2] == 1) {
                currPiece[2][0] = 0;currPiece[2][1] = 0;currPiece[2][2] = 0;
            } else if (currPiece[1][0] == 1 || currPiece[1][1] == 1 || currPiece[1][2] == 1) {
                currPiece[1][0] = 0;currPiece[1][1] = 0;currPiece[1][2] = 0;
            } else {
                currPiece[0][0] = 0;currPiece[0][1] = 0;currPiece[0][2] = 0;
            }
            score += 100 * numClear * numClear * (combo + 1);
            return true;
        }
    }
    return false;
}

void Tetris::turnPiece() {
    int tempPiece[3][3]{ };
    for(int i=0;i<3;i++) {
        if (currPiece[2][i] == 1) {
            if (liste[curry + 3][currx + i] != 0) return;
        } else if (currPiece[1][i] == 1) {
            if (liste[curry + 2][currx + i] != 0) return;
        } else if (currPiece[0][i] == 1) {
            if (liste[curry + 1][currx + i] != 0) return;
        }
    }
    for (int i = 0; i < 3; i++)
        for (int m = 0; m < 3; m++) {
            tempPiece[i][m] = currPiece[2 -m][i];
            if (currPiece[i][m] == 1)
                liste[curry + i][currx + m] = 0;
        }
    if(currx<0) currx=0;if(currx>7) currx=7;
    for (int i = 0; i < 3; i++)
        for (int m = 0; m < 3; m++)
            if (tempPiece[i][m] == 1) {
                if (liste[curry + i][currx + m] == 1) return;
            }
    for (int i = 0; i < 3; i++)
        for (int m = 0; m < 3; m++) {
            currPiece[i][m] = tempPiece[i][m];
        }
}

void Tetris::turnPiece_() {
    turnPiece();turnPiece();turnPiece();
}

void Tetris::theme() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    static int z=0;
    char c;
    system("CLS");cout<<"CURRENT COLOUR: "<<colour_<<'\t'<<"|| PRESS 't' TO CHANGE THEME"<<
                      endl<<"CURRENT BLOCK SHAPE: "<<block<<'\t'<<"|| PRESS 'e' TO CHANGE SHAPE"<<endl<<
                      endl<<"PRESS 'q' TO GO BACK TO MENU"<<endl;cin>>c;
    switch (c) {
        case 'q':
            runGame();
            break;
        case 't':
            if (z==0) {SetConsoleTextAttribute(h,13);;z++;colour_="PINK";colour=13;}
            else if(z==1) {SetConsoleTextAttribute(h,14);;z++;colour_="YELLOW";colour=14;}
            else{ SetConsoleTextAttribute(h,7);;z=0;colour_="WHITE";colour=7;}
            break;
        case 'e':
            system("CLS");cout<<"ENTER YOUR SHAPE: ";cin>>c;block=c;break;
        default:
            break;
    }
    theme();
}

void Tetris::holdPiece_() {
    if(hold!=0) return;
    hold++;
    static int u = 0;
    if (u == 0) {
        for (int i = 0; i < 3; ++i) {
            for (int m = 0; m < 3; ++m) {
                holdPiece[i][m] = currPiece[i][m];liste[curry+i][currx+m] = 0;u++;}}
        curry=1;placePiece();}
    else{
        int tempPiece[3][3];
        for (int i = 0; i < 3; ++i) {
            for (int m = 0; m < 3; ++m){
                if(currPiece[i][m]==1) liste[curry+i][currx+m]=0;
                tempPiece[i][m] = currPiece[i][m]; currPiece[i][m]= holdPiece[i][m]; holdPiece[i][m]=tempPiece[i][m];}}
        currx=4;curry=-1;}}


bool Tetris::mainMenu() {
    system("CLS");
    cout<<"WELCOME TO THE TETRIS GAME"<<endl<<endl;
    if(isStart==1) cout<<"PRESS 'n' TO CONTINUE THE GAME"<<endl;
    cout<<"PRESS 's' TO START A NEW GAME"<<endl<<"PRESS 'e' TO CHANGE SETTINGS"<<
        endl<<"PRESS 'c' TO CREATE YOUR OWN PIECE"<<endl<<"PRESS 'h' TO HOW TO PLAY"<<endl<<"PRESS 'q' TO QUIT THE GAME"<<endl;
    char c;cin>>c;
    switch(c){
        case 's':
            crBoard();placePiece();
            score=0;combo=0;
            return true;
        case 'n':
            return true;
        case 'e':
            system("CLS");
            cout<<"PRESS 'q' TO GO BACK TO MENU"<<endl<<endl<<"PRESS 'd' TO SET DIFFICULTY"<<endl<<"PRESS 't' TO CHANGE THEME"<<endl;
            cin>>c;
            switch (c) {
                case 'q':
                    runGame();
                    break;
                case 'd':
                    system("CLS");cout<<"PRESS 'e' TO EASY MODE"<<endl<<"PRESS 'n' TO NORMAL MODE"<<endl<<"PRESS 'h' TO HARD MODE: ";cin>>c;
                    switch (c) {
                        case 'e':speed=15;runGame();break;
                        case 'n':speed=10;runGame();break;
                        case 'h':speed=5;runGame();break;
                        default:break;}
                case 't':
                    theme();
                    break;
                default:break;
            }
            break;
        case 'h':
            system("CLS");
            cout<<"WELCOME TO THE TETRIS GAME"<<endl<<endl<<"PRESS 'p' TO PAUSE THE GAME"<< endl<<"PRESS 'd' TO MOVE YOUR PIECE TO RIGHT"<<endl<<"PRESS 'a' TO MOVE YOUR PIECE LEFT"<<
                endl<<"PRESS 's' TO MOVE YOUR PIECE DOWN"<<endl<<"PRESS 'e' TO TURN PIECE TO RIGHT YOU CAN USE IT 3 TIMES FOR EACH PIECE"<<
                endl<<"PRESS 'q' TO TURN PIECE LEFT YOU CAN USE IT 3 TIMES FOR EACH PIECE"<<endl<<"PRESS 'h' TO HOLD PIECE (CAN NOT HOLD TWICE)"<<
                endl<<"YOUR INPUTS MUST BE LOWERCASE"<<endl<<"THERE WILL BE A RANDOM EVENTS THAT SIZE OF THE BOARD WILL DECREASE BY 1"<<
                endl<<"GAME SPEED WILL INCREASE AFTER SOME TIME"<<endl<<endl<<"PRESS ANY KEY TO GO BACK TO MENU"<<endl;
            cin>>c;
            runGame();
            break;
        case 'c':
            addPiece();
            runGame();
            break;
        case 'q':
            system("CLS");
            exit(3);
        default:
            runGame();
    }
    return false;
}

void Tetris::changeHeight() {
    for(int i=3;i<height;i++)
        for(int m=0;m<10;m++)
            if(liste[i][m]==1){liste[i][m]=0;liste[i-1][m]=1;}
    for(int i=0;i<10;i++)
        liste[height][i]=2;
    height--;
}

void Tetris::runGame() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    isAlive=true;
    bool n = mainMenu();
    crBoard();
    char num;
    int speedCount=0,incSpeed=0,isS=speed,turn=0,chH=0,m=0;score=0;combo=0;
    placePiece();
    if (n) {
        isStart=1;
        while (isAlive) {
            system("CLS");
            prBoard(height);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));speedCount++;isS++;chH++;incSpeed++;m++;
            if(speed==speedCount) {
                speedCount=0;
                if (!down()) {
                    while (checkLine());
                    if(chH>speed*40){
                        changeHeight();chH=0;
                    }
                    placePiece();
                    hold = 0;turn=0;
                }
            }
            if(m==12){SetConsoleTextAttribute(h,colour);m=0;}
            if(incSpeed>60){speed++;incSpeed=0;}
            if (_kbhit()) {
                num = _getch();
                switch (num) {
                    case 'p':
                        mainMenu();
                        break;
                    case 'a':
                        Move(-1);
                        break;
                    case 'd':
                        Move(1);
                        break;
                    case 's':
                        if(isS>speed){
                            Move(0);
                            while (checkLine());
                            if(chH>speed*40){
                                changeHeight();chH=0;
                            }
                            placePiece();
                            isS=0;turn=0;speedCount=0;hold=0;}
                        break;
                    case 'e':
                        if(turn==3){SetConsoleTextAttribute(h,12);m=0;}
                        else{turnPiece();turn++;}
                        break;
                    case 'q':
                        if(turn==3){SetConsoleTextAttribute(h,12);m=0;}
                        else{turnPiece_();turn++;}
                        break;
                    case 'h':
                        holdPiece_();
                        speedCount=0;turn=0;isS=0;
                        break;
                    default:
                        break;
                }
            }
        }
    }
    system("CLS");
    isStart=0;
    cout<<"GAME OVER"<<endl<<"TO RESTART PRESS 'r'"<<endl<<"PRESS 'q' TO QUIT THE GAME"<<endl;cin>>num;
    switch (num) {
        case 'q':
            return;
        case 'r':
            runGame();
            break;
        default:
            break;
    }
}