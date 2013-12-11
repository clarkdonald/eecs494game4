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

Crystal::Crystal(const Point2f &position_, const Vector2f& size_) :
  Game_Object(position_, size_) 
{}

void Crystal::render() const {
  Game_Object::render("crystal");
}
