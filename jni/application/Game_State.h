//
//  Game_State.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Utility.h"
#include "Weapon.h"
#include <zenilib.h>
#include <string>

class Grass;
class Terrain;
class Atmosphere;
class Environment;
class Player;
class Health_Bar;

class Game_State {
  public:
    Game_State(const std::string &file_);
    
    ~Game_State();
    
    void on_push();
    
    void on_pop();
        
    void perform_logic();
    
    void render();
        
    bool is_gameover() const {return gameover;}

		void execute_controller_code(const Zeni::Zeni_Input_ID &id,
                                 const float &confidence,
                                 const int &action);
    
  private:
    void clear();

	  void render_all();

    void render_spawn_menu();
  
    void create_tree(const Zeni::Point2f &position);
  
    void create_house(const Zeni::Point2f &position);
  
    void load_map(const std::string &file_);
    
    Zeni::Time_HQ time_passed;
    //Zeni::Chronometer<Zeni::Time> shooting_timer;
    std::vector<Controls> controls;
    std::list<Terrain*> terrains;
    std::list<Environment*> environments;
    std::list<Atmosphere*> atmospheres;
    std::list<Grass*> grasss;
    std::list<Player*> players;

    std::list<Weapon*> projectiles;
    bool gameover;
    Dimension dimension;
    std::vector<std::pair<Zeni::Point2i, Zeni::Point2i> (*)()> screen_coord_map;
    std::vector<Health_Bar*> health_bars;
};

#endif /* GAME_STATE_H */