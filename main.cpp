#include <iostream>
#include <raylib.h>
#include <constants.h>
#include <paddle.h>
#include <ball.h>
#include <state.h>
#include <string>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    State state;

    Ball ball{ state };
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

    char name[255];
    Rectangle nbounds = { SCREEN_WIDTH / 2 - 700 / 2, SCREEN_HEIGHT / 2 - 300 / 2, 700, 300 };
    const char* title = "Player name";
    const char* text = "Enter your name";
    const char* button = "Ok";
    bool secret_view = false;
    bool in_menu = true;
    int text_input_result = -1;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (text_input_result == -1) {
            text_input_result = GuiTextInputBox(nbounds, title, text, button, name, 255, &secret_view);
            std::cout << text_input_result;
            EndDrawing();
            continue;
        }

        ball.update();
        player1.update(ball.y);
        player2.update();

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1;
        }
        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height})) {
            ball.speed_x *= -1;
        }

        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

        ball.draw();

        player1.draw();
        player2.draw();

        const char* player1_label = TextFormat("Player 1: %i", state.player1_score);
        const char* player2_label = TextFormat("%s: %i", name, state.player2_score);

        int player1_score_text_width = MeasureText(player1_label, SCORE_FONT_SIZE);
        int player2_score_text_width = MeasureText(player2_label, SCORE_FONT_SIZE);

        DrawText(player1_label, SCREEN_WIDTH / 4 - player1_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);
        DrawText(player2_label, SCREEN_WIDTH * 3 / 4 - player2_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);

        // respawn middle
        // acceleration
        // multi balls (how many)
        // extend length

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
