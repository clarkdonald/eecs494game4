//
//  Environment.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <zenilib.h>

class Environment : public Game_Object {
  public:
    Environment(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    virtual ~Environment() = 0;

    const Zeni::String get_texture() const {return texture;}
    
    virtual void affect(Player &player_);

  private:
    Zeni::String texture;
};

#endif /* ENVIRONMENT_H */
