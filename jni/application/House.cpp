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

String House::get_texture() const {
  switch (house_part) {
    case DOOR:
      return "door";
      break;
      
    case WINDOW_RIGHT:
      return "windowright";
      break;
      
    case WINDOW_LEFT:
      return "windowleft";
      break;
      
    case BLUE_ROOF_UP_RIGHT_CORNER:
      return "blueroofuprightcorner";
      break;
      
    case BLUE_ROOF_UP_MIDDLE:
      return "blueroofupmiddle";
      break;
      
    case BLUE_ROOF_UP_LEFT_CORNER:
      return "blueroofupleftcorner";
      break;
      
    case BLUE_ROOF_LEFT_SIDE:
      return "blueroofleftside";
      break;
      
    case BLUE_ROOF_RIGHT_SIDE:
      return "blueroofrightside";
      break;
      
    case BLUE_ROOF_MIDDLE_EDGE:
      return "blueroofmiddleedge";
      break;
      
    case BLUE_ROOF_MIDDLE:
      return "blueroofmiddle";
      break;
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_1:
      return "blueroofdownrightcorner1";
      break;
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_2:
      return "blueroofdownrightcorner2";
      break;
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_1:
      return "blueroofdownleftcorner1";
      break;
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_2:
      return "blueroofdownleftcorner2";
      break;
      
    default:
      error_handle("Unknown House part orientation for House");
  }
}

void House::render() const {
  Game_Object::render(get_texture());
}
