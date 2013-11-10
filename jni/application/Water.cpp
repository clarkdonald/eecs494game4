//
//  Water.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Water.h"

using namespace Zeni;

Water::Water(const Point2f &position_)
: Terrain(position_)
{}

void Water::render() const {
  Game_Object::render("water");
}

void Water::affect(Player &player_) {
}
