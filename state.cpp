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
