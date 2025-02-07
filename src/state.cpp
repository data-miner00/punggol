#include <raylib.h>
#include <constants.h>
#include <state.h>

bool State::IsGameOver(void) {
    return player1_score >= WINNING_SCORE || player2_score >= WINNING_SCORE;
}

void State::AdvanceScreen(void) {
    if (currentScreen == EnterUsername) {
        currentScreen = GameSelection;
    } else if (currentScreen == GameSelection) {
        currentScreen = Pong;
    }
}

void State::drawPlayer1Score(const char * name) {
    const char* player_label = TextFormat("%s: %i", name, player1_score);
    int label_width = MeasureText(player_label, SCORE_FONT_SIZE);
    DrawText(player_label, SCREEN_WIDTH / 4 - label_width / 2, 20, SCORE_FONT_SIZE, WHITE);
}

void State::drawPlayer2Score(const char * name) {
    const char* player_label = TextFormat("%s: %i", name, player2_score);
    int label_width = MeasureText(player_label, SCORE_FONT_SIZE);
    DrawText(player_label, SCREEN_WIDTH * 3 / 4 - label_width / 2, 20, SCORE_FONT_SIZE, WHITE);
}

void State::displayGamePaused() {
    pausedTimestamp++;
    if (pausedTimestamp % FPS == 0) {
        blinkShow = !blinkShow;
    }

    if (blinkShow) {
        const char * paused_text = "PAUSED";
        int font_size = 40;
        int pause_width = MeasureText(paused_text, font_size);

        DrawText(paused_text, SCREEN_WIDTH / 2 - pause_width / 2, SCREEN_HEIGHT / 2 - font_size / 2, font_size, WHITE);
    }
}
