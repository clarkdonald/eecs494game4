//
//  Stone_Road.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef STONE_ROAD_H
#define STONE_ROAD_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Stone_Road : public Terrain {
  public:
    Stone_Road(const Zeni::Point2f &position_, const Zeni::Vector2f &size_ = OBJECT_SIZE);
    
    void render() const override;
};

#endif /* STONE_ROAD_H */
