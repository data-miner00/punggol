#pragma once
#include <raylib.h>

enum Screen {
    EnterUsername,
    GameSelection,
    Pong,
};

enum ButtonState {
    Normal,
    Hover,
    Pressed,
};

class State {
public:
    bool isPaused = false;
    int player1_score = 0, player2_score = 0;

    // Whether the ball respawn in the middle on scoring
    bool respawnMiddle = true;

    Screen currentScreen = EnterUsername;
    Color ballColor = WHITE;

    long pausedTimestamp = 0;
    bool blinkShow = true;
    bool aiMode = false;

    Vector2 mousePoint = { .0f, .0f };
public:
    bool IsGameOver(void);
    void AdvanceScreen(void);

    void drawPlayer1Score(const char * name);
    void drawPlayer2Score(const char * name);
    void displayGamePaused(void);
};

