#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>

using namespace std;

#define MAX_LENGTH 1000
const char DIR_UP='U';
const char DIR_DOWN='D';
const char DIR_LEFT='L';
const char DIR_RIGHT='R';
int consoleWidth,consoleHeight;
void initScreen(){
    HANDLE hconsole=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hconsole,&csbi);
    consoleWidth=csbi.srWindow.Right-csbi.srWindow.Left+1;
    consoleHeight=csbi.srWindow.Bottom-csbi.srWindow.Top+1;

}
void setColor(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

struct Point{
    int XCoord;
    int YCoord;
    Point(){

    }
    Point(int x,int y){
        XCoord=x;
        YCoord=y;
    }
};
class Snake{
    int length;
    char direction;
    public:
    Point body[MAX_LENGTH];
    Snake(int x,int y){
        length=1;
        body[0]=Point(x,y);
        direction=DIR_RIGHT;
    }

    int getLength(){
        return length;
    }

    void changeDirection(char newDirection){
        if(direction==DIR_UP && newDirection!=DIR_DOWN){
           direction= newDirection;
        }else  if(direction==DIR_DOWN && newDirection!=DIR_UP){
            direction= newDirection;
         }else   if(direction==DIR_RIGHT && newDirection!=DIR_LEFT){
          direction= newDirection;
         } else if(direction==DIR_LEFT && newDirection!=DIR_RIGHT){
            direction= newDirection;
         }
    }

    bool move(Point food){
       for(int i=length-1;i>0;i--){
        body[i]=body[i-1];
       }
       switch (direction){
          int val;
          case DIR_UP:
          val=body[0].YCoord;
          body[0].YCoord=val-1;
          break;

          case DIR_DOWN:
          val=body[0].YCoord;
          body[0].YCoord=val+1;
          break;

          case DIR_RIGHT:
          val=body[0].XCoord;
          body[0].XCoord=val+1;
          break;
          
          case DIR_LEFT:
          val=body[0].XCoord;
          body[0].XCoord=val-1;
          break;


       }

       for(int i=1;i<length;i++){
        if(body[0].XCoord==body[i].XCoord && body[0].YCoord==body[i].YCoord){
            return false;
        }
       }
    
       if(food.XCoord==body[0].XCoord && food.YCoord==body[0].YCoord){
        body[length]=Point(body[length-1].XCoord,body[length-1].YCoord);
        length++;

       }
       return true;

      
    }
};
class Board{
Snake *snake;
Point food;
const char SNAKE_BODY='O';
const char FOOD='o';
int score;

public:
Board(){
    spawnFood();
    snake=new Snake(10,10);
    score=0;
}
~Board(){
    delete snake;
}
int getScore(){
    return score;
}
void spawnFood(){
int x=rand()%consoleWidth;
int y=rand()%consoleHeight;
food=Point(x,y);
}

void displayscore(){
    gotoxy(consoleWidth/2,0);
    cout<<"YOUR SCORE: "<<score;
}

void gotoxy(int x,int y){
COORD coord;
coord.X=x;
coord.Y=y;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void drawBorader(){
    setColor(5);
    for(int i=0;i<consoleWidth;i++){
        gotoxy(i,1);
        cout<<"#";
        gotoxy(i,consoleHeight-1);
        cout<<"#";
    }

    for(int i=1;i<consoleHeight;i++){
        gotoxy(0,i);
        cout<<"#";
        gotoxy(consoleWidth-1,i);
        cout<<"#";
    }
}

void draw(){
    system("cls");
    drawBorader();
    for(int i=0;i<snake->getLength();i++){
        
        gotoxy(snake->body[i].XCoord,snake->body[i].YCoord);
        setColor(2);
        cout<<SNAKE_BODY;
    }
    gotoxy(food.XCoord,food.YCoord);
    setColor(4);
    cout<<FOOD;
    setColor(1);
    displayscore();
}

bool update(){
    bool isalive=snake->move(food);
    if(!isalive)return false;

    if(food.XCoord==snake->body[0].XCoord && food.YCoord==snake->body[0].YCoord){
        score++;
        spawnFood();
    }

    return true;
}
void getInput(){
    if(kbhit()){
        int key=getch();
        if(key=='W'|| key=='w'){
            snake->changeDirection(DIR_UP);
        }else if(key=='s'|| key=='S'){
            snake->changeDirection(DIR_DOWN);
        }else if(key=='d'|| key=='D'){
            snake->changeDirection(DIR_RIGHT);
        }else if(key=='A'|| key=='a'){
            snake->changeDirection(DIR_LEFT);
        }

       
    }
}

};
int main(){
    srand(time(0));
    initScreen();
    Board *board=new Board();

    while(board->update()){
     board->getInput();
     board->draw();
     Sleep(100);
    }

    cout<<"GAME OVER";
return 0;
}