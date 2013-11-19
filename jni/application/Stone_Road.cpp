//
//  Stone_Road.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Stone_Road.h"

using namespace Zeni;

Stone_Road::Stone_Road(const Point2f &position_)
: Terrain(position_, "stonevertical")
{}

void Stone_Road::render() const {
  Game_Object::render("stonevertical");
}
