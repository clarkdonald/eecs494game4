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
#include <zenilib.h>

class Terrain : public Game_Object {
  public:
    Terrain(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    virtual ~Terrain() = 0;
    
    virtual void affect(Player &player_);

    const Zeni::Material get_material() const {return terrain_material;}

  protected:
    Zeni::Material terrain_material;
    Zeni::String texture;
};

#endif /* TERRAIN_H */
