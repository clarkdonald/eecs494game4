//
//  Grass.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Grass.h"

using namespace Zeni;

Grass::Grass(const Point2f &position_)
: Terrain(position_)
{}

void Grass::render() const {
  Game_Object::render("grass");
}
