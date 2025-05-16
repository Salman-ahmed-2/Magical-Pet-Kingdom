#include "minigame.h"

extern int coin;
int score=0;
using namespace std;

void mini_g(Training &mini, const string &input, Font &font, RenderWindow &window, Event &event, int &currentScreen) {
    if (!font.loadFromFile("hello.ttf")) {
        cout<<"Failed to load font! ... Exiting ...."<<endl;
        return;
    }

    // menu elements
    RectangleShape exit_button(Vector2f(400, 50));
    exit_button.setFillColor(Color::Black);
    exit_button.setPosition(1100, 230);

    RectangleShape play_button(Vector2f(400, 50));
    play_button.setFillColor(Color::Black);
    play_button.setPosition(1100, 300);

    Text op_1("1. Exit", font, 50);
    op_1.setFillColor(Color::Red);
    op_1.setPosition(1100, 230);

    Text op_2("2. Play Again", font, 50);
    op_2.setFillColor(Color::Red);
    op_2.setPosition(1100, 300);

    Text inputText("Enter your choice ->", font, 40);
    inputText.setFillColor(Color::Red);
    inputText.setPosition(1100, 400);

    Text input_mini(input, font, 40);
    input_mini.setFillColor(Color::Red);
    input_mini.setPosition(290, 320);

    currentScreen = 2; // Start game

    do {
        bool gameOver = false;
        // Game initialization
        Text scoreText = mini.createScoreText(font, 10);
        scoreText.setPosition(1000, 10);

        int row=20, col=10;
        int prow=0, pcol = 0;
        score=0; // reset score
        int** A=mini.allocateGrid(row, col);
        mini.initGrid(A, row, col);

        // game loop
        while (window.isOpen() && !gameOver) {
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    mini.cleanupGrid(A, row); // Clean up before closing
                    window.close();
                    return;
                }

                if (event.type==Event::KeyPressed&&!gameOver) {
                    mini.handleInput(event, A, row, col, prow, pcol, score);
                }
            }

            // check for game over
            if (!mini.canMove(A, row, col, prow, pcol)) {
                cout<<"No more moves! Final Score: "<<score<<endl;
                coin+=score; // update coin
                gameOver=true;
            }

            // draw game
            window.clear();
            mini.drawGrid(window, A, row, col, scoreText, score);
            window.display();
        }

        // clean up grid
        mini.cleanupGrid(A, row);

        // game over menu loop
        bool menuActive=true;
        while (window.isOpen()&&menuActive) {
            while (window.pollEvent(event)) {
                if (event.type==Event::Closed) {
                    window.close();
                    return;
                }

                if (event.type==Event::KeyPressed) {
                    if (event.key.code==Keyboard::Num1) {
                        currentScreen=0; // Exit to main menu
                        menuActive=false;
                    } else if (event.key.code==Keyboard::Num2) {
                        currentScreen=2; // Restart game
                        menuActive=false;
                    }
                }
            }

            // Draw menu
            window.clear();
            window.draw(exit_button);
            window.draw(play_button);
            window.draw(op_1);
            window.draw(op_2);
            window.draw(inputText);
            window.draw(input_mini);
            window.display();
        }

    } while (currentScreen==2);
}