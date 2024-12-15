#include "raylib.h"
int main()
{
    InitWindow(800, 800, "Pong");
    SetTargetFPS(60);
    int left_count=0,right_count=0;

    // Paddle properties
    Vector2 position1 = { 30, 800 / 2.0f - 75 };
    Vector2 position2 = { 770, 800 / 2.0f - 75 };
    float paddleWidth = 5.0f;
    float paddleHeight = 150.0f;
    float paddleSpeed = 5.0f;

    // Ball properties
    float ballRadius = 8.0f;
    Vector2 ballPosition = { 400, 400 };
    Vector2 ballSpeed = { 300, 300 };
    bool ispaused=false;

    while (!WindowShouldClose())
    {
     if(!ispaused){
        ballPosition.x += ballSpeed.x * GetFrameTime();
        ballPosition.y += ballSpeed.y * GetFrameTime();

        if (ballPosition.y - ballRadius <= 0 || ballPosition.y + ballRadius >= GetScreenHeight())
        {
            ballSpeed.y *= -1;
        }

       
        if (ballPosition.x - ballRadius <= 0 )
        {
            right_count++;
            ballSpeed.x *= -1; 
          
        }
        if(ballPosition.x + ballRadius >= GetScreenWidth())
        {
            left_count++;
            ballSpeed.x *= -1;
        }
         if (IsKeyDown(KEY_W) && position1.y > 0) position1.y -= paddleSpeed;
        if (IsKeyDown(KEY_S) && position1.y + paddleHeight < GetScreenHeight()) position1.y += paddleSpeed;
        if (IsKeyDown(KEY_UP) && position2.y > 0) position2.y -= paddleSpeed;
        if (IsKeyDown(KEY_DOWN) && position2.y + paddleHeight < GetScreenHeight()) position2.y += paddleSpeed;
     }
        // Paddle movement
       
        if(IsKeyPressed(KEY_P))   ispaused = !ispaused;

        // Ball collision with paddles
        if ((ballPosition.x - ballRadius <= position1.x + paddleWidth &&
             ballPosition.y >= position1.y && ballPosition.y <= position1.y + paddleHeight) ||
            (ballPosition.x + ballRadius >= position2.x &&
             ballPosition.y >= position2.y && ballPosition.y <= position2.y + paddleHeight))
        {
            ballSpeed.x *= -1;
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw ball
        DrawCircleV(ballPosition, ballRadius, WHITE);

        // Draw paddles
        DrawRectangleV(position1, (Vector2){ paddleWidth, paddleHeight }, WHITE);
        DrawRectangleV(position2, (Vector2){ paddleWidth, paddleHeight }, WHITE);
        if(ispaused){
       
            if(left_count>right_count)
             DrawText("RIGHT PLAYER WON",200,400,50,YELLOW);
             else if(right_count>left_count){
                 DrawText("LEFT PLAYER WON",200,400,50,YELLOW);
             }
             else
             {
                DrawText("DRAW",200,400,50,YELLOW);
             }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
