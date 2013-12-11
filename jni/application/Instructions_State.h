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
  
    bool is_done() const {return done;}
  
    void render();
  
    void perform_logic();
  
    void execute_controller_code(const Zeni::Zeni_Input_ID &id,
                                 const float &confidence,
                                 const int &action);
  
  private:
    void on_key(const SDL_KeyboardEvent &event);
  
    void load_map(const std::string &file_);
    
    Zeni::Time_HQ time_passed;
    Zeni::Text_Box tb;
    bool done;
    float distance;
    int movement;
    bool start_movement;
    std::vector< Zeni::Chronometer<Zeni::Time> > text_timers;
    Zeni::Chronometer<Zeni::Time> final_timer;
    std::vector<std::string> texts;
    int timer_index;
    int num_texts_to_render;
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
