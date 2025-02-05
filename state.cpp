#include <constants.h>
#include <state.h>

bool State::IsGameOver(void) {
    return player1_score >= WINNING_SCORE || player2_score >= WINNING_SCORE;
}
