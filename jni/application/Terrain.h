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
    Terrain(const Zeni::Point2f &position_,
            const Zeni::String &texture_,
            const Zeni::Vector2f &size_ = OBJECT_SIZE);
    
    virtual ~Terrain() = 0;
    
    virtual bool slow_player_down() const;

    const Zeni::String get_texture() const {return texture;}

  private:
    Zeni::String texture;
};

#endif /* TERRAIN_H */
