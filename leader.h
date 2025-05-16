

// From leader.h
// ScoreEntry
// Attributes:
// string player_name
// int player_score
// Methods: None (data structure).
// GameTexture
// Attributes:
// string texture_name
// Texture sf_texture
// Methods: None.
// GameFont
// Attributes:
// string font_name
// Font sf_font
// Methods: None.
// AssetData
// Attributes:
// string asset_type
// string asset_name
// string asset_path
// Methods: None.
// GameManager
// Attributes:
// RenderWindow& game_window (private)
// AssetData game_assets[MAX_ASSETS] (private)
// GameTexture game_textures[MAX_TEXTURES] (private)
// GameFont game_fonts[MAX_FONTS] (private)
// ScoreEntry leader_board[MAX_LEADERBOARD_ENTRIES] (private)
// int asset_count (private)
// int texture_count (private)
// int font_count (private)
// int leader_board_count (private)
// Methods:
// GameManager(RenderWindow& window) (constructor)
// void run()
// void load_assets() (private)
// void setup_game() (private)
// void main_loop() (private)
// int load_asset_data(const string& config_file, AssetData assets[], int max_assets) (private)
// void save_player_scores(const string& score_file, const ScoreEntry scores[], int count) (private)
// int load_leader_board(const string& score_file, ScoreEntry board[], int max_entries) (private)
// Relationships:
// Composes AssetData, GameTexture, GameFont, ScoreEntry.
// Associated with RenderWindow (SFML).





#ifndef LEADER_H
#define LEADER_H

#include<SFML/Graphics.hpp>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;
using namespace sf;

extern int currentSscreen;

// maximum counts 
const int MAX_ASSETS=5;
const int MAX_TEXTURES=50;
const int MAX_FONTS=2;
const int MAX_LEADERBOARD_ENTRIES=5;

// classs for score input
class ScoreEntry {

    public:

    string player_name;
    int player_score;
};

// class for texture data
class GameTexture {

    public:

    string texture_name;
    Texture sf_texture;
};

// class for font data
class GameFont {

    public:

    string font_name;
    Font sf_font;
};

// class for asset data
struct AssetData {

    public:

    string asset_type;
    string asset_name;
    string asset_path;
};

class GameManager {

private:

    RenderWindow& game_window; // existing video
    AssetData game_assets[MAX_ASSETS];
    GameTexture game_textures[MAX_TEXTURES];
    GameFont game_fonts[MAX_FONTS];
    ScoreEntry leader_board[MAX_LEADERBOARD_ENTRIES];
    
    int asset_count;
    int texture_count;
    int font_count;
    int leader_board_count;

    // see asset data
    int load_asset_data(const string& config_file,AssetData assets[],int max_assets) {
        ifstream input_file(config_file);
        int count=0;
        
        if (!input_file.is_open()) {
            cerr<<"Error loading: "<<config_file<<endl;
            return 0;
        }
        
        string current_line;
        while (getline(input_file, current_line)&&count<max_assets) {
           
            
            size_t first_comma=current_line.find(',');
            size_t second_comma=current_line.find(',',first_comma+1);
            
            if (first_comma!=string::npos&&second_comma!=string::npos) {
                assets[count].asset_type=current_line.substr(0,first_comma);
                assets[count].asset_name=current_line.substr(first_comma+1,second_comma-first_comma-1);
                assets[count].asset_path=current_line.substr(second_comma+1);
                
                
                auto trim=[](string& str) {
                    str.erase(0,str.find_first_not_of("  "));
                    str.erase(str.find_last_not_of("  ")+1);
                };
                
                trim(assets[count].asset_type);
                trim(assets[count].asset_name);
                trim(assets[count].asset_path);
                
                count++;
            }
        }
        
        input_file.close();
        return count;
    }

    //  save points
    void save_player_scores(const string& score_file, const ScoreEntry scores[], int count) {
        ofstream output_file(score_file);
        
        if (!output_file.is_open()) {
            cerr<<"Error saving to: "<<score_file<<endl;
            return;
        }
        
        for (int i=0; i<count; i++) {
            output_file<<scores[i].player_name<<","<<scores[i].player_score<<endl;
        }
        
        output_file.close();
    }

    //  load points
    int load_leader_board(const string& score_file, ScoreEntry board[], int max_entries) {
        ifstream input_file(score_file);
        int count = 0;
        
        if (!input_file.is_open()) {
            cerr<<"Error loading: "<<score_file<<endl;
            return 0;
        }
        
        string current_line;
        while (getline(input_file, current_line) && count<max_entries) {
           
            
            size_t comma_pos=current_line.find(',');
            if (comma_pos!=string::npos) {
                board[count].player_name=current_line.substr(0, comma_pos);
                string score_str=current_line.substr(comma_pos + 1);
                
                istringstream score_stream(score_str);
                if (score_stream >> board[count].player_score) {
                    count++;
                }
            }
        }
        
        input_file.close();
        
        // sort by score top to bottom
                for (int i=0; i < count-1; i++) {
            for (int j=0; j<count-i-1; j++) {
                if (board[j].player_score<board[j + 1].player_score) {
                    swap(board[j], board[j+1]);
                }
            }
        }
        
        return count;
    }

public:
    GameManager(RenderWindow& window) : game_window(window) {
        // initialize counts
        asset_count=0;
        texture_count=0;
        font_count=0;
        leader_board_count=0;
    }

