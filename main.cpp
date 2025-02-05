#include <iostream>
#include <raylib.h>
#include <constants.h>
#include <paddle.h>
#include <ball.h>
#include <state.h>
#include <fstream>
#include <macros.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    State state;

    Ball ball{ state, WHITE };
    ball.x = SCREEN_WIDTH / 2;
    ball.y = SCREEN_HEIGHT / 2;
    ball.radius = BALL_RADIUS;
    ball.speed_x = BALL_SPEED_X;
    ball.speed_y = BALL_SPEED_Y;

    AiPaddle player1{ state };
    player1.x = 10;
    player1.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player1.width = PADDLE_WIDTH;
    player1.height = PADDLE_HEIGHT;
    player1.speed = PLAYER1_PADDLE_SPEED;

    Paddle player2{ state };
    player2.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player2.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player2.width = PADDLE_WIDTH;
    player2.height = PADDLE_HEIGHT;
    player2.speed = PLAYER2_PADDLE_SPEED;

    AiPaddle player3{ state };
    player3.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player3.y = SCREEN_HEIGHT / 2 - PADDLE_HEIGHT / 2;
    player3.width = PADDLE_WIDTH;
    player3.height = PADDLE_HEIGHT;
    player3.speed = PLAYER2_PADDLE_SPEED;

    char name[255];
    Rectangle nbounds = { SCREEN_WIDTH / 2 - 700 / 2, SCREEN_HEIGHT / 2 - 300 / 2, 700, 300 };
    const char* title = "Player name";
    const char* text = "Enter your name";
    const char* button = "Ok";
    bool secret_view = false;
    bool in_menu = true;
    int text_input_result = -1;

    Rectangle selectGreenButton = { SCREEN_WIDTH / 4 - 300 / 2, SCREEN_HEIGHT / 2 - 150 / 2, 300, 150 };
    Rectangle selectBlueButton = { SCREEN_WIDTH  * 3 / 4 - 300 / 2, SCREEN_HEIGHT / 2 - 150 / 2, 300, 150 };

    int btnState = 0;               // Button state: 0-NORMAL, 1-MOUSE_HOVER, 2-PRESSED
    bool btnAction = false, btnAction2 = false;

    Vector2 mousePoint = { 0.0f, 0.0f };
    long timestamp = 0;
    bool blinkShow = true;
    // make togglable
    bool aiMode = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) {
            state.isPaused = !state.isPaused;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        if (text_input_result == -1) {
            text_input_result = GuiTextInputBox(nbounds, title, text, button, name, 255, &secret_view);
            EndDrawing();

            if (text_input_result == 1) {
                std::ifstream inFile(strcat(name, ".txt"));
                if (inFile.is_open()) {
                    inFile >> player2;
                    std::cout << "Player " << player2.name << " loaded with high score " << player2.highScore << ".\n";
                } else {
                    TraceLog(LOG_WARNING, "File not found");
                }

                inFile.close();
                state.AdvanceScreen();
            }

            continue;
        }

        if (state.currentScreen == GameSelection) {
            DrawRectangleRec(selectGreenButton, GREEN);
            DrawRectangleRec(selectBlueButton, BLUE);

            mousePoint = GetMousePosition();
            btnAction = false;

            // Check button state
            if (CheckCollisionPointRec(mousePoint, selectGreenButton))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
                else btnState = 1;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
            }
            else btnState = 0;

            if (btnAction)
            {
                ball.color = GREEN;
                state.AdvanceScreen();
            }

            if (CheckCollisionPointRec(mousePoint, selectBlueButton))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = 2;
                else btnState = 1;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction2 = true;
            }
            else btnState = 0;

            if (btnAction2)
            {
                ball.color = BLUE;
                state.AdvanceScreen();
            }

            EndDrawing();
            continue;
        }

        // todo: Freeze when game over
        if (state.IsGameOver()) {
            const char* game_over_label = "Game Over";
            int label_width = MeasureText(game_over_label, 50);

            DrawText(game_over_label, SCREEN_WIDTH / 2 - label_width / 2, SCREEN_HEIGHT / 2 - 25, 50, WHITE);
        }

        ball.update();
        player1.update(ball.y);

        if (!aiMode) {
            player2.update();
        } else {
            player3.update(ball.y);
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player1.x, player1.y, player1.width, player1.height})) {
            ball.speed_x *= -1;
        }

        if (!aiMode) {
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player2.x, player2.y, player2.width, player2.height})) {
                ball.speed_x *= -1;
            }
        } else {
            if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player3.x, player3.y, player3.width, player3.height})) {
                ball.speed_x *= -1;
            }
        }

        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

        ball.draw();
        player1.draw();

        if (!aiMode) {
            player2.draw();
        } else {
            player3.draw();
        }

        const char* player1_label = TextFormat("Player 1: %i", state.player1_score);
        const char* player2_label = TextFormat("%s: %i", name, state.player2_score);

        int player1_score_text_width = MeasureText(player1_label, SCORE_FONT_SIZE);
        int player2_score_text_width = MeasureText(player2_label, SCORE_FONT_SIZE);

        DrawText(player1_label, SCREEN_WIDTH / 4 - player1_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);
        DrawText(player2_label, SCREEN_WIDTH * 3 / 4 - player2_score_text_width / 2, 20, SCORE_FONT_SIZE, WHITE);

        // acceleration
        // multi balls (how many)
        // extend length

        if (state.isPaused) {
            timestamp++;
            if (timestamp % 60 == 0) {
                blinkShow = !blinkShow;
            }
            if (blinkShow) {
                int pause_width = MeasureText("PAUSED", 40);
                DrawText("PAUSED", SCREEN_WIDTH / 2 - pause_width / 2, SCREEN_HEIGHT / 2 - 40 / 2, 40, WHITE);
            }
        }

        EndDrawing();
    }

    // Save data
    if (state.player2_score > player2.highScore) {
        player2.highScore = state.player2_score;
        std::ofstream outFile (name);
        outFile << player2;
        outFile.close();
        std::cout << "File saved\n";
    }

    CloseWindow();

    return 0;
}
