//
//  Crystal.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Crystal.h"

using namespace Zeni;

Crystal::Crystal(const Point2f &position_)
: Game_Object(position_)
{}

void Crystal::render() const {
  Game_Object::render("crystal");
}
