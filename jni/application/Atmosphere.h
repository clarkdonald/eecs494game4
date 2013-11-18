//
//  Atmosphere.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Atmosphere : public Game_Object {
  public:
    Atmosphere(const Zeni::Point2f &position_);
    
    virtual ~Atmosphere() = 0;
    
    virtual void affect(Player &player_);
};

#endif /* ATMOSPHERE_H */
