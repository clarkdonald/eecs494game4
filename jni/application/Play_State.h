//
//  Play_State.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <zenilib.h>

class Game_State;
class Instructions_State;

class Play_State : public Zeni::Gamestate_II {
  public:
    Play_State();
    
    ~Play_State();
    
    void on_push();
    
    void on_pop();
    
    void on_key(const SDL_KeyboardEvent &event);

		//detect xbox controller button
		void on_event(const Zeni::Zeni_Input_ID &id, const float &confidence, const int &action);
    
    void perform_logic();
    
    void render();

	void initialize_xbox_controller();
    
  private:
    Game_State *game_state;
    Instructions_State *instructions;
};

#endif /* PLAY_STATE_H */