//
//  House.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "House.h"

using namespace Zeni;

House::House(const Point2f &position_, const House_Part &house_part_)
: Environment(position_), house_part(house_part_)
{}

void House::render() const {
  switch (house_part) {
    case DOOR:
      Game_Object::render("door");
      break;
      
    case WINDOW_RIGHT:
      Game_Object::render("windowright");
      break;
      
    case WINDOW_LEFT:
      Game_Object::render("windowleft");
      break;
      
    case BLUE_ROOF_UP_RIGHT_CORNER:
      Game_Object::render("blueroofuprightcorner");
      break;
      
    case BLUE_ROOF_UP_MIDDLE:
      Game_Object::render("blueroofupmiddle");
      break;
      
    case BLUE_ROOF_UP_LEFT_CORNER:
      Game_Object::render("blueroofupleftcorner");
      break;
      
    case BLUE_ROOF_LEFT_SIDE:
      Game_Object::render("blueroofleftside");
      break;
      
    case BLUE_ROOF_RIGHT_SIDE:
      Game_Object::render("blueroofrightside");
      break;
      
    case BLUE_ROOF_MIDDLE_EDGE:
      Game_Object::render("blueroofmiddleedge");
      break;
      
    case BLUE_ROOF_MIDDLE:
      Game_Object::render("blueroofmiddle");
      break;
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_1:
      Game_Object::render("blueroofdownrightcorner1");
      break;
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_2:
      Game_Object::render("blueroofdownrightcorner2");
      break;
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_1:
      Game_Object::render("blueroofdownleftcorner1");
      break;
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_2:
      Game_Object::render("blueroofdownleftcorner2");
      break;
      
    default:
      error_handle("Unknown House part orientation for House");
  }
}
