











// From fight.h
// Potion
// Attributes:
// string name
// string effect
// int quantity
// Texture texture
// Sprite sprite
// float effect_timer
// Methods:
// Potion() (default constructor)
// Potion(string name, string effect, string image_path, int quantity)
// void apply_effect(Pet* pet)
// Relationships:
// Associated with Pet.
// Obstacle
// Attributes:
// RectangleShape wall (protected)
// Methods:
// Obstacle() (default constructor)
// Obstacle(float width, float height)
// const RectangleShape& get_wall() const
// void set_position(float x, float y)
// void draw(RenderWindow& window)
// HealthBar
// Attributes:
// float max_width (protected)
// RectangleShape background
// RectangleShape bar
// Methods:
// HealthBar(float width, float height, Color color)
// void set_position(float x, float y)
// void update(int current_health)
// void draw(RenderWindow& window)
// Fireball
// Attributes:
// CircleShape shape_circle (protected)
// float velocity_x (protected)
// float velocity_y (protected)
// bool available (protected)
// int turn (protected)
// Methods:
// Fireball(float radius = 8.f)
// const CircleShape& get_shape() const
// bool is_available() const
// void set_available(bool available)
// int get_turn() const
// void set_turn(int turn)
// bool check_obstacle_collision(const Obstacle obstacles[], int obstacle_count)
// void launch(float pos_x, float pos_y, float dir_x, float dir_y, int turn)
// void update(Obstacle obstacles[], int obstacle_count)
// void draw(RenderWindow& window)
// Relationships:
// Associated with Obstacle.
// Pet (abstract/base class)
// Attributes:
// Sprite sprite (protected)
// Texture texture (protected)
// PetType type (protected)
// float velocity_x (protected)
// float velocity_y (protected)
// int health (protected)
// int score (protected)
// float attack_power (protected)
// float speed (protected)
// float defense (protected)
// bool is_blocking_state (protected)
// float fireball_cooldown (protected)
// int player_id (protected)
// HealthBar health_bar (protected)
// float invincible_timer (protected)
// bool is_invincible (protected)
// RectangleShape shape
// Methods:
// Pet(float size, int id, int pet_type)
// const RectangleShape& get_shape() const
// const Vector2f& get_position() const
// int get_score()
// bool is_blocking()
// int get_player_id()
// bool get_invincible()
// const HealthBar& get_health_bar() const
// float get_velocity_x() const
// float get_velocity_y() const
// float get_attack_power() const
// float get_speed() const
// float get_defense() const
// void set_attack_power(float value)
// void set_speed(float value)
// void set_defense(float value)
// void set_invincible(bool invincible)
// void set_health(int new_health)
// int get_health() const
// void set_score(int new_score)
// void set_blocking(bool blocking)
// void set_player_id(int id)
// void set_velocity(float x, float y)
// void reset_position(float x, float y)
// void move_towards(float target_x, float target_y)
// float get_distance_to(float x, float y) const
// bool has_line_of_sight(float target_x, float target_y, const Obstacle obstacles[], int obstacle_count)
// void update(float delta_time, const Obstacle obstacles[], int obstacle_count, const Potion potions[])
// void take_damage(int damage)
// bool can_shoot() const
// void shoot(Fireball& fireball, float target_x, float target_y)
// void draw(RenderWindow& window)
// Relationships:
// Composes HealthBar.
// Associated with Fireball, Obstacle, Potion.
// Dragon (inherits from Pet)
// Attributes: None additional.
// Methods:
// Dragon(int id = 1)
// void attack()
// void special_ability()
// Phoenix (inherits from Pet)
// Attributes: None additional.
// Methods:
// Phoenix(int id = 1)
// void attack()
// void special_ability()
// Unicorn (inherits from Pet)
// Attributes: None additional.
// Methods:
// Unicorn(int id = 1)
// void speed_burst()
// void magic_shield()
// Griffin (inherits from Pet)
// Attributes: None additional.
// Methods:
// Griffin(int id = 1)
// void claw_strike()
// void dive_bomb()
// Game
// Attributes:
// RenderWindow& window (private)
// Pet* player_1 (private)
// Pet* player_2 (private)
// Fireball fireballs[MAX_FIREBALLS] (private)
// Obstacle obstacles[MAX_OBSTACLES] (private)
// Font font (private)
// Text score_1 (private)
// Text score_2 (private)
// Text game_over_text (private)
// int active_fireball (private)
// int obstacle_count (private)
// bool game_over_state (private)
// Potion potions[MAX_POTIONS] (private)
// Text potion_status (private)
// Vector2f last_position (private)
// Vector2f search_path[MAX_SEARCH_POINTS] (private)
// float search_timer (private)
// int current_point (private)
// int search_size (private)
// int battlefield_type (private)
// Methods:
// Game(RenderWindow& window, int battlefield = 1)
// ~Game() (destructor)
// void initialize_obstacles()
// void initialize_search_path()
// void initialize_potions()
// void run(int pet_type)
// void process_events()
// void update(float delta_time)
// void update_bot_player(float delta_time)
// Fireball& get_available_fireball()
// void check_fireball_collision(Fireball& fireball)
// void reset_game()
// void draw()
// Relationships:
// Composes Pet, Fireball, Obstacle, Potion.
// Associated with SFML classes (RenderWindow, Font, Text).



















