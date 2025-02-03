#include <iostream>
#include <raylib.h>
#include <constants.h>
#include <paddle.h>
#include <ball.h>

int player1_score = 0, player2_score = 0;

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    Ball ball;
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.radius = BALL_RADIUS;
    ball.speed_x = BALL_SPEED_X;
    ball.speed_y = BALL_SPEED_Y;

    AiPaddle player1;
    player1.x = 10;
    player1.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player1.width = PADDLE_WIDTH;
    player1.height = PADDLE_HEIGHT;
    player1.speed = PLAYER1_PADDLE_SPEED;

    Paddle player2;
    player2.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player2.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player2.width = PADDLE_WIDTH;
    player2.height = PADDLE_HEIGHT;
    player2.speed = PLAYER2_PADDLE_SPEED;

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

        int player1_score_text_width = MeasureText(TextFormat("Player 1: %i", player1_score), SCORE_FONT_SIZE);
        int player2_score_text_width = MeasureText(TextFormat("Player 2: %i", player2_score), SCORE_FONT_SIZE);

        DrawText(TextFormat("Player 1: %i", player1_score), SCREEN_WIDTH / 4 - player1_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);
        DrawText(TextFormat("Player 2: %i", player2_score), SCREEN_WIDTH * 3 / 4 - player2_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
