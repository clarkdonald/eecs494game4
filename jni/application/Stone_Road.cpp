//
//  Stone_Road.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Stone_Road.h"

using namespace Zeni;

Stone_Road::Stone_Road(const Point2f &position_, const Vector2f &size_)
: Terrain(position_, "stonevertical", size_)
{}

void Stone_Road::render() const {
  Game_Object::render(get_texture());
}
