//
//  Wood_Floor.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Wood_Floor.h"

using namespace Zeni;

Wood_Floor::Wood_Floor(const Point2f &position_)
: Terrain(position_, "woodfloor")
{}

void Wood_Floor::render() const {
  Game_Object::render("woodfloor");
}
