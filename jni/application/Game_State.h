//
//  Game_State.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Weapon.h"
#include "Health_Bar.h"
#include "Utility.h"
#include <zenilib.h>
#include <string>

class Control;
class Terrain;
class Atmosphere;
class Environment;
class Player;
class Npc;

struct Player_Wrapper {
  Player_Wrapper(Player *player_, const int &uid_);
  ~Player_Wrapper();
  Player* player;
  int uid;
};

struct Player_Info {
  Player_Info(const Zeni::Point2f &start_position_, const Team &team_);
  Controls controls;
  Health_Bar health_bar;
  Zeni::Point2f start_position;
  Team team;
};

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
    std::list<Terrain*> terrains;
    std::list<Environment*> environments;
    std::list<Atmosphere*> atmospheres;
    std::list<Terrain*> grasss;
    std::list<Player_Wrapper*> player_wrappers;
    std::vector<Player_Info*> player_infos;
    std::list<Weapon*> projectiles;
    std::list<Npc*> npcs;
    int total_num_crystals;
    int crystals_in_play;
    bool gameover;
    Dimension dimension;
    std::vector<std::pair<Zeni::Point2i, Zeni::Point2i> (*)()> screen_coord_map;
};

#endif /* GAME_STATE_H */