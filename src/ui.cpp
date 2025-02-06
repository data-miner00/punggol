#include <ui.h>
#include <raylib.h>
#include <constants.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

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
    return GuiTextInputBox(nbounds, input_box_title, input_box_text, input_box_button, name, 255, &secret_view);
}

void DrawGameOver() {
    const int font_size = 50;
    int label_width = MeasureText(game_over, font_size);
    DrawText(game_over, SCREEN_WIDTH / 2 - label_width / 2, SCREEN_HEIGHT / 2 - font_size / 2, 50, WHITE);
}

