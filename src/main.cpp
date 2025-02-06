#include <raylib.h>
#include <constants.h>
#include <paddle.h>
#include <ball.h>
#include <state.h>
#include <macros.h>
#include <ui.h>
#include <cstring>


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    State state;

    Ball ball{ state, WHITE };
    ball.x = float(SCREEN_WIDTH) / 2;
    ball.y = float(SCREEN_HEIGHT) / 2;
    ball.radius = BALL_RADIUS;
    ball.speed_x = BALL_SPEED_X;
    ball.speed_y = BALL_SPEED_Y;

    AiPaddle player1{ state };
    player1.x = 10;
    player1.y = float(SCREEN_HEIGHT) / 2 - float(PADDLE_HEIGHT) / 2;
    player1.width = PADDLE_WIDTH;
    player1.height = PADDLE_HEIGHT;
    player1.speed = PLAYER1_PADDLE_SPEED;

    Paddle player2{ state };
    player2.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player2.y = float(SCREEN_HEIGHT) / 2 - float(PADDLE_HEIGHT) / 2;
    player2.width = PADDLE_WIDTH;
    player2.height = PADDLE_HEIGHT;
    player2.speed = PLAYER2_PADDLE_SPEED;

    AiPaddle player3{ state };
    player3.x = SCREEN_WIDTH - PADDLE_WIDTH - 10;
    player3.y = float(SCREEN_HEIGHT) / 2 - float(PADDLE_HEIGHT) / 2;
    player3.width = PADDLE_WIDTH;
    player3.height = PADDLE_HEIGHT;
    player3.speed = PLAYER2_PADDLE_SPEED;

    char name[255];
    int text_input_result = -1;

    Rectangle selectGreenButton = { float(SCREEN_WIDTH) / 4 - 300. / 2, float(SCREEN_HEIGHT) / 2 - 150. / 2, 300, 150 };
    Rectangle selectBlueButton = { float(SCREEN_WIDTH)  * 3 / 4 - 300. / 2, float(SCREEN_HEIGHT) / 2 - 150. / 2, 300, 150 };

    int btnState = Normal;
    bool btnAction = false, btnAction2 = false;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) {
            state.isPaused = !state.isPaused;
        }

        BeginDrawing();

        ClearBackground(BLACK);

        // First screen
        if (text_input_result == -1) {
            text_input_result = GetNameFromUser(name);
            EndDrawing();

            if (text_input_result == 1) {
                strcpy(player2.name, name);
                player2.loadDataFromFile();
                state.AdvanceScreen();
            }

            continue;
        }

        // Second screen
        if (state.currentScreen == GameSelection) {
            DrawRectangleRec(selectGreenButton, GREEN);
            DrawRectangleRec(selectBlueButton, BLUE);

            state.mousePoint = GetMousePosition();
            btnAction = false;

            // Check button state
            if (CheckCollisionPointRec(state.mousePoint, selectGreenButton))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = Pressed;
                else btnState = Hover;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction = true;
            }
            else btnState = Normal;

            if (btnAction)
            {
                ball.color = GREEN;
                state.AdvanceScreen();
            }

            if (CheckCollisionPointRec(state.mousePoint, selectBlueButton))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) btnState = Pressed;
                else btnState = Hover;

                if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) btnAction2 = true;
            }
            else btnState = Normal;

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
            DrawGameOver();
        }

        ball.update();
        player1.update(ball.y);

        if (!state.aiMode) {
            player2.update();
        } else {
            player3.update(ball.y);
        }

        if (player1.checkCollisionWithBall(ball)) {
            ball.speed_x *= -1;
        }

        if (!state.aiMode) {
            if (player2.checkCollisionWithBall(ball)) {
                ball.speed_x *= -1;
            }
        } else {
            if (player3.checkCollisionWithBall(ball)) {
                ball.speed_x *= -1;
            }
        }

        DrawLine(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT, WHITE);

        ball.draw();
        player1.draw();

        if (!state.aiMode) {
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

        if (state.isPaused) {
            state.pausedTimestamp++;
            if (state.pausedTimestamp % 60 == 0) {
                state.blinkShow = !state.blinkShow;
            }
            if (state.blinkShow) {
                int pause_width = MeasureText("PAUSED", 40);
                DrawText("PAUSED", SCREEN_WIDTH / 2 - pause_width / 2, SCREEN_HEIGHT / 2 - 40 / 2, 40, WHITE);
            }
        }

        EndDrawing();
    }

    player2.saveData(state.player2_score);

    CloseWindow();
    return 0;
}
