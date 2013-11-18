//
//  Atmosphere.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Atmosphere.h"

using Zeni::Point2f;

Atmosphere::Atmosphere(const Point2f &position_)
: Game_Object(position_)
{}

Atmosphere::~Atmosphere() {}

void Atmosphere::affect(Player &player_) {
  // default behavior: do nothing
}
