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

class Instructions_State : public Zeni::Gamestate_Base {
  Zeni::Text_Box tb;
  
  public:
    Instructions_State();
    
  private:
    void on_key(const SDL_KeyboardEvent &event);
    
    void render();
};

#endif /* INSTRUCTIONS_STATE_H */
