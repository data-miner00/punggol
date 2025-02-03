#include <iostream>
#include <raylib.h>
#include <constants.h>

int player1_score = 0, player2_score = 0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void draw() {
        DrawCircle(this->x, this->y, this->radius, WHITE);
    }

    void update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth()) {
            player1_score++;
            speed_x *= -1;
        } else if (x - radius <= 0) {
            player2_score++;
            speed_x *= -1;
        }
    }
};

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;

    void draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }
        limitMovement();
    }
protected:
    void limitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y >= GetScreenHeight() - height) {
            y = GetScreenHeight() - height;
        }
    }
};

class AiPaddle: public Paddle {
public:
    void update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y -= speed;
        }
        else {
            y += speed;
        }
        limitMovement();
    }
};

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    Ball ball;
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.radius = 20;
    ball.speed_x = 7;
    ball.speed_y = 7;

    AiPaddle player1;
    player1.x = 10;
    player1.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player1.width = PADDLE_WIDTH;
    player1.height = PADDLE_HEIGHT;
    player1.speed = 6;

    Paddle player2;
    player2.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player2.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player2.width = PADDLE_WIDTH;
    player2.height = PADDLE_HEIGHT;
    player2.speed = 6;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ball.update();
        player1.update(ball.y);
        player2.update();

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height})) {
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);

        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

        ball.draw();

        player1.draw();
        player2.draw();

        int player1_score_text_width = MeasureText(TextFormat("Player 1: %i", player1_score), 30);
        int player2_score_text_width = MeasureText(TextFormat("Player 2: %i", player2_score), 30);

        DrawText(TextFormat("Player 1: %i", player1_score), SCREEN_WIDTH / 4 - player1_score_text_width / 2, 20, 30, WHITE);
        DrawText(TextFormat("Player 2: %i", player2_score), SCREEN_WIDTH * 3 / 4 - player2_score_text_width / 2, 20, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
