#pragma once
#include <state.h>
#include <raylib.h>

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;
    Color color;

    Ball(State&, Color);

    void draw();
    void update();
    void reset();
private:
    State& state;
};

