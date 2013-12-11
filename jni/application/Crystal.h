//
//  Crystal.h
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#ifndef CRYSTAL_H
#define CRYSTAL_H

#include "Game_Object.h"

class Crystal : public Game_Object {
  public:
    Crystal(const Zeni::Point2f &position_);
    Crystal(const Zeni::Point2f &position_, const Zeni::Vector2f& size_);
  
    void render() const override;
};

#endif /* CRYSTAL_H */
