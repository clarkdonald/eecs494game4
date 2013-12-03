//
//  Simple_Environment.cpp
//  game
//
//  Created by Donald Clark on 12/3/13.
//
//

#include "Simple_Environment.h"

using namespace Zeni;

Simple_Environment::Simple_Environment(const Point2f &position_, const String &texture_)
: Environment(position_, texture_)
{}

void Simple_Environment::render() const {
  Game_Object::render(get_texture());
}
