#include <raylib.h>
#include <constants.h>
#include <paddle.h>
#include <ball.h>
#include <state.h>
#include <macros.h>
#include <ui.h>
#include <cstring>
#include <raygui.h>

#define MAX_INPUT_CHARS 100


int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My punggol game");
    SetTargetFPS(FPS);
    SetExitKey(KEY_Q);

    State state;

    Ball ball{ state, WHITE };

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

    int letterCount = 0;

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
            state.mousePoint = GetMousePosition();

            int name_width = MeasureText("Punggol", 100);
            DrawText("Punggol", float(SCREEN_WIDTH) / 2 - float(name_width) / 2, 100, 100, WHITE);

            float menu_box_x = float(SCREEN_WIDTH) / 2 - 125. / 2;
            float menu_box_y = float(SCREEN_HEIGHT) / 8 - 30. / 2 + 150;

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 50, 125, 30 }, GuiIconText(1, "Respawn in center"))) {
                state.respawnMiddle = !state.respawnMiddle;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 2 * 50, 125, 30 }, GuiIconText(2, "Ball speed"))) {
                ball.speed_x = 20;
                ball.speed_y = 20;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 3 * 50, 125, 30 }, GuiIconText(3, "Paddle width"))) {
                player2.height = 200;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 4 * 50, 125, 30 }, GuiIconText(4, "Max score wins"))) {
                state.maxScoreWins = !state.maxScoreWins;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 5 * 50, 125, 30 }, GuiIconText(5, "Green ball"))) {
                ball.color = GREEN;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 6 * 50, 125, 30 }, GuiIconText(6, "Blue ball"))) {
                ball.color = BLUE;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 7 * 50, 125, 30 }, GuiIconText(7, "Start!"))) {
                state.AdvanceScreen();
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 8 * 50, 125, 30 }, GuiIconText(8, "Exit"))) {
                break;
            }

            if (GuiButton((Rectangle){ float(SCREEN_WIDTH) / 2 - 125. / 2, menu_box_y + 9 * 50, 125, 30 }, GuiIconText(9, "AI mode"))) {
                state.aiMode = !state.aiMode;
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

        state.drawPlayer1Score("Player 1");
        state.drawPlayer2Score(name);

        if (state.isPaused) {
            state.displayGamePaused();
        }

        EndDrawing();
    }

    player2.saveData(state.player2_score);

    CloseWindow();
    return 0;
}
