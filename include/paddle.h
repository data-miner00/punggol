#pragma once
#include <iostream>
#include <state.h>
#include <string>

class Paddle {
public:
    float x, y;
    float width, height;
    int speed;
    std::string name;
    int highScore = 0;


    Paddle(State&);

    void draw();
    void update();

    friend std::istream& operator >> (std::istream&, Paddle&);
    friend std::ostream& operator << (std::ostream&, const Paddle&);
protected:
    void limitMovement();
    State& state;
};

class AiPaddle: public Paddle {
public:
    AiPaddle(State&);
    void update(int ball_y);
};
