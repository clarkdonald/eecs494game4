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
#include <zenilib.h>
#include <string>

class Dirt;
class Terrain;
class Atmosphere;
class Environment;
class Player;

class Game_State {
  public:
    Game_State(const std::string &file_);
    
    ~Game_State();
    
    void on_push();
    
    void on_pop();
        
    void perform_logic();
    
    void render();
        
    bool is_gameover() const {return gameover;}

		void execute_controller_code(const Zeni::Zeni_Input_ID &id, const float &confidence, const int &action);
    
  private:
    void clear();

	void render_all();
        
    void load_map(const std::string &file_);
    
    Zeni::Time_HQ time_passed;
    //Zeni::Chronometer<Zeni::Time> shooting_timer;
    Controls controls;
    std::list<Terrain*> terrains;
    std::list<Environment*> environments;
    std::list<Atmosphere*> atmospheres;
    std::list<Dirt*> dirts;
    bool gameover;
    Player *player;
    Dimension dimension;
};

#endif /* GAME_STATE_H */