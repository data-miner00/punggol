#pragma once

class State {
public:
    bool isPaused = false;
    int player1_score = 0, player2_score = 0;

    bool IsGameOver(void);
};

enum Screen {
    EnterUsername,
    GameSelection,
    Pong,
};

