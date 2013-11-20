//
//  Terrain.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Terrain.h"

using Zeni::Point2f;
using Zeni::String;

Terrain::Terrain(const Point2f &position_, const String &texture_)
: Game_Object(position_),
  texture(texture_)
{}

Terrain::~Terrain() {}

bool Terrain::slow_player_down() const {
  return false;
}
