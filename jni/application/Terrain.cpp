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
using Zeni::Vector2f;

Terrain::Terrain(const Point2f &position_, const String &texture_, const Vector2f &size_)
: Game_Object(position_, size_),
  texture(texture_)
{}

Terrain::~Terrain() {}

bool Terrain::slow_player_down() const {
  return false;
}
