//
//  Atmosphere.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Atmosphere.h"

using Zeni::Point2f;
using Zeni::String;

Atmosphere::Atmosphere(const Point2f &position_,  const String &texture_)
: Game_Object(position_, LARGE_SIZE),
  texture(texture_)
{}

Atmosphere::~Atmosphere() {}

void Atmosphere::update(const float &value) {
  // do nothing as default
}
