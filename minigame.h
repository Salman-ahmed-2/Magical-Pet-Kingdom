


// From minigame.h
// Training
// Attributes:
// None explicitly defined (but manipulates int** A dynamically).
// Methods:
// int** allocateGrid(int row, int col)
// void cleanupGrid(int** A, int row)
// void initGrid(int** A, int row, int col)
// bool canMove(int** A, int row, int col, int prow, int pcol)
// void handleInput(Event& event, int** A, int row, int col, int& prow, int& pcol, int& score)
// void drawGrid(RenderWindow& window, int** A, int row, int col, Text& scoreText, int score)
// bool loadFont(Font& font)
// Text createScoreText(Font& font, int row)
// Relationships:
// Uses SFML classes (RenderWindow, Event, Font, Text).
// Associated with mini_g function.





































#ifndef MINIGAME_H
#define MINIGAME_H

#include<iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string.h>
using namespace sf;
using namespace std;

#define CELL_SIZE  50

class Training {
    public:

int **allocateGrid(int row, int col) {
    int **A = new int*[row];
    for (int i = 0; i < row; ++i)
        A[i] = new int[col];
    return A;
}

void cleanupGrid(int **A, int row) {
    for (int i = 0; i < row; ++i)
        delete[] A[i];
    delete[] A;
}

void initGrid(int **A, int row, int col) {
    srand(time(0));
    do {
        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j)
                A[i][j] = -1 + rand() % 3;  // Values: -1, 0, 1
    } while (A[0][0] == -1);
    A[0][0] = 8;
}

bool canMove(int **A, int row, int col, int prow, int pcol) {
    if (prow + 1 < row && (A[prow + 1][pcol] == 0 || A[prow + 1][pcol] == 1)) return true;
    if (prow - 1 >= 0 && (A[prow - 1][pcol] == 0 || A[prow - 1][pcol] == 1)) return true;
    if (pcol + 1 < col && (A[prow][pcol + 1] == 0 || A[prow][pcol + 1] == 1)) return true;
    if (pcol - 1 >= 0 && (A[prow][pcol - 1] == 0 || A[prow][pcol - 1] == 1)) return true;
    return false;
}

void handleInput(Event &event, int **A, int row, int col, int &prow, int &pcol, int &score) {
    int newRow = prow, newCol = pcol;

    if (event.key.code == Keyboard::Up) newRow--;
    else if (event.key.code == Keyboard::Down) newRow++;
    else if (event.key.code == Keyboard::Left) newCol--;
    else if (event.key.code == Keyboard::Right) newCol++;

    if (newRow >= 0 && newRow < row && newCol >= 0 && newCol < col &&
        (A[newRow][newCol] == 0 || A[newRow][newCol] == 1)) {
        prow = newRow;
        pcol = newCol;
        A[prow][pcol] = 8;
        score++;
    }
}

void drawGrid(RenderWindow &window, int **A, int row, int col, Text &scoreText, int score) {
    window.clear();

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            RectangleShape cell(Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            cell.setPosition(j * CELL_SIZE, i * CELL_SIZE);

            if (A[i][j] == -1)
                cell.setFillColor(Color::Black);
            else if (A[i][j] == 0 || A[i][j] == 1)
                cell.setFillColor(Color::White);
            else if (A[i][j] == 8)
                cell.setFillColor(Color::Red);

            window.draw(cell);
        }
    }

    scoreText.setString("Score: " + to_string(score));
    window.draw(scoreText);
    window.display();
}

bool loadFont(Font &font) {
    return font.loadFromFile("hello.ttf");
}

Text createScoreText(Font &font, int row) {
    Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setPosition(10, row * CELL_SIZE + 10);
    scoreText.setFillColor(Color::White);
    return scoreText;






    
}};

extern Training mini;
extern int currentScreen;


void mini_g(Training &mini,const string &input, Font &font, RenderWindow &window, Event &event,int & currentScreen);

#endif
