#ifndef FIGHT_H
#define FIGHT_H










//battlefield 453

#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<iostream>
#include<cmath>
#include<cstdlib>

using namespace std;
using namespace sf;

extern int currentScreen;
extern int selectedPetType;
int z;

// constants
#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1000
#define PLAYER_SPEED 0.2f
#define FIREBALL_SPEED 0.2f
#define MAX_HEALTH 100
#define FIREBALL_DAMAGE 10
#define BLOCKED_DAMAGE 2
#define FIREBALL_COOLDOWN 1.0f
#define MAX_FIREBALLS 50
#define MAX_OBSTACLES 15
#define MAX_SEARCH_POINTS 4
#define POTION_DURATION 10.0f
#define MAX_POTIONS 4



class Dragon;
class Phoenix;
class Unicorn;
class Griffin;

enum PetType {DRAGON,PHOENIX,UNICORN,GRIFFIN };

// Potion class
class Potion {
public:
    string name;
    string effect;
    int quantity;
    Texture texture;
    Sprite sprite;
    float effect_timer;

    Potion() : name(""), effect(""),quantity(0),effect_timer(0){
        sprite.setScale(0.1, 0.1);
    }

    Potion(string name,string effect, string image_path, int quantity):name(name),effect(effect), quantity(quantity), effect_timer(0.f) {
        
    }

    void apply_effect(Pet* pet) {
        if (quantity>0) {
            quantity--;
            effect_timer=POTION_DURATION;
            // effects applied in Pet::update
        }
    }
};

// obstacle class
class Obstacle {
protected:
    RectangleShape wall;
public:
    const RectangleShape& get_wall() const {return wall;}
    Obstacle() {
        wall.setSize(Vector2f(0.f,0.f));
        wall.setFillColor(Color::Red);
        wall.setOrigin(0.f,0.f);
    }
    Obstacle(float width, float height) {
        wall.setSize(Vector2f(width, height));
        wall.setFillColor(Color::Red);
        wall.setOrigin(width/2,height/2);
    }
    void set_position(float x,float y) 
    { wall.setPosition(x, y); }
    void draw(RenderWindow& window) 
    { window.draw(wall); }
};

// HealthBar class
class HealthBar {
protected:
    float max_width;
public:
    RectangleShape background;
    RectangleShape bar;
    HealthBar(float width, float height, Color color) : max_width(width) {
        background.setSize(Vector2f(width, height));
        background.setFillColor(Color::Red);
        bar.setSize(Vector2f(width, height));
        bar.setFillColor(color);
    }
    void set_position(float x,float y) {
        background.setPosition(x,y);
        bar.setPosition(x,y);
    }
    void update(int current_health) {
        float width=(current_health/static_cast<float>(MAX_HEALTH))*max_width;
        if (width<0) width=0;
        bar.setSize(Vector2f(width,bar.getSize().y));
    }
    void draw(RenderWindow& window) {
        window.draw(background);
        window.draw(bar);
    }
};

