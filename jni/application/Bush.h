//
//  Bush.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef BUSH_H
#define BUSH_H

#include "Terrain.h"
#include "Utility.h"
#include <zenilib.h>

class Bush : public Terrain {
  public:
    Bush(const Zeni::Point2f &position_);
    
    void render() const override;
};

#endif /* BUSH_H */
