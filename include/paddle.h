#pragma once

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;

    void draw();
    void update();
protected:
    void limitMovement();
};

class AiPaddle: public Paddle {
public:
    void update(int ball_y);
};
