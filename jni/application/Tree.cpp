//
//  Tree.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Tree.h"

using namespace Zeni;

Tree::Tree(const Point2f &position_, const String &texture_)
: Environment(position_, texture_)
{}

void Tree::render() const {
  Game_Object::render(get_texture());
}
