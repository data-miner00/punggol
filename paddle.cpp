#include <paddle.h>
#include <raylib.h>
#include <state.h>
#include <iostream>
#include <fstream>
#include <string.h>

void concat(char* s1, char* s2, char* ns) {
    ns[0] = '\0';
    strcpy(ns, s1);
    strcat(ns, s2);
}

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

std::istream& operator >> (std::istream& in, Paddle& p) {
    in >> p.name;
    in >> p.highScore;
    in.ignore();
    return in;
}

std::ostream& operator << (std::ostream& out, const Paddle& p) {
    out << p.name << std::endl;
    out << p.highScore << std::endl;
    return out;
}

void Paddle::loadDataFromFile() {
    char txtExtension[] = ".txt";
    char saveFile[strlen(this->name) + strlen(txtExtension) + 1];
    concat(this->name, txtExtension, saveFile);
    std::ifstream inFile(saveFile);
    if (inFile.is_open()) {
        inFile >> this->highScore;
    }
    inFile.close();
}

void Paddle::saveData(int currentScore) {
    char txtExtension[] = ".txt";
    if (currentScore > this->highScore) {
        char saveFile[strlen(this->name) + strlen(txtExtension) + 1];
        concat(this->name, txtExtension, saveFile);
        std::ofstream outFile (saveFile);
        outFile << currentScore;
        outFile.close();
        TraceLog(LOG_INFO, "File saved");
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

