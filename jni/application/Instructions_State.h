//
//  Instructions_State.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef INSTRUCTIONS_STATE_H
#define INSTRUCTIONS_STATE_H

#include <zenilib.h>
#include "Utility.h"
#include <list>
#include <vector>

class Player;
class Npc;
class Crystal;
class Game_Object;

class Instructions_State : public Zeni::Gamestate_Base {
  public:
    Instructions_State();
  
    ~Instructions_State();
  
  private:
    void on_key(const SDL_KeyboardEvent &event);
  
    void render();
  
    void perform_logic();
  
    void load_map(const std::string &file_);
  
    void load_scripted_movement();
  
    Zeni::Time_HQ time_passed;
    Zeni::Text_Box tb;
    std::vector< Zeni::Chronometer<Zeni::Time> > text_timers;
    std::vector<std::string> texts;
    int timer_index;
    Dimension dimension;
    Player *player_blue0;
    Player *player_blue1;
    Player *player_red0;
    Player *player_red1;
    Npc *npc_blue;
    Npc *npc_red;
    std::list<Crystal*> crystals;
    std::list<Game_Object*> terrains;
};

#endif /* INSTRUCTIONS_STATE_H */
