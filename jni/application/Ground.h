//
//  Ground.h
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#ifndef GROUND_H
#define GROUND_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Ground : public Terrain {
  public:
    Ground(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* GROUND_H */
