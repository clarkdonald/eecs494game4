//
//  Rock_Pile.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef ROCK_PILE_H
#define ROCK_PILE_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Rock_Pile : public Terrain {
  public:
    Rock_Pile(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* ROCK_PILE_H */
