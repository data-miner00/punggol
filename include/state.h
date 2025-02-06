#pragma once
#include <raylib.h>
#include <string>

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

public:
    bool IsGameOver(void);
    void AdvanceScreen(void);

    void LoadUserAsPlayer2(std::string name);
    void SaveUserData(std::string name, int score);
};

