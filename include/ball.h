#pragma once
#include <state.h>

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    Ball(State&);

    void draw();
    void update();
    void reset();
private:
    State& state;
};

