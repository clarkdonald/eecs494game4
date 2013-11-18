//
//  Dirt.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef DIRT_H
#define DIRT_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Dirt : public Terrain {
  public:
    Dirt(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* DIRT_H */
