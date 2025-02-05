#pragma once

enum Screen {
    EnterUsername,
    GameSelection,
    Pong,
};

class State {
public:
    bool isPaused = false;
    int player1_score = 0, player2_score = 0;

    // Whether the ball respawn in the middle on scoring
    bool respawnMiddle = true;

    Screen currentScreen = EnterUsername;

    bool IsGameOver(void);
};

