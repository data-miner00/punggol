#include <paddle.h>
#include <raylib.h>
#include <state.h>

Paddle::Paddle(State& state) : state(state) {}

void Paddle::draw() {
    DrawRectangle(x, y, width, height, WHITE);
}

void Paddle::update() {
    if (state.isPaused) {
        return;
    }

    if (IsKeyDown(KEY_UP)) {
        y -= speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        y += speed;
    }
    limitMovement();
}

void Paddle::limitMovement() {
    if (y <= 0) {
        y = 0;
    }
    if (y >= GetScreenHeight() - height) {
        y = GetScreenHeight() - height;
    }
}

AiPaddle::AiPaddle(State& state) : Paddle(state) {}

void AiPaddle::update(int ball_y) {
    if (state.isPaused) {
        return;
    }

    if (y + height / 2 > ball_y) {
        y -= speed;
    }
    else {
        y += speed;
    }
    limitMovement();
}

