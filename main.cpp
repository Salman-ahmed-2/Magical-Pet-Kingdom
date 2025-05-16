



// From main.cpp
// Player
// Attributes:
// string player_name (private)
// int age (private)
// int level (private)
// Methods:
// Player(string player_name, int age, int level) (constructor)
// void set_player_name(string player_name)
// string get_player_name()
// void set_age(int age)
// int get_age()
// void set_level(int level)
// int get_level()
// void display_pet_info()
// Relationships:
// Associated with Game, GameManager, Training.
















#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include"minigame.h"
#include"shop.h"
#include"fight.h"
#include"leader.h"

using namespace std;
using namespace sf;

int currentScreen=0;
int selectedPetType=1;
bool choosingPet=false;
int coin=0;

class Player {
    string player_name;
    int age;
    int level;
public:
    Player(string player_name, int age, int level):player_name(player_name),age(age),level(level) {}
    void set_player_name(string player_name) 
    { this->player_name=player_name; }
    string get_player_name() 
    { return player_name; }
    void set_age(int age) 
    { this->age=age; }
    int get_age()
     { return age; }
    void set_level(int level) 
    { this->level=level; }
    int get_level() 
    { return level; }
    void display_pet_info() {
        cout<<"Player Name: "<<player_name<<endl;
        cout<<"Age: "<<age<<endl;
        cout<<"Level: "<<level<<endl;
    }
};

void display_menu(const string &, const Font &, RenderWindow &);
void display_shop_info(const string &, Font &, RenderWindow &, Event &, int &, Item);
void display_pet_selection_screen(RenderWindow &, const Font &, string &, string &, Event &, int &, int &, bool &);

int main() {
    Player player("salman",1,1);
    
    RenderWindow window(VideoMode(1920, 1000),"Magical Pet Game",Style::Fullscreen);
    GameManager lead(window);
    srand(static_cast<unsigned>(time(nullptr)));
    Item item[5];
    Game game(window);
    Training mini;

    string input;
    string errorMessage;
    Font font;
    if (!font.loadFromFile("hello.ttf")) {
        cout<<"Failed to load font! Exiting..."<<endl;
        return -1;
    }

    Music backgroundMusic;
    if (!backgroundMusic.openFromFile("entry.ogg")) {
        cerr<<"Failed to load background music."<<endl;
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(50);
    }

    auto playMusicIfNeeded=[&]() {
        if ((currentScreen==0)&&backgroundMusic.getStatus()!=Music::Playing) {
            backgroundMusic.play();
        } else if (currentScreen!=0&&backgroundMusic.getStatus()==Music::Playing) {
            backgroundMusic.stop();
        }
    };





    Music backgroundMusic1;
    if (!backgroundMusic1.openFromFile("entry.ogg")) {
        cerr<<"Failed to load background music." << endl;
    } else {
        backgroundMusic.setLoop(true);
        backgroundMusic1.setVolume(50);
    }

    auto playMusicIfNeeded1=[&]() {
        if ((currentScreen==2||currentScreen==5)&&backgroundMusic1.getStatus()!=Music::Playing) {
            backgroundMusic1.play();
        } else if (currentScreen != 2 && currentScreen != 5 && backgroundMusic1.getStatus()==Music::Playing) {
            backgroundMusic1.stop();
        }
    };


    while (window.isOpen()) {
        Event event;
        playMusicIfNeeded();
        playMusicIfNeeded1();
        while (window.pollEvent(event)) {
            if (event.type==Event::Closed) {
                window.close();
            }
            if (event.type==Event::TextEntered&&(currentScreen==0||currentScreen==50)) {
                if (event.text.unicode=='\b'&&!input.empty()) {
                    input.pop_back();
                } else if (event.text.unicode >= 32 && event.text.unicode <= 126) {
                    input+=static_cast<char>(event.text.unicode);
                }
            }
            if (event.type==Event::KeyPressed && event.key.code == Keyboard::Enter && !input.empty()) {
                if (currentScreen==0) {
                    try {
                        int choice = stoi(input);
                        input.clear();
                        switch (choice) {
                            case 1: currentScreen=1; 
                            break;
                            case 2: currentScreen=2; 
                            break;
                            case 3: currentScreen=3; 
                            break;
                            case 4: currentScreen=4; 
                            break;
                            case 5: currentScreen=50; 
                            choosingPet = true; 
                            break;
                            case 6: currentScreen=6; 
                            break;
                            case 7: window.close(); 
                            break;
                            default: cout<<"Invalid choice."<<endl;
                        }
                    } catch (...) {
                        cout << "Invalid input." << endl;
                        input.clear();
                    }
                } else if (currentScreen==50) {
                    try {
                        int petChoice=stoi(input);
                        if (petChoice>=1&&petChoice<=4) {
                            selectedPetType=petChoice;
                            input.clear();
                            choosingPet=false;
                            errorMessage.clear();
                            currentScreen=5;
                        } else {
                            errorMessage="Invalid choice. Enter 1-4.";
                            input.clear();
                        }
                    } catch (...) {
                        errorMessage="Please enter a number (1-4).";
                        input.clear();
                    }
                }
            }
            if (event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape) {
                currentScreen=0;
                choosingPet=false;
                input.clear();
                errorMessage.clear();
            }
        }

        window.clear();
        if (currentScreen==0) {
            display_menu(input,font,window);
        } else if (currentScreen==1) {
            lead.run();
        } else if (currentScreen==2) {
              game.run(selectedPetType);
           
        } else if (currentScreen==3) {
            
          
            mini_g(mini,input,font,window,event,currentScreen);
           

} else if (currentScreen==5) {
            game.run(selectedPetType);
        } else if (currentScreen==6) {
            display_shop_info(input, font, window, event, currentScreen, item);
        } else if (currentScreen==50) {
            display_pet_selection_screen(window, font, input, errorMessage, event, selectedPetType, currentScreen, choosingPet);
        }
        window.display();
    }

    return 0;
}

