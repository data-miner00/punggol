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
