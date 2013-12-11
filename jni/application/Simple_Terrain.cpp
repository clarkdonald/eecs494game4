//
//  Simple_Terrain.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Simple_Terrain.h"

using namespace Zeni;

Simple_Terrain::Simple_Terrain(const Point2f &position_,
                               const String &texture_,
                               const Vector2f &size_)
: Terrain(position_, texture_, size_)
{}

void Simple_Terrain::render() const {
  Game_Object::render(get_texture());
}
