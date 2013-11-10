//
//  Ground.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Ground.h"

using namespace Zeni;

Ground::Ground(const Point2f &position_)
: Terrain(position_)
{}

void Ground::render() const {
  Game_Object::render("ground");
}