// fireball class
class Fireball {
protected:
    CircleShape shape_circle;
    float velocity_x, velocity_y;
    bool available;
    int turn;
public:
    const CircleShape& get_shape() const 
    { return shape_circle; }
    bool is_available() const 
    { return available; }
    void set_available(bool available) 
    { this->available=available; }
    int get_turn() const
     { return turn; }
    void set_turn(int turn) 
    { this->turn=turn; }
    Fireball(float radius=8.f) : velocity_x(0.f),velocity_y(0.f),available(false),turn(0) {
        shape_circle.setRadius(radius);
        shape_circle.setFillColor(Color::Red);
        shape_circle.setOrigin(radius, radius);
    }
    bool check_obstacle_collision(const Obstacle obstacles[], int obstacle_count) {
        for (int i=0; i<obstacle_count; ++i) {
            if (shape_circle.getGlobalBounds().intersects(obstacles[i].get_wall().getGlobalBounds())) {
                return true;
            }
        }
        return false;
    }
    void launch(float pos_x, float pos_y, float dir_x, float dir_y, int turn) {
        shape_circle.setPosition(pos_x, pos_y);
        velocity_x=dir_x*FIREBALL_SPEED;
        velocity_y=dir_y*FIREBALL_SPEED;
        available=true;
        this->turn=turn;
        shape_circle.setFillColor(turn==1?Color::Red:Color::Blue);
    }
    void update(Obstacle obstacles[], int obstacle_count) {
        if (!available) 
        return;
        shape_circle.move(velocity_x, velocity_y);
        if (check_obstacle_collision(obstacles, obstacle_count)) {
            available=false;
            return;
        }
        Vector2f pos=shape_circle.getPosition();
        float radius=shape_circle.getRadius();
        if (pos.x<radius||pos.x>WINDOW_WIDTH-radius||pos.y<radius||pos.y>WINDOW_HEIGHT-radius) {
            available=false;
        }
    }
    void draw(RenderWindow& window) {
        if (available)
         window.draw(shape_circle);
    }
};

