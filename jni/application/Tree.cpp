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

Zeni::String Tree::get_texture() const {
  switch (part) {
    case TOP:
      return "treetop";
      break;
    
    case BOTTOM:
      return "treebottom";
      break;
      
    default:
      error_handle("Unknown tree part orientation for Tree");
  }
}

void Tree::render() const {
  Game_Object::render(get_texture());  
}
