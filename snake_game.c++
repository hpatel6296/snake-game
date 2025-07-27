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
           switch (getch())
           {
            case 'a':
                dir =  LEFT;
                break;
            case 'd':
                dir =  RIGHT;
                break;
            case 'w':
                dir =  UP;
                break;
            case 's':
                dir =  DOWN;
                break;
                            
           
           default:
            break;
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
    cout<<"*********************************************\n";
    cout<<"\t\tSnake game\n";
    cout<<"*********************************************\n";
    char start;
    cout<<"\nPress 's' to start game =";
    cin>>start;
    if(start=='s'){
          setup();
          while(!gameOver){
          draw();
          input();
          logic();
          Sleep(30);
          system("cls");
          }
    }
    cout<<"Game Over! Your score is: "<<score<<endl;
    return 0;
}