// pet class
class Pet {
protected:
    Sprite sprite;
    Texture texture;
    PetType type;
    float velocity_x, velocity_y;
    int health, score;
    float attack_power, speed, defense;
    bool is_blocking_state;
    float fireball_cooldown;
    int player_id;
    HealthBar health_bar;
    float invincible_timer;
    bool is_invincible;
public:
    RectangleShape shape;
    const RectangleShape& get_shape() const 
    { return shape; }
    const Vector2f& get_position() const 
    { return shape.getPosition(); }
    int get_score() 
    { return score; }
    bool is_blocking() 
    { return is_blocking_state; }
    int get_player_id() 
    { return player_id; }
    bool get_invincible()
     { return is_invincible; }
    const HealthBar& get_health_bar() const 
    { return health_bar; }
    float get_velocity_x() const
     { return velocity_x; }
    float get_velocity_y() const
     { return velocity_y; }
    float get_attack_power() const 
    { return attack_power; }
    float get_speed() const
     { return speed; }
    float get_defense() const 
    { return defense; }
    void set_attack_power(float value) 
    { attack_power=value; }
    void set_speed(float value) 
    { speed=value; }
    void set_defense(float value) 
    { defense=value; }
    void set_invincible(bool invincible)
     { is_invincible=invincible; }
    void set_health(int new_health)
     { health=new_health; }
    int get_health() const { return health; }
    void set_score(int new_score) 
    { score=new_score; }
    void set_blocking(bool blocking)
     { is_blocking_state=blocking; }
    void set_player_id(int id) 
    { player_id=id; }
    void set_velocity(float x,float y) { velocity_x=x; velocity_y=y; }
    Pet(float size, int id, int pet_type):velocity_x(0.f), velocity_y(0.f), health(MAX_HEALTH), score(0),attack_power(1.0f), speed(1.0f), defense(1.0f),is_blocking_state(false), fireball_cooldown(0.f), player_id(id),health_bar(200.f, 20.f, id == 1 ? Color::Green : Color::Blue),invincible_timer(0.f), is_invincible(false) {
        shape.setSize(Vector2f(size, size));
        shape.setOrigin(size/2, size/2);
        Color colors[]={Color::Red, Color::Yellow, Color::Green, Color::Blue};
        shape.setFillColor(colors[pet_type - 1]);
        health_bar.set_position(id == 1 ? 50.f : WINDOW_WIDTH-250.f,20.f);
    }
    void reset_position(float x, float y) { shape.setPosition(x, y);}
    void move_towards(float target_x, float target_y) {
        float dx=target_x-shape.getPosition().x;
        float dy=target_y-shape.getPosition().y;
        float length=sqrt(dx*dx+dy*dy);
        if (length>0) {
            dx/=length;
            dy/=length;
        }
        velocity_x=dx*PLAYER_SPEED*speed*0.6f;
        velocity_y=dy*PLAYER_SPEED*speed*0.6f;
    }
    float get_distance_to(float x, float y) const {
        return sqrt(pow(x - shape.getPosition().x, 2) + pow(y - shape.getPosition().y, 2));
    }
    bool has_line_of_sight(float target_x, float target_y, const Obstacle obstacles[], int obstacle_count) {
        Vector2f start = shape.getPosition();
        Vector2f end(target_x,target_y);
        Vector2f direction=end-start;
        float distance=sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance==0) 
        return true;
        direction /= distance;
        for (float t=0; t<distance; 
            t+=10.f) {
            Vector2f point=start+direction*t;
            CircleShape test_point(5.f);
            test_point.setPosition(point);
            for (int i=0; i<obstacle_count; ++i) {
                if (test_point.getGlobalBounds().intersects(obstacles[i].get_wall().getGlobalBounds())) {
                    return false;
                }
            }
        }
        return true;
    }
    void update(float delta_time, const Obstacle obstacles[], int obstacle_count, const Potion potions[]) {
        float prev_x=shape.getPosition().x;
        float prev_y=shape.getPosition().y;
        shape.move(velocity_x, velocity_y);
        bool collided=false;
        FloatRect player_bounds = shape.getGlobalBounds();
        for (int i=0; i<obstacle_count; ++i) {
            FloatRect obstacle_bounds = obstacles[i].get_wall().getGlobalBounds();
            if (player_bounds.intersects(obstacle_bounds)) {
                collided=true;
                break;
            }
        }
        float x=shape.getPosition().x;
        float y=shape.getPosition().y;
        float half_size=shape.getSize().x / 2;
        if (collided||x<half_size||x>WINDOW_WIDTH-half_size||y<half_size||y>WINDOW_HEIGHT-half_size) {
            shape.setPosition(prev_x, prev_y);
        }
        if (fireball_cooldown>0) {
            fireball_cooldown-=delta_time;
        }
        if (is_invincible) {
            invincible_timer-=delta_time;
            if (invincible_timer<=0) {
                is_invincible=false;
            }
        }
        // apply potion effects
        for (int i=0; i<MAX_POTIONS; ++i) {
            if (potions[i].effect_timer>0) {
                if (potions[i].effect=="Health") health = min(health + 5, MAX_HEALTH);
                else if (potions[i].effect=="Attack") attack_power = 1.5f;
                else if (potions[i].effect=="Speed") speed = 1.5f;
                else if (potions[i].effect=="Defense") defense = 1.5f;
            }
        }
        health_bar.update(health);
    }
    void take_damage(int damage) {
        if (!is_invincible && !is_blocking_state) {
            int reduced_damage=static_cast<int>(damage/defense);
            health-=reduced_damage;
            is_invincible=true;
            invincible_timer=1.0;
        } else if (is_blocking_state) {
            health-=BLOCKED_DAMAGE;
        }
        if (health<0) 
        health = 0;
    }
    bool can_shoot() const { return fireball_cooldown <= 0; }
    void shoot(Fireball& fireball, float target_x, float target_y) {
        if (can_shoot()) {
            float dx=target_x-shape.getPosition().x;
            float dy=target_y-shape.getPosition().y;
            float length=sqrt(dx*dx+dy*dy);
            if (length>0) {
                dx/=length;
                dy/=length;
            }
            fireball.launch(shape.getPosition().x, shape.getPosition().y, dx, dy, player_id);
            fireball_cooldown=FIREBALL_COOLDOWN;
        }
    }
    void draw(RenderWindow& window) {
        if (!is_invincible||static_cast<int>(invincible_timer*10)%2==0) {
            window.draw(shape);
        }
        health_bar.draw(window);
    }
};

// derived pet classes
class Dragon : public Pet {
public:
    Dragon(int id=1) : Pet(30,id,1) {
        type=DRAGON;
        set_health(200);
        attack_power=1.2f;
        speed=0.8f;
        defense=1.3f;
    }
    void attack() {  }
    void special_ability() {  }
};

