//
//  Wood_Floor.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//
#ifndef WOOD_FLOOR_H
#define WOOD_FLOOR_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Wood_Floor : public Terrain {
  public:
    Wood_Floor(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* WOOD_FLOOR_H */
