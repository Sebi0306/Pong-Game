#include <iostream>
#include <conio.h>
#include <time.h>
using namespace std;

enum DirectionEnum{STOP=0, LEFT=1, UPLEFT=2, DOWNLEFT=3, RIGHT=4,UPRIGHT=5,DOWNRIGHT=6};

class BallClass{

private:
    int x, y, original_X, original_Y;
    DirectionEnum ball_direction;

public:
    BallClass(int posX, int posY)
    {
        original_X=posX;
        original_Y=posY;
        x=posX;
        y=posY;
        ball_direction=STOP;
    }

    void Reset()
    {
        x=original_X;
        y=original_Y;
        ball_direction=STOP;
    }

    void ChangeDirection(DirectionEnum dir)
    {
        ball_direction=dir;
    }

    void RandomDirection()
    {
        ball_direction = (DirectionEnum)(rand()%6+1);
    }

    void Move()
    {
        switch (ball_direction)
        {
            case STOP:
                break;

            case LEFT:
                x--;
                break;

            case UPLEFT:
                x--;
                y--;
                break;

            case DOWNLEFT:
                x--;
                y++;
                break;

            case RIGHT:
                x++;

            case UPRIGHT:
                x++;
                y--;
                break;

            case DOWNRIGHT:
                x++;
                y++;
                break;

            default:
                break;
        }
    }

    void PrintBallCoordinates()
    {
        cout<<"Ball ["<<x<<","<<y<<"] "<<ball_direction<<endl;
    }

    inline int GetX(){return x;}
    inline int GetY(){return y;}
    inline DirectionEnum GetDirection(){return ball_direction;}
};

class PaddleClass{

private:
    int x, y, originalX, originalY;

public:
    PaddleClass(int posX, int posY)
    {
        originalX=posX;
        originalY=posY;
        x=posX;
        y=posY;
    }

    inline void Reset()
    {
        x = originalX;
        y = originalY;
    }

    inline int getX(){return x;}
    inline int GetY(){return y;}

    void MoveUP(){y--;}
    void MoveDOWN(){y++;}

    void PrintPaddleCoordinates()
    {
        cout<<"Paddle ["<<x<<","<<y<<"]"<<endl;
    }
};

class GameManagerClass{

private:
    int width, height;
    int score_1=0, score_2=0;
    char up_1, down_1, up_2, down_2;
    bool quit;

    BallClass *ball;
    PaddleClass *player1, *player2;

public:
    GameManagerClass(int w, int h)
    {
        quit=false;

        up_1='w';
        down_1='s';

        up_2='i';
        down_2='k';

        width = w;
        height = h;

        ball = new BallClass(width/2,height/2);

        player1 = new PaddleClass(1, height/2-3);
        player2 = new PaddleClass(width-2, height/2-3);
    }

    ~GameManagerClass()
    {
        delete ball;
        delete player1;
        delete player2;
    }

    void ScoreUp(PaddleClass *player)
    {
        if(player == player1)
            score_1++;
        else
            score_2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw()
    {
        system("cls");

        int ballX = ball->GetX();
        int ballY = ball->GetY();

        int player1_X = player1->getX();
        int player1_Y = player1->GetY();

        int player2_X = player2->getX();
        int player2_Y = player2->GetY();

        cout<<endl<<endl<<"\t";

        for(int i=0;i<width+2;i++)
            cout<<"\xB0";

        cout<<endl;

        for(int i=0;i<height;i++)
        {
            cout<<"\t";
            for(int j=0;j<width;j++)
            {
                if(j==0)
                    cout<<"\xB0";

                if(ballX==j && ballY==i)
                    cout<<"O";

    // Draw Player 1
                else if(player1_X==j && player1_Y==i)
                    cout<<"\xDB";
                else if(player1_X==j && player1_Y+1==i)
                    cout<<"\xDB";
                else if(player1_X==j && player1_Y+2==i)
                    cout<<"\xDB";
                else if(player1_X==j && player1_Y+3==i)
                    cout<<"\xDB";

    // Draw Player 2
                else if(player2_X==j && player2_Y==i)
                    cout<<"\xDB";
                else if(player2_X==j && player2_Y+1==i)
                    cout<<"\xDB";
                else if(player2_X==j && player2_Y+2==i)
                    cout<<"\xDB";
                else if(player2_X==j && player2_Y+3==i)
                    cout<<"\xDB";

                else
                    cout<<" ";

                if(j==width-1)
                    cout<<"\xB0";

            }
            cout<<endl;
        }

        cout<<"\t";

        for(int i=0;i<width+2;i++)
            cout<<"\xB0";

        cout<<endl<<endl;
        cout<<"\tPlayer 1:\t\t\t\tPlayer 2: "<<endl<<"\t"<<score_1<<"\t\t\t\t\t"<<score_2;

    }

    void Input()
    {
        ball->Move();

        int player1_Y = player1->GetY();

        int player2_Y = player2->GetY();

        if(_kbhit())
        {
            char key = _getch();

            if(key == up_1 && player1_Y > 0)
                player1->MoveUP();

            if(key == down_1 && (player1_Y + 4) < height)
                player1->MoveDOWN();

            if(key == up_2 && player2_Y > 0)
                player2->MoveUP();

            if(key == down_2 && (player2_Y + 4) <height)
                player2->MoveDOWN();

            if(key == 'q')
                quit = true;

            if(ball->GetDirection() == STOP)
                ball->RandomDirection();
        }
    }

    void Logic()
    {
        int ballX = ball->GetX();
        int ballY = ball->GetY();

        int player1_X = player1->getX();
        int player1_Y = player1->GetY();

        int player2_X = player2->getX();
        int player2_Y = player2->GetY();

        //left paddle
        for(int i=0;i<4;i++)
            if((ballX==(player1_X+1))&&(ballY==(player1_Y+i)))
                ball->ChangeDirection((DirectionEnum)(rand()%3+4));

        //right paddle
        for(int i=0;i<4;i++)
            if((ballX==(player2_X-1))&&(ballY==(player2_Y+i)))
                ball->ChangeDirection((DirectionEnum)(rand()%3+1));

        //bottom wall
        if(ballY == height-1)
        {
            if(ball->GetDirection()==DOWNRIGHT)
                ball->ChangeDirection(UPRIGHT);
            else
                ball->ChangeDirection(UPLEFT);
        }


        //top wall
        if(ballY == 0)
        {
            if(ball->GetDirection()==UPRIGHT)
                ball->ChangeDirection(DOWNRIGHT);
            else
                ball->ChangeDirection(DOWNLEFT);
        }

        //left wall
        if(ballX == 1)
            ScoreUp(player2);

        //right wall
        if(ballX == width-1)
            ScoreUp(player1);
    }

    void Run()
    {
        while(!quit)
        {
            Draw();
            Input();
            Logic();
        }
    }
};

int main()
{
    GameManagerClass game(50,15);
    srand(time(0));
    game.Run();

    return 0;
}
