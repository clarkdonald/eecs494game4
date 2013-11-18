//
//  Rock_Pile.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Rock_Pile.h"

using namespace Zeni;

Rock_Pile::Rock_Pile(const Point2f &position_)
: Terrain(position_)
{}

void Rock_Pile::render() const {
  Game_Object::render("rockpile");
}
