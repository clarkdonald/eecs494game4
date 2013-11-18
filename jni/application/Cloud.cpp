//
//  Cloud.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Cloud.h"

using namespace Zeni;

Cloud::Cloud(const Point2f &position_)
: Atmosphere(position_)
{}

void Cloud::render() const {
  Game_Object::render("cloud");
}
