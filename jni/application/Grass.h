//
//  Grass.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef GRASS_H
#define GRASS_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Grass : public Terrain {
  public:
    Grass(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* GRASS_H */
