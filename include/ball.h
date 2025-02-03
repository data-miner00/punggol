#pragma once

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void draw();
    void update();
    void reset();
};