void display_menu(const string &input, const Font &font, RenderWindow &window) {
    Texture background_texture;
    if (!background_texture.loadFromFile("bio.png")) {
        cerr << "Failed to load background!" << endl;
        return;
    }
    Sprite background(background_texture);
    background.setPosition(0, 0);
    float scaleX=static_cast<float>(window.getSize().x)/background.getLocalBounds().width;
    float scaleY=static_cast<float>(window.getSize().y)/background.getLocalBounds().height;
    background.setScale(scaleX, scaleY);

    const int NUM_OPTIONS=8;
    RectangleShape buttons[NUM_OPTIONS];
    Text buttonTexts[NUM_OPTIONS];
    string labels[NUM_OPTIONS]={"Magical Pet Kingdom","1. Leader board","2. 1 v 1 ","3. Training Camp","4. Guild Management", "5. Arena Battles", "6. Shop", "7. Exit"};

    for (int i=0; i<NUM_OPTIONS; ++i) {
        buttons[i].setSize(Vector2f(i==0?460:400,i==0?60:50));
        buttons[i].setFillColor(Color::Black);
        buttons[i].setPosition(760,230+i*70);
        buttonTexts[i].setFont(font);
        buttonTexts[i].setCharacterSize(i==0?50:40);
        buttonTexts[i].setFillColor(Color::Red);
        buttonTexts[i].setString(labels[i]);
        buttonTexts[i].setPosition(780,230+i*70);
    }

    RectangleShape enter_choice_button(Vector2f(400, 50));
    enter_choice_button.setFillColor(Color::Black);
    enter_choice_button.setPosition(760,850);
    Text inputText("Enter your choice ->",font,40);
    inputText.setFillColor(Color::Red);
    inputText.setPosition(780,850);
    Text userInput(input, font,44);
    userInput.setFillColor(Color::Red);
    userInput.setPosition(1130,850);

    window.clear();
    window.draw(background);
    for (int i=0; i<NUM_OPTIONS; ++i) {
        window.draw(buttons[i]);
        window.draw(buttonTexts[i]);
    }
    window.draw(enter_choice_button);
    window.draw(inputText);
    window.draw(userInput);
}

void display_pet_selection_screen(RenderWindow &window, const Font &font, string &input, string &errorMessage, Event &event, int &selectedPetType, int &currentScreen, bool &choosingPet) {
    Texture background_texture;
    if (!background_texture.loadFromFile("bio.png")) {
        cerr<<"Failed to load background!"<<endl;
        return;
    }
    Sprite background(background_texture);
    background.setPosition(0,0);
    float scaleX=static_cast<float>(window.getSize().x)/background.getLocalBounds().width;
    float scaleY=static_cast<float>(window.getSize().y)/background.getLocalBounds().height;
    background.setScale(scaleX,scaleY);

    RectangleShape p2(Vector2f(400,100));
    p2.setFillColor(Color::Black);
    p2.setPosition(1000,250);
    Text pt2("1. DRAGON",font,70);
    pt2.setFillColor(Color::Red);
    pt2.setPosition(1000,250);

    RectangleShape p1(Vector2f(400, 100));
    p1.setFillColor(Color::Black);
    p1.setPosition(1500, 250);
    Text pt1("2. PHOENIX", font, 70);
    pt1.setFillColor(Color::Blue);
    pt1.setPosition(1500, 250);

    RectangleShape p3(Vector2f(400, 100));
    p3.setFillColor(Color::Black);
    p3.setPosition(1500, 750);
    Text pt3("3. GRIFFIN", font, 70);
    pt3.setFillColor(Color::Yellow);
    pt3.setPosition(1500, 750);

    RectangleShape p4(Vector2f(400, 100));
    p4.setFillColor(Color::Black);
    p4.setPosition(1000, 750);
    Text pt4("4. UNICORN", font, 70);
    pt4.setFillColor(Color::Green);
    pt4.setPosition(1000, 750);

    Text inputText("Choice: "+input, font, 30);
    inputText.setFillColor(Color::Green);
    inputText.setPosition(100, 350);

    if (!errorMessage.empty()) {
        Text errorText("Error: "+errorMessage, font, 24);
        errorText.setFillColor(Color::Red);
        errorText.setPosition(100, 400);
        window.draw(errorText);
    }

    window.clear();
    window.draw(background);
    window.draw(p1);
     window.draw(pt1);
    window.draw(p2);
     window.draw(pt2);
    window.draw(p3); 
    window.draw(pt3);
    window.draw(p4); 
    window.draw(pt4);
    window.draw(inputText);
}