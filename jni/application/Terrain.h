//
//  Terrain.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef TERRAIN_H
#define TERRAIN_H

#include "Game_Object.h"
#include "Player.h"
#include "Utility.h"
#include <Zeni/Coordinate.h>

class Terrain : public Game_Object {
  public:
    Terrain(const Zeni::Point2f &position_);
    
    virtual ~Terrain() = 0;
    
    virtual void affect(Player &player_);
};

#endif /* TERRAIN_H */