    void run() {
        load_assets();
        setup_game();
        main_loop();
    }

private:

    void load_assets() {
        // load data
        asset_count = load_asset_data("game_assets.txt", game_assets, MAX_ASSETS);
        
        // process data
        for (int i = 0; i < asset_count; i++) {
            if (game_assets[i].asset_type=="texture" && texture_count<MAX_TEXTURES) {
                // only load textures for player_1 and player_2
                if (game_assets[i].asset_name=="player_1"||game_assets[i].asset_name == "player_2") {
                    if (game_textures[texture_count].sf_texture.loadFromFile(game_assets[i].asset_path)) {
                        game_textures[texture_count].texture_name=game_assets[i].asset_name;
                        texture_count++;
                    } else {
                        cerr<<"Failed to load texture: "<<game_assets[i].asset_path << endl;
                    }
                }
            }
            else if (game_assets[i].asset_type=="font" && font_count < MAX_FONTS) {
                if (game_fonts[font_count].sf_font.loadFromFile(game_assets[i].asset_path)) {
                    game_fonts[font_count].font_name=game_assets[i].asset_name;
                    font_count++;
                } else {
                    cerr<<"Failed to load font: "<<game_assets[i].asset_path<<endl;
                }
            }
        }
    }

    void setup_game() {
        // Sample player data
        ScoreEntry player_scores[MAX_LEADERBOARD_ENTRIES]={
            {"Player_2", 1500},
            {"player_1", 1200},
        };
        
        save_player_scores("player_scores.txt", player_scores, 2);
        leader_board_count = load_leader_board("player_scores.txt", leader_board, MAX_LEADERBOARD_ENTRIES);
    }

    void main_loop() {
       
       
     
        
        // create elements
        Text main_title;
        if (font_count>0) {
            main_title.setFont(game_fonts[0].sf_font);
        }
        main_title.setString("Game Assets:");
        main_title.setCharacterSize(24);
        main_title.setFillColor(Color::Red);
        main_title.setPosition(50, 10);
        
        // Texture displays
        RectangleShape texture_boxes[MAX_TEXTURES];
        Text texture_labels[MAX_TEXTURES];
        
        for (int i=0; i<texture_count; i++) {
            texture_boxes[i].setSize(Vector2f(200, 200));
            texture_boxes[i].setPosition(50, 50 + i * 390);
            texture_boxes[i].setTexture(&game_textures[i].sf_texture);
            texture_boxes[i].setOutlineThickness(2.f);
            texture_boxes[i].setOutlineColor(Color::Red);
            
            if (font_count>0) {
                texture_labels[i].setFont(game_fonts[0].sf_font);
            }
            texture_labels[i].setString(game_textures[i].texture_name);
            texture_labels[i].setCharacterSize(40);
            texture_labels[i].setFillColor(Color::Red);
            texture_labels[i].setPosition(50, 300 + i * 400);
        }
        
    
        Text leader_board_title;
        if (font_count>0) {
            leader_board_title.setFont(game_fonts[0].sf_font);
        }
        leader_board_title.setString("Top Players:");
        leader_board_title.setCharacterSize(50);
        leader_board_title.setFillColor(Color::Red);
        leader_board_title.setPosition(600, 100);
        
        Text leader_board_entries[MAX_LEADERBOARD_ENTRIES];
        for (int i = 0; i < leader_board_count; i++) {
            if (font_count > 0) {
                leader_board_entries[i].setFont(game_fonts[0].sf_font);
            }
            
            leader_board_entries[i].setString(to_string(i+1)+". "+leader_board[i].player_name + " - "+to_string(leader_board[i].player_score));
            
            if (leader_board[i].player_name.find("enemy")!=string::npos) {
                leader_board_entries[i].setFillColor(Color::Red);
            } else {
                leader_board_entries[i].setFillColor(Color::Green);
            }
            
            leader_board_entries[i].setCharacterSize(40);
            leader_board_entries[i].setPosition(600, 250+i*50);
        }
       
    
        //  game loop
        while (game_window.isOpen()) {
            Event event;
            while (game_window.pollEvent(event)) {
                if (event.type==Event::Closed) {
                    game_window.close();
                }
                if (event.type==Event::KeyPressed && event.key.code==Keyboard::Escape) {
                    currentScreen=0;
                    return; // exit to switch screens
                }
            }

            game_window.clear();

            // Draw 
            game_window.draw(main_title);

            for (int i=0; i<texture_count; i++) {
                game_window.draw(texture_boxes[i]);
                game_window.draw(texture_labels[i]);
            }

            game_window.draw(leader_board_title);
            for (int i=0; i<leader_board_count; i++) {
                game_window.draw(leader_board_entries[i]);
            }

           

            game_window.display();
        }
    }
};

#endif