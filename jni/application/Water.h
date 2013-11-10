//
//  Water.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef WATER_H
#define WATER_H

#include "Terrain.h"
#include "Utility.h"
#include <Zeni/String.h>
#include <Zeni/Coordinate.h>

class Water : public Terrain {
  public:
    Water(const Zeni::Point2f &position_);
    
    void render() const;
    
    void affect(Player &player_) override;
};

#endif /* WATER_H */
