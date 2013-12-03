//
//  House.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "House.h"

using namespace Zeni;

House::House(const Point2f &position_, const String &texture_)
: Environment(position_, texture_)
{}

void House::render() const {
  Game_Object::render(get_texture());
}
