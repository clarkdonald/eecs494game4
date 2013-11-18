//
//  Bush.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Bush.h"

using namespace Zeni;

Bush::Bush(const Point2f &position_)
: Terrain(position_)
{}

void Bush::render() const {
  Game_Object::render("bush");
}
