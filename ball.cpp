#include <ball.h>
#include <raylib.h>
#include <state.h>

Ball::Ball(State& state) : state(state) {}
// Ball::Ball(State& state) {
//     this->state = state;
// }

void Ball::draw() {
    DrawCircle(this->x, this->y, this->radius, WHITE);
}

void Ball::update() {
    if (state.isPaused) {
        return;
    }

    x += speed_x;
    y += speed_y;

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speed_y *= -1;
    }
    if (x + radius >= GetScreenWidth()) {
        state.player1_score++;
        speed_x *= -1;
    } else if (x - radius <= 0) {
        state.player2_score++;
        speed_x *= -1;
    }
}

void Ball::reset() {
    x = GetScreenWidth() / 2 - radius;
    y = GetScreenHeight() / 2 - radius;

    int speed_choices[2] = {-1, 1};
    speed_x *= speed_choices[GetRandomValue(0, 1)];
    speed_y *= speed_choices[GetRandomValue(0, 1)];
}

