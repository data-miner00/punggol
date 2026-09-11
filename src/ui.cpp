#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include "constants.h"
#include "ui.h"

// Text input to get user name
const char* input_box_title = "Player name";
const char* input_box_text = "Enter your name";
const char* input_box_button = "Ok";

// Selection
const char* select_color = "Select ball color";

const char* game_over = "Game Over";

bool secret_view = false;
Rectangle nbounds = { float(SCREEN_WIDTH) / 2 - 700. / 2, float(SCREEN_HEIGHT) / 2 - 300. / 2, 700, 300 };

int GetNameFromUser(char* name) {
    int btnActive = 0;
    int result = GuiTextInputBox(nbounds, input_box_title, input_box_text, name, 255, input_box_button, &btnActive, &secret_view);

    // GuiTextInputBox() now returns RESULT_PRESSED (1) for ANY interaction that
    // closes the box (a listed button OR the window's own close icon), and
    // reports which one via btnActive: 0 = closed via the window's close icon,
    // 1..n = index into the ';'-separated btnText list. We only have one
    // button ("Ok"), so btnActive doubles as our old-style result code.
    if (result == RESULT_NONE) return -1;
    return btnActive;
}
void DrawGameOver() {
    const int font_size = 50;
    int label_width = MeasureText(game_over, font_size);
    DrawText(game_over, SCREEN_WIDTH / 2 - label_width / 2, SCREEN_HEIGHT / 2 - font_size / 2, 50, WHITE);
}

// I forgot why I add these but anyways
const char* green_label = "Green";
const char* blue_label = "Blue";
const char* red_label = "Red";

Rectangle multiBallCheckboxBound = { };
Rectangle enableMaxScoreCheckboxBound = { };

const char* multiBallCheckboxLabel = "Enable multiple balls";
const char* enableMaxScoreCheckboxLabel = "Enable max score";

