//
//  Dirt.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Dirt.h"

using namespace Zeni;

Dirt::Dirt(const Point2f &position_)
: Terrain(position_)
{}

void Dirt::render() const {
  Game_Object::render("dirt");
}