class Phoenix:public Pet {
public:
    Phoenix(int id=1) : Pet(30, id, 2) {
        type=PHOENIX;
        set_health(150);
        attack_power=1.0f;
        speed=1.2f;
        defense=1.0f;
    }
    void attack() { }
    void special_ability() {  }
};

class Unicorn : public Pet {
public:
    Unicorn(int id=1) : Pet(30,id,3) {
        type=UNICORN;
        set_health(80);
        attack_power=0.8f;
        speed=1.5f;
        defense=0.9f;
    }
    void speed_burst() 
    { cout<<"Unicorn uses Speed Burst!"<<endl; }
    void magic_shield() 
    { cout<<"Unicorn activates Magic Shield!"<<endl; }
};

class Griffin : public Pet {
public:
    Griffin(int id=1) : Pet(30, id, 4) {
        type=GRIFFIN;
        set_health(120);
        attack_power=1.1f;
        speed=1.0f;
        defense=1.2f;
    }
    void claw_strike() 
    { cout<<"Griffin uses Claw Strike!"<<endl; }
    void dive_bomb() 
    { cout<<"Griffin uses Dive Bomb and stuns enemies!"<<endl; }
};

// Game class
class Game {
private:
    RenderWindow &window;
    Pet *player_1, *player_2;
    Fireball fireballs[MAX_FIREBALLS];
    Obstacle obstacles[MAX_OBSTACLES];
    Font font;
    Text score_1, score_2, game_over_text;
    int active_fireball, obstacle_count;
    bool game_over_state;
    Potion potions[MAX_POTIONS];
    Text potion_status;
    // AI
    Vector2f last_position, search_path[MAX_SEARCH_POINTS];
    float search_timer;
    int current_point, search_size;
    int battlefield_type; // 1 or 2 for different battlearena
public:


