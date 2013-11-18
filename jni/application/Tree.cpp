//
//  Tree.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Tree.h"

using namespace Zeni;

Tree::Tree(const Point2f &position_, const Two_Part_Object &part_)
: Environment(position_), part(part_)
{}

void Tree::render() const {
  switch (part) {
    case TOP:
      Game_Object::render("treetop");
      break;
    
    case BOTTOM:
      Game_Object::render("treebottom");
      break;
      
    default:
      error_handle("Unknown tree part orientation for Tree");
  }
}
