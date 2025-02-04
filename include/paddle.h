#pragma once
#include <state.h>

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;

    Paddle(State&);

    void draw();
    void update();
protected:
    void limitMovement();
    State& state;
};

class AiPaddle: public Paddle {
public:
    AiPaddle(State&);
    void update(int ball_y);
};