    Game(RenderWindow &window, int battlefield=1) : window(window), active_fireball(0), obstacle_count(0),game_over_state(false), search_timer(0), current_point(0),search_size(0), last_position(0, 0), battlefield_type(battlefield) {
        player_1=new Pet(30,1,selectedPetType);
        player_2=new Pet(30,2,(selectedPetType%4)+1);
        player_1->reset_position(250,WINDOW_HEIGHT/2);
        player_2->reset_position(WINDOW_WIDTH-250, WINDOW_HEIGHT/2);
        initialize_obstacles();
        initialize_search_path();
        initialize_potions();
        if (!font.loadFromFile("hello.ttf")) {
            cerr << "Failed to load font" << endl;
            exit(-1);
        }
        score_1.setFont(font);
        score_1.setCharacterSize(20);
        score_1.setFillColor(Color::White);
        score_1.setPosition(10, 10);
        score_2.setFont(font);
        score_2.setCharacterSize(20);
        score_2.setFillColor(Color::White);
        score_2.setPosition(WINDOW_WIDTH - 150, 10);
        game_over_text.setFont(font);
        game_over_text.setCharacterSize(40);
        game_over_text.setFillColor(Color::Red);
        game_over_text.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 50);
        game_over_text.setString("GAME OVER");
        potion_status.setFont(font);
        potion_status.setCharacterSize(20);
        potion_status.setFillColor(Color::Red);
        potion_status.setPosition(50, 600);
    }
    ~Game() {
        delete player_1;
        delete player_2;
    }
    void initialize_obstacles() {



 z=rand()%2;
        battlefield_type=z;
        obstacle_count=0;
        if (battlefield_type==1) {
            // Battlefield 1
        
            obstacles[obstacle_count++]=Obstacle(WINDOW_WIDTH, 100);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH / 2, 10);
            obstacles[obstacle_count++]=Obstacle(WINDOW_WIDTH, 100);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 10);
            
            obstacles[obstacle_count++]=Obstacle(200, WINDOW_HEIGHT - 200);
            obstacles[obstacle_count-1].set_position(100, WINDOW_HEIGHT / 2);
            obstacles[obstacle_count++]=Obstacle(200, WINDOW_HEIGHT - 200);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2);
          
            obstacles[obstacle_count++]=Obstacle(150, 50);
            obstacles[obstacle_count-1].set_position(500, 300);
            obstacles[obstacle_count++]=Obstacle(150, 50);
            obstacles[obstacle_count-1].set_position(700, 700);
            obstacles[obstacle_count++]=Obstacle(150, 50);
            obstacles[obstacle_count-1].set_position(1300, 700);
            obstacles[obstacle_count++]=Obstacle(150, 50);
            obstacles[obstacle_count-1].set_position(1300, 700);
        } else {
            // Battlefield 2:
            
            obstacles[obstacle_count++]=Obstacle(WINDOW_WIDTH, 100);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH/2,10);
            obstacles[obstacle_count++]=Obstacle(WINDOW_WIDTH, 100);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH/2, WINDOW_HEIGHT-10);
            obstacles[obstacle_count++]=Obstacle(100, WINDOW_HEIGHT);
            obstacles[obstacle_count-1].set_position(10, WINDOW_HEIGHT/2);
            obstacles[obstacle_count++]=Obstacle(100, WINDOW_HEIGHT);
            obstacles[obstacle_count-1].set_position(WINDOW_WIDTH-10, WINDOW_HEIGHT/2);

            obstacles[obstacle_count++]=Obstacle(200, 300);
            obstacles[obstacle_count-1].set_position(400, 300);
            obstacles[obstacle_count++]=Obstacle(200, 300);
            obstacles[obstacle_count-1].set_position(400, 700);
            obstacles[obstacle_count++]=Obstacle(300, 200);
            obstacles[obstacle_count-1].set_position(900, 300);
            obstacles[obstacle_count++]=Obstacle(300, 200);
            obstacles[obstacle_count-1].set_position(900, 700);
            obstacles[obstacle_count++]=Obstacle(200, 300);
            obstacles[obstacle_count-1].set_position(1400, 300);
            obstacles[obstacle_count++]=Obstacle(200, 300);
            obstacles[obstacle_count-1].set_position(1400, 700);
        }
    }
    void initialize_search_path() {
        search_size=4;
        search_path[0]=Vector2f(100, 100);
        search_path[1]=Vector2f(WINDOW_WIDTH-100,100);
        search_path[2]=Vector2f(WINDOW_WIDTH-100, WINDOW_HEIGHT - 100);
        search_path[3]= Vector2f(100, WINDOW_HEIGHT - 100);
        current_point = 0;
    }
    void initialize_potions() {
        potions[0]=Potion("Health Potion", "Health", "p1.png", 3);
        potions[1]= Potion("Attack Potion", "Attack", "p2.png", 2);
        potions[2]= Potion("Speed Potion", "Speed", "p3.png", 2);
        potions[3]= Potion("Defense Potion", "Defense", "p4.png", 2);
        for (int i=0; i<MAX_POTIONS; ++i) {
            potions[i].sprite.setPosition(50, 650+i*60);
        }
    }
    void run(int pet_type) {
        Clock clock;
        while (window.isOpen()) {
            float delta_time=clock.restart().asSeconds();
            process_events();
            if (!game_over_state && currentScreen != 0) {
                update(delta_time);
            } else if (!game_over_state && currentScreen == 0) {
                update(delta_time);
                return;
            }
            draw();
        }
    }
    void process_events() {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    currentScreen = 0;
                    this->reset_game();
                    break;
                }
                if (event.key.code == Keyboard::Space && !game_over_state) {
                    Vector2i mouse_pos = Mouse::getPosition(window);
                    player_1->shoot(this->get_available_fireball(), static_cast<float>(mouse_pos.x), static_cast<float>(mouse_pos.y));
                }
                if (event.key.code == Keyboard::LShift) {
                    player_1->set_blocking(true);
                }
                if (event.key.code == Keyboard::R && game_over_state) {
                    this->reset_game();
                }
                // Potion usage
                if (event.key.code == Keyboard::Num1 && potions[0].quantity > 0) {
                    potions[0].apply_effect(player_1);
                    potion_status.setString("Used Health Potion!");
                }
                if (event.key.code == Keyboard::Num2 && potions[1].quantity > 0) {
                    potions[1].apply_effect(player_1);
                    potion_status.setString("Used Attack Potion!");
                }
                if (event.key.code == Keyboard::Num3 && potions[2].quantity > 0) {
                    potions[2].apply_effect(player_1);
                    potion_status.setString("Used Speed Potion!");
                }
                if (event.key.code == Keyboard::Num4 && potions[3].quantity > 0) {
                    potions[3].apply_effect(player_1);
                    potion_status.setString("Used Defense Potion!");
                }
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::LShift) {
                    player_1->set_blocking(false);
                }
            }
        }
        if (!game_over_state) {
            player_1->set_velocity(0, player_1->get_velocity_y());
            player_1->set_velocity(player_1->get_velocity_x(), 0);
            if (Keyboard::isKeyPressed(Keyboard::Left)) {
                player_1->set_velocity(-PLAYER_SPEED * player_1->get_speed(), player_1->get_velocity_y());
            }
            if (Keyboard::isKeyPressed(Keyboard::Right)) {
                player_1->set_velocity(PLAYER_SPEED * player_1->get_speed(), player_1->get_velocity_y());
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                player_1->set_velocity(player_1->get_velocity_x(), -PLAYER_SPEED * player_1->get_speed());
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                player_1->set_velocity(player_1->get_velocity_x(), PLAYER_SPEED * player_1->get_speed());
            }
            if (player_1->get_velocity_x() != 0 && player_1->get_velocity_y() != 0) {
                player_1->set_velocity(player_1->get_velocity_x() * 0.7, player_1->get_velocity_y() * 0.7);
            }
        }
    }
    void update(float delta_time) {
        // Update potion timers
        for (int i = 0; i < MAX_POTIONS; ++i) {
            // Reset stats before applying active potion effects
            player_1->set_attack_power(1.0f);
            player_1->set_speed(1.0f);
            player_1->set_defense(1.0f);
            // If potion is active, apply its effect
            if (potions[i].effect_timer > 0) {
                if (potions[i].effect == "Attack") player_1->set_attack_power(1.5f);
                else if (potions[i].effect == "Speed") player_1->set_speed(1.5f);
                else if (potions[i].effect == "Defense") player_1->set_defense(1.5f);
                else if (potions[i].effect == "Health") player_1->set_health(min(player_1->get_health() + 5, MAX_HEALTH));
                potions[i].effect_timer -= delta_time;
                if (potions[i].effect_timer < 0) potions[i].effect_timer = 0;
            }
        }
        player_1->update(delta_time, obstacles, obstacle_count, potions);
        update_bot_player(delta_time);
        for (int i = 0; i < MAX_FIREBALLS; ++i) {
            if (fireballs[i].is_available()) {
                fireballs[i].update(obstacles, obstacle_count);
                check_fireball_collision(fireballs[i]);
            }
        }
        score_1.setString("P1 Score: " + to_string(player_1->get_score()));
        score_2.setString("P2 Score: " + to_string(player_2->get_score()));
        if (player_1->get_health() <= 0 || player_2->get_health() <= 0) {
            game_over_state = true;
        }
    }
    void update_bot_player(float delta_time) {
        if (player_2->has_line_of_sight(player_1->get_position().x, player_1->get_position().y, obstacles, obstacle_count)) {
            last_position = player_1->get_position();
            search_timer = 3.0;
        } else {
            search_timer -= delta_time;
        }
        if (search_timer > 0) {
            float distance_to_player = player_2->get_distance_to(last_position.x, last_position.y);
            if (distance_to_player < 300) {
                if (distance_to_player > 150) {
                    player_2->move_towards(last_position.x, last_position.y);
                } else if (distance_to_player < 100) {
                    float dx = player_2->shape.getPosition().x - last_position.x;
                    float dy = player_2->shape.getPosition().y - last_position.y;
                    float length = sqrt(dx * dx + dy * dy);
                    if (length > 0) {
                        dx /= length;
                        dy /= length;
                    }
                    player_2->set_velocity(dx * PLAYER_SPEED * player_2->get_speed() * 0.6, player_2->get_velocity_y());
                    player_2->set_velocity(player_2->get_velocity_x(), dy * PLAYER_SPEED * player_2->get_speed() * 0.6);
                }
                if (rand() % 100 < 15) player_2->set_blocking(true);
                else player_2->set_blocking(false);
            } else {
                player_2->move_towards(last_position.x, last_position.y);
                player_2->set_blocking(false);
            }
            if (player_2->can_shoot() && player_2->has_line_of_sight(player_1->get_position().x, player_1->get_position().y, obstacles, obstacle_count)) {
                int shoot_probability = static_cast<int>(50 - distance_to_player / 10);
                shoot_probability = max(5, min(50, shoot_probability));
                if (rand() % 100 < shoot_probability) {
                    float lead_time = 0.3;
                    float predicted_x = player_1->shape.getPosition().x + player_1->get_velocity_x() * lead_time * 60;
                    float predicted_y = player_1->shape.getPosition().y + player_1->get_velocity_y() * lead_time * 60;
                    player_2->shoot(get_available_fireball(), predicted_x, predicted_y);
                }
            }
        } else {
            player_2->set_blocking(false);
            float distance_to_point = player_2->get_distance_to(search_path[current_point].x, search_path[current_point].y);
            if (distance_to_point < 30) {
                current_point = (current_point + 1) % search_size;
            } else {
                player_2->move_towards(search_path[current_point].x, search_path[current_point].y);
            }
            if (rand() % 100 < 5) player_2->move_towards(last_position.x, last_position.y);
        }
        player_2->update(delta_time, obstacles, obstacle_count, potions);
    }
    Fireball& get_available_fireball() {
        for (int i=0; i<MAX_FIREBALLS; ++i) {
            if (!fireballs[i].is_available()) {
                active_fireball++;
                return fireballs[i];
            }
        }
        active_fireball=MAX_FIREBALLS;
        return fireballs[0];
    }
    void check_fireball_collision(Fireball& fireball) {
        if (!fireball.is_available()) return;
        Pet* target_player=(fireball.get_turn()==1) ? player_2:player_1;
        if (fireball.get_shape().getGlobalBounds().intersects(target_player->get_shape().getGlobalBounds())) {
            target_player->take_damage(static_cast<int>(FIREBALL_DAMAGE * (fireball.get_turn() == 1 ? player_1->get_attack_power() : player_2->get_attack_power())));
            if (fireball.get_turn()==1) {
                player_1->set_score(player_1->get_score()+1);
            } else {
                player_2->set_score(player_2->get_score()+1);
            }
            fireball.set_available(false);
            active_fireball--;
        }
    }
    void reset_game() {
        player_1->set_health(MAX_HEALTH);
        player_2->set_health(MAX_HEALTH);
        player_1->reset_position(250, WINDOW_HEIGHT / 2);
        player_2->reset_position(WINDOW_WIDTH - 250, WINDOW_HEIGHT / 2);
        player_1->set_invincible(false);
        player_2->set_invincible(false);
        for (int i = 0; i < MAX_FIREBALLS; ++i) {
            fireballs[i].set_available(false);
        }
        active_fireball = 0;
        game_over_state = false;
        search_timer = 0;
        current_point = 0;
        last_position = player_1->shape.getPosition();
    }
    void draw() {
        window.clear();
        for (int i = 0; i < obstacle_count; ++i) {
            obstacles[i].draw(window);
        }
        player_1->draw(window);
        player_2->draw(window);
        for (int i = 0; i < MAX_FIREBALLS; ++i) {
            if (fireballs[i].is_available()) {
                fireballs[i].draw(window);
            }
        }
        window.draw(score_1);
        window.draw(score_2);
        if (player_1->is_blocking()) {
            float radius = player_1->shape.getSize().x / 2 + 5;
            CircleShape shield(radius);
            shield.setOrigin(radius, radius);
            shield.setPosition(player_1->shape.getPosition());
            shield.setFillColor(Color::White);
            window.draw(shield);
        }
        if (player_2->is_blocking()) {
            float radius = player_2->shape.getSize().x / 2 + 5;
            CircleShape shield(radius);
            shield.setOrigin(radius, radius);
            shield.setPosition(player_2->shape.getPosition());
            shield.setFillColor(Color::White);
            window.draw(shield);
        }
        // Draw potions
        for (int i = 0; i < MAX_POTIONS; ++i) {
            Text potion_text(potions[i].name + ": " + to_string(potions[i].quantity), font, 20);
            potion_text.setFillColor(Color::White);
            potion_text.setPosition(100, 650 + i * 60);
            window.draw(potion_text);
        }
        window.draw(potion_status);
        if (game_over_state) {
            window.draw(game_over_text);
            Text restart_text("Press R to restart", font, 20);
            restart_text.setFillColor(Color::White);
            restart_text.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 20);
            window.draw(restart_text);
            currentScreen = 5;
        }
        window.display();
    }
};

#endif