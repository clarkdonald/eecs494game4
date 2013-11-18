//
//  Simple_Terrain.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef SIMPLE_TERRAIN_H
#define SIMPLE_TERRAIN_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Simple_Terrain : public Terrain {
  public:
    Simple_Terrain(const Zeni::Point2f &position_, const Zeni::String &texture_);
    
    void render() const override;
  
  private:
    Zeni::String texture;
};

#endif /* SIMPLE_TERRAIN_H */
