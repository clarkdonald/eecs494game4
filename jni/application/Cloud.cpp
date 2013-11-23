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
: Atmosphere(position_, "cloud")
{}

void Cloud::render() const {
  Game_Object::render(get_texture());
}

void Cloud::update(const float &timestep) {
  Point2f pos = get_position();
  pos.x += (CLOUD_SPD * timestep);
  set_position(pos);
}
