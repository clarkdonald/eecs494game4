//
//  Terrain.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Terrain.h"

using Zeni::Point2f;

Terrain::Terrain(const Point2f &position_, const Zeni::String &texture_)
: Game_Object(position_),
  texture(texture_)
{}

Terrain::~Terrain() {}

void Terrain::affect(Player &player_) {
  // default behavior: do nothing
}
