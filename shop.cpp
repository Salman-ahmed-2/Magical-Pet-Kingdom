





// From shop.h and shop.cpp
// Shop
// Attributes: None (commented out int coins).
// Methods: None (commented out set_coin, get_coins).
// Item (inherits from Shop)
// Attributes:
// string name
// string type
// string effect
// int price
// int quantity
// Methods:
// Item() (default constructor)
// Item(string name, string type, string effect, int price, int quantity)
// string get_display_text()
// string get_name()
// string get_effect()
// int get_price()
// Relationships:
// Inherits from Shop.
// Used in display_shop_info function.
// Associated with SFML classes (Font, RenderWindow, Event).
















#include "shop.h"
#include<iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string.h>
using namespace sf;
using namespace std;






void display_shop_info(const string &input, Font &font, RenderWindow &window, Event &event, int &currentScreen, Item *items) {
   
    
 int player_currency=100000; 

   

    Texture potionTexture1; 
    Sprite potionSprite1;
    if (!potionTexture1.loadFromFile("p1.png")) {
        cerr<<"Failed to load image!"<<endl;
        return;
    }
    
    potionSprite1.setTexture(potionTexture1);
    potionSprite1.setPosition(300,250); 
    potionSprite1.setScale(0.5f,0.5f);
    
    Texture potionTexture2; 
    Sprite potionSprite2;
    if (!potionTexture2.loadFromFile("p2.png")) {
        cerr<<"Failed to load image!"<<endl;
        return;
    }
    
    potionSprite2.setTexture(potionTexture2);
    potionSprite2.setPosition(300,650); 
    potionSprite2.setScale(0.5f,0.5f);
    

    Texture potionTexture3; 
    Sprite potionSprite3;
    if (!potionTexture3.loadFromFile("p3.png")) {
        cerr<<"Failed to load image!"<<endl;
        return;
    }
    
    potionSprite3.setTexture(potionTexture3);
    potionSprite3.setPosition(1600,250); 
    potionSprite3.setScale(0.5f,0.5f);
    

    Texture potionTexture4; 
    Sprite potionSprite4;
    if (!potionTexture4.loadFromFile("p4.png")) {
        cerr<<"Failed to load image!"<<endl;
        return;
    }
    
    potionSprite4.setTexture(potionTexture4);
    potionSprite4.setPosition(1600,650); 
    potionSprite4.setScale(0.5f,0.5f);
    
    Texture background_texture;
    if (!background_texture.loadFromFile("bio.png"))
    {
        cerr<<"Failed to load background!"<<endl;
        return;
    }
    Sprite background(background_texture);
    background.setPosition(0,0);
    
    float scaleX=static_cast<float>(window.getSize().x)/background.getLocalBounds().width;
    float scaleY=static_cast<float>(window.getSize().y)/background.getLocalBounds().height;
    

    background.setScale(scaleX,scaleY);

    items[0]=Item("Healing Potion","Healing", "Restore 50 HP",50,3);
    items[1]=Item("Mana Potion","Mana","Restore 40 MP",30,2);
    items[2]=Item("Speed Buff","Buff","Boost Speed",75,1);
    items[3]=Item("Attack Buff","Buff","Boost Attack",100,1);
    items[4]=Item("Shield","Defense","Block Damage",120,2);

    Text item_texts[5];
    RectangleShape buttons[5];

    for (int i=0; i<5; ++i) {
        buttons[i].setSize(Vector2f(900,50));
        buttons[i].setPosition(600,250+i*120);
        buttons[i].setFillColor(Color::Black);

        item_texts[i].setFont(font);
        item_texts[i].setString(items[i].get_display_text());
        item_texts[i].setCharacterSize(35);
        item_texts[i].setPosition(600,250+i*120);
        item_texts[i].setFillColor(Color::Red);
    }


RectangleShape info_button(Vector2f(800,50));
    info_button.setFillColor(Color::Black);
    info_button.setPosition(610,820);

RectangleShape currency_button(Vector2f(600, 60));
    currency_button.setFillColor(Color::Black);
    currency_button.setPosition(1700,20);
    
    RectangleShape title_button(Vector2f(780, 60));
    title_button.setFillColor(Color::Black);    
    title_button.setPosition(700,20);
    
    Text info;
    info.setFont(font);
    info.setString("Click on option to select item");
    info.setCharacterSize(50);
    info.setPosition(610,820);
    info.setFillColor(Color::Red);
    

    Text title;
    title.setFont(font);
    title.setString("Welcome to Mystic Market!");
    title.setCharacterSize(50);
    title.setFillColor(Color::Red);
    title.setPosition(700,20);

    Text currency_display;
    currency_display.setFont(font);
    currency_display.setCharacterSize(40);
    currency_display.setFillColor(Color::Red);
    currency_display.setPosition(1700,10);
    currency_display.setString("Gold: $" + to_string(player_currency));

    Text status_message;
    status_message.setFont(font);
    status_message.setCharacterSize(18);
    status_message.setFillColor(Color::Red);
    status_message.setPosition(100,400);


    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type==Event::Closed)
                window.close();
    
            // Go back to main screen on ESC
            if (event.type==Event::KeyPressed&&event.key.code==Keyboard::Escape) {
                currentScreen=0; 
                return;
            }
    
            // Detect item click
            if (event.type==Event::MouseButtonPressed) {
                Vector2i mouse_pos=Mouse::getPosition(window);
    
                for (int i=0; i<5; i++) {
                    if (buttons[i].getGlobalBounds().contains((float)mouse_pos.x,(float)mouse_pos.y)) {
                        if (items[i].quantity>0) {
                            if (player_currency>=items[i].price) {
                                player_currency-=items[i].price;
                                items[i].quantity--;
                                item_texts[i].setString(items[i].get_display_text());
                                currency_display.setString("Gold: $"+to_string(player_currency));
                                status_message.setString("You bought: "+items[i].name+"!");
                            } else {
                                status_message.setString("Not enough gold to buy "+items[i].name+".");
                            }
                        } else {
                            status_message.setString(items[i].name+" is out of stock!");
                        }
                    }
                }
            }
        }
    
        window.clear();
        window.draw(background);
        window.draw(potionSprite1);
        window.draw(potionSprite2);
        window.draw(potionSprite3);
        window.draw(potionSprite4);
        
        window.draw(info_button);
       
        window.draw(currency_button);
        
        window.draw(title_button);
        for (int i=0; i<5; ++i) {
            window.draw(buttons[i]);
            window.draw(item_texts[i]);
        }
       
        window.draw(status_message);
        window.draw(info);

        window.draw(currency_display);
        window.draw(title);
        window.display();
    }
    
    return ;
}