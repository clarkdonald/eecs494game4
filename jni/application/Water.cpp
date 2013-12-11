//
//  Water.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Water.h"

using namespace Zeni;

Water::Water(const Point2f &position_, const Vector2f &size_)
: Terrain(position_, "water", size_)
{}

void Water::render() const {
  Game_Object::render(get_texture());
}

bool Water::slow_player_down() const {
  return true;
}
