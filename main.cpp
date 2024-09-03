#include<iostream>
#include<raylib.h>
#include<raymath.h>
#include <deque>
using namespace std;
const int Screen_width = 1000;
const int Screen_height= 500;
int speed_x=7  , speed_y=7;
int height = 100;
int Player_Score=0 , Cpu_Score=0;;
    double LastUpdatedTime=0;
bool TimeForCpu(double interval)
{
    double CurrentTime= GetTime();
    if(CurrentTime-LastUpdatedTime >=interval)
    {
        LastUpdatedTime=CurrentTime;
        return true;
    }
    else
    return false;
}
class Paddle{
    public:
    int update_paddle_Y=0, valueOfupdate_paddle=5;
    int YOfPaddle=(Screen_height -height)/2-update_paddle_Y   , XofPaddle=Screen_width-35;
void draw()
{
    DrawRectangle( XofPaddle, YOfPaddle , 25 , height , WHITE);
}
void update()
{
    update_paddle_Y+=valueOfupdate_paddle;
    YOfPaddle=(Screen_height -height)/2-update_paddle_Y;
    if(update_paddle_Y>=180 || update_paddle_Y<=-180)
    valueOfupdate_paddle*=-1;
}

};
class Ball {
    public:
    int xofBall = Screen_width/2 , yofBall =Screen_height/2;
    void draw()
    {
         DrawCircle(xofBall , yofBall , 15 , WHITE);   
    }
    void update()
    {
        
       xofBall+=speed_x;
       yofBall+=speed_y;
       if(yofBall>=Screen_height || yofBall<= 0)
       {
       speed_y*=-1;
       }
       if( xofBall>=Screen_width )
       {
        Cpu_Score+=10;
        xofBall = GetRandomValue(Screen_width/2 - 40 ,Screen_width/2 - 20 );
       }
       if(xofBall<=0)
       {
        Player_Score+=10;
        
        xofBall = GetRandomValue(Screen_width/2 +20 ,Screen_width/2 + 40 );
       }
    }
};
class CpuPaddle: public Paddle{
public:
int speed=6;
int YofCpu=(Screen_height + -height)/2 ;  // 125 is the height
void update(int ball_y)
{
    if(YofCpu + height/2 >ball_y )
    {
        YofCpu-=speed;
    }
    if(YofCpu + height/2 < ball_y  )
    {
        YofCpu+=speed;
    }
}
void draw()
{
    DrawRectangle(10 , YofCpu , 25 , height , WHITE);
}

};
int main()
{
InitWindow(Screen_width , Screen_height , "PING POMG!");
SetTargetFPS(60);
Ball ball;
Paddle padd;
CpuPaddle cpu;
while (WindowShouldClose()==false)
{
    BeginDrawing();
    ClearBackground(GREEN);
    ball.update();
    ball.draw();
    padd.draw();
    padd.update();
    if(TimeForCpu(0.015))
    {
    cpu.update(ball.yofBall); // 000000000
    }
    cpu.draw();
    if(IsKeyPressed(KEY_DOWN) )
    { 
        if(padd.valueOfupdate_paddle>0)
    padd.valueOfupdate_paddle*=-1;
    }
     if (IsKeyPressed(KEY_UP) )
     {
        if(padd.valueOfupdate_paddle<0)
        padd.valueOfupdate_paddle*=-1;
     }
     
    if(CheckCollisionCircleRec(Vector2{(float)ball.xofBall ,(float) ball.yofBall} , 15 , Rectangle{(float)padd.XofPaddle , (float)padd.YOfPaddle , 25 , 125}))
    speed_x*=-1;
     if(CheckCollisionCircleRec(Vector2{(float)ball.xofBall ,(float) ball.yofBall} , 15 , Rectangle{10 , (float)cpu.YofCpu , 25 , 125}))  
      speed_x*=-1;
     
    DrawLine(Screen_width/2 , 0 , Screen_width/2 , Screen_height , WHITE);
    DrawCircle(Screen_width/2 , Screen_height/2 , 80 , {242, 242, 242 , 100} );
    DrawText(TextFormat("%i" , Player_Score) , 3*Screen_width/4 -20 , 30 , 30 , WHITE);
    DrawText(TextFormat("%i" , Cpu_Score) , Screen_width/4 -20 , 30 , 30 , WHITE);
    EndDrawing();
}

CloseWindow();
 return 0;
}