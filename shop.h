#ifndef SHOP_H
#define SHOP_H

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<sstream>

using namespace std;
using namespace sf;


class Pet;
class Training;



class Shop //: virtual public Pet,  virtual public Training {

{
   protected:
    int coins;

public:
    Shop() : coins(10000) {} 
    void set_coin(int coins){
        this->coins=coins;

    }
    int get_coins()
    {
        return coins;
    }

};





class Item : public Shop{
    public:
        string name;
        string type;
        string effect;
        int price;
        int quantity;
    
        Item() {}
    
        Item(string name, string type, string effect, int price, int quantity) {
            this->name = name;
            this->type = type;
            this->effect = effect;
            this->price = price;
            this->quantity = quantity;
        }
    
        string get_display_text() {
            stringstream ss;
            ss << " == "<<name << " -- " << " Gold=" <<" == " <<price << " == "<<"Effect"<<" == "<<effect<<" == "<<"Quantity"<< " == " << quantity;
            return ss.str();
        }
        string get_name() { return name; }
        string get_effect() { return effect; }
        int get_price() { return price; }













        
        
    };

// Declare items array properly elsewhere in the implementation file or another header
extern Item items[5];





void display_shop_info(const string &input, Font &font, RenderWindow &window, Event &event, int &currentScreen, Item *item); ;

#endif 