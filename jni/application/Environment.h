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
#include <Zeni/Coordinate.h>

class Environment : public Game_Object {
  public:
    Environment(const Zeni::Point2f &position_);
    
    virtual ~Environment() = 0;
    
    virtual void affect(Player &player_);
};

#endif /* ENVIRONMENT_H */
