//
//  Environment.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Environment.h"

using Zeni::Point2f;

Environment::Environment(const Point2f &position_)
: Game_Object(position_)
{}

Environment::~Environment() {}

void Environment::affect(Player &player_) {
  // default behavior: do nothing
}
