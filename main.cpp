#include "raylib.h"
#include <cstdio>
namespace score{
int lscore=0,rscore=0;
}
class peddle {
private:
    Vector2 positions;
    float paddleWidth;
    float paddleHeight;
    float paddleSpeed;

public:
    peddle(Vector2 val1 = {0, 0}, float val2 = 0.0f, float val3 = 0.0f, float val4 = 0.0f)
        : positions(val1), paddleWidth(val2), paddleHeight(val3), paddleSpeed(val4) {}

    void Move(int direction) {
        if (direction == 1 && positions.y + paddleHeight + paddleSpeed <= GetScreenHeight()) {
            positions.y += paddleSpeed;
        } else if (direction == 2 && positions.y - paddleSpeed >= 0) {
            positions.y -= paddleSpeed;
        }
    }

    void Draw() const {
        DrawRectangleV(positions, {paddleWidth, paddleHeight}, WHITE);
    }

    Rectangle GetBounds() const {
        return {positions.x, positions.y, paddleWidth, paddleHeight};
    }
};

class ball {
private:
    float ballRadius;
    Vector2 ballPosition;
    Vector2 ballSpeed;

public:
    ball(float val1, Vector2 pos, Vector2 spe)
        : ballRadius(val1), ballPosition(pos), ballSpeed(spe) {}

    ball() : ballRadius(8.0f), ballPosition({400, 400}), ballSpeed({300, 300}) {}

    void Update(float deltaTime, const peddle& p1, const peddle& p2) {
      
        ballPosition.x += ballSpeed.x * deltaTime;
        ballPosition.y += ballSpeed.y * deltaTime;

       
        if (ballPosition.y - ballRadius <= 0 || ballPosition.y + ballRadius >= GetScreenHeight()) {
            ballSpeed.y = -ballSpeed.y; 
        }

       
        if (CheckCollisionCircleRec(ballPosition, ballRadius, p1.GetBounds()) ||
            CheckCollisionCircleRec(ballPosition, ballRadius, p2.GetBounds())) {
            ballSpeed.x = -ballSpeed.x;
        }

       
        if(ballPosition.x + ballRadius >= GetScreenWidth())
        {
            score::lscore++;
            ballPosition = {400, 400}; 
            ballSpeed = {300, 300};    
        }
        if (ballPosition.x - ballRadius <= 0) {
            score::rscore++;
            ballPosition = {400, 400}; 
            ballSpeed = {300, 300};    
        }
    }

    void Draw() const {
        DrawCircleV(ballPosition, ballRadius, WHITE);
    }
};

class game {
private:
    Texture2D background;
    peddle p1, p2;
    ball b;
    

public:
    game()
        : p1({30, 800 / 2.0f - 75}, 10.0f, 150.0f, 5.0f),
          p2({800 - 40, 800 / 2.0f - 75}, 10.0f, 150.0f, 5.0f),
          b(8.0f, {400, 400}, {300, 300}) {
        InitWindow(800, 800, "Pong");

       
        Image img = LoadImage("qq.jpg");
        ImageResize(&img, 1000, 800);
        background = LoadTextureFromImage(img);
        UnloadImage(img); 
        SetTargetFPS(60);
    }

    ~game() {
        UnloadTexture(background);
        CloseWindow();
    }

    void Run() {
        InitAudioDevice();
	    Music a =LoadMusicStream("song.ogg");
            PlayMusicStream(a);   
        while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime();
             UpdateMusicStream(a);
          
            if (IsKeyDown(KEY_W)) p1.Move(2);
            if (IsKeyDown(KEY_S)) p1.Move(1);
            if (IsKeyDown(KEY_UP)) p2.Move(2);
            if (IsKeyDown(KEY_DOWN)) p2.Move(1);

          
            b.Update(deltaTime, p1, p2);
            //Music a =LoadMusicStream("song.ogg");
            //PlayMusicStream(a);
           
            BeginDrawing();
            ClearBackground(BLACK);

           
            DrawTexture(background, 0, 0, WHITE);
           
            char lscoreText[10];
            char rscoreText[10];
            snprintf(lscoreText, sizeof(lscoreText), "%d", score::lscore);
            snprintf(rscoreText, sizeof(rscoreText), "%d", score::rscore);

  
            DrawText(lscoreText, 10, 10, 50, BLACK);
            DrawText(rscoreText, 740, 10, 50, BLACK); 


      
            p1.Draw();
            p2.Draw();
            b.Draw();

            EndDrawing();
        }
    }
};

int main() {
    game pongGame;
    pongGame.Run();
    return 0;
}
