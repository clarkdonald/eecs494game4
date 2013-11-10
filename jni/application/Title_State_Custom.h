//
//  Title_State_Custom.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef TITLE_STATE_CUSTOM_H
#define TITLE_STATE_CUSTOM_H

#include <zenilib.h>
#include "Play_State.h"
#include "Instructions_State.h"

class Title_State_Custom : public Zeni::Title_State<Play_State, Instructions_State> {
  public:
    Title_State_Custom();
    
    void render();
};

#endif /* TITLE_STATE_CUSTOM_H */
