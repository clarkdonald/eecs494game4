//
//  Environment.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Environment.h"

using Zeni::Point2f;
using Zeni::String;

Environment::Environment(const Point2f &position_, const String &texture_)
: Game_Object(position_),
  texture(texture_)
{}

Environment::~Environment() {}

void Environment::affect(Player &player_) {
  // default behavior: do nothing
}
