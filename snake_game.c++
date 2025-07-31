#include<iostream>
#include<windows.h>
#include<conio.h>
using namespace std;

enum Direction{STOP,RIGHT,LEFT,UP,DOWN};
Direction dir;
bool gameOver;
const int height = 20;
const int width = 20;
int headX,headY,fruitX,fruitY,tail_len,score;
int tailx[100],taily[100];
void setup(){
    gameOver = false;
    dir = STOP;
    headX = width/2;
    headY = width/2;
    fruitX = rand()%width;
    fruitY = rand()%height;
}
void showSplashScreen() {
    system("cls");
    cout << R"(
   _________              __         
  /   _____/ ____   _____/  |_  ____ 
  \_____  \ /  _ \ /    \   __\/ __ \
  /        (  <_> )   |  \  | \  ___/
 /_______  /\____/|___|  /__|  \___  >
         \/            \/          \/
)" << endl;
    cout << "\nPress any key to continue...";
    getch();
}

void showMenu() {
    system("cls");
    cout << "====================================\n";
    cout << "\t  SNAKE GAME - C++ \n";
    cout << "====================================\n";
    cout << "1. Start Game\n";
    cout << "2. Instructions\n";
    cout << "3. Exit\n";
    cout << "Enter choice: ";
}
void draw(){
    system("cls");
    //uper border
    cout<<"\t\t";
    for(int i=0;i<width-8;i++){
        cout<<"||";
    }
     cout<<endl;
     for(int i=0;i<height;i++){
         for(int j=0;j<width;j++){
            //Left border
            if(j == 0){
                cout<<"\t\t||";
            }
            //head of snake
            if(i == headY && j==headX){
                cout<<"O";
            }
            //fruit
            else if(i == fruitY && j == fruitX){
                cout<<"*";
            }
            //space,tail
            else{
                bool print = false;
                for(int k =0;k<tail_len;k++){
                    if(tailx[k]==j && taily[k]==i){
                        cout<<"o";
                        print = true;
                    }
                }
                //space
                if(!print){
                cout<<" ";
                }
            }
            //Left border
            if(j == width-1){
                cout<<"||";
            }
         }
         cout<<endl;
     }
     cout<<"\t\t";
     //Lower bownry
       for(int i=0;i<width-8;i++){
        cout<<"||";
    }
     cout<<endl;
     cout<<"\t\t Score:"<<score;
}
void input(){
    if (_kbhit()) {
        switch (getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
        }
    }
}

void logic(){
        int prevx = tailx[0];
        int prevy = taily[0];
        int prev2x,prev2y;
        tailx[0] = headX;
        taily[0] = headY;
        for(int i=1;i<tail_len;i++){
            prev2x = tailx[i];
            prev2y = taily[i];
            tailx[i] = prevx;
            taily[i] = prevy;
            prevx = prev2x;
            prevy = prev2y;
        }
        switch (dir)
        {
        case LEFT:
            headX--;
            break;
        case RIGHT:
            headX++;
            break;
           
        case UP:
            headY--;
            break;
            
        case DOWN:
            headY++;
            break;
        
        default:
            
            break;
        }
        // touch wall
        if (headX >=width)
        {
            headX = 0;
        }
        else if(headX<0){
            headX = width-1;
        }
        
        if (headY >=height)
        {
            headY = 0;
        }
        else if(headY<0){
            headY = height-1;
        }
        //snake bit itself 
        for (int i = 0; i < tail_len; i++)
        {
            if (tailx[i] == headX && taily[i] == headY){
                gameOver = true;
            }
        }
        //snake eat fruit
        if(headX == fruitX && headY == fruitY){
            score += 10;
            fruitX = rand()%width;
            fruitY = rand()%height;
            tail_len++;
        }
}

int main(){

    int start;
    showSplashScreen();
    again:
    showMenu();
    cin>>start;
    if(start==1){
          setup();
          while(!gameOver){
          draw();
          input();
          logic();
          Sleep(100);
          cout<<"Score ="<<score<<endl;
          return 0;
          } 
    }
    if (start == 2){
        system("cls");
        cout << "INSTRUCTIONS:\n";
        cout << "- Use W A S D to move the snake\n";
        cout << "- Eat * to grow and gain score\n";
        cout << "- Don't hit your own tail\n";
        cout << "\nPress any key to go back...";
        getch();
        showMenu();

        cin>>start;
        goto again;
    }
    
    if(start == 3){
        cout<<"Good bye";
    }
    return 0;
} 
