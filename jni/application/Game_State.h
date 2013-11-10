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

class Ground;
class Terrain;

class Game_State {
  public:
    Game_State(const std::string &file_);
    
    ~Game_State();
    
    void on_push();
    
    void on_pop();
        
    void perform_logic();
    
    void render();
        
    bool is_done() const {return done;}
    
  private:
    void clear();
        
    void load_map(const std::string &file_);
    
    Zeni::Time_HQ time_passed;
    Zeni::Chronometer<Zeni::Time> use_timer;
    Zeni::Chronometer<Zeni::Time> shoot_timer;
    Zeni::Chronometer<Zeni::Time> hit_timer;
    Zeni::Chronometer<Zeni::Time> shooting_timer;
    Controls controls;
    std::list<Terrain*> terrains;
    std::list<Ground*> grounds;
    bool done;
    Dimension dimension;
};

#endif /* GAME_STATE_H */