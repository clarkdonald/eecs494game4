//
//  Environment_Factory.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Environment_Factory.h"
#include "Environment_Includes.h"
#include "Utility.h"

using std::bad_alloc;
using namespace Zeni;

Environment * create_environment(const String &type_, const Point2f &position_)
{
  if (type_ == "Fence") return new Simple_Environment(position_, "fencehorizontal");
  error_handle("Unknown environment type");
  return nullptr;
}

Environment * create_environment(const String &type_,
                                 const Point2f &position_,
                                 const Two_Part_Object &part_)
{
  if (type_ != "Tree") error_handle("Unknown environment type");
  
  switch (part_) {
    case TOP:
      return new Tree(position_, "treetop");
      
    case BOTTOM:
      return new Tree(position_, "treebottom");
      
    default:
      error_handle("Unknown tree part orientation for Tree");
  }
}

Environment * create_environment(const String &type_,
                                 const Point2f &position_,
                                 const House_Part &part_)
{
  if (type_ != "House") error_handle("Unknown environment type");
  
  switch (part_) {
    case DOOR:
      return new House(position_, "door");
      
    case WINDOW_RIGHT:
      return new House(position_, "windowright");
      
    case WINDOW_LEFT:
      return new House(position_, "windowleft");
      
    case BLUE_ROOF_UP_RIGHT_CORNER:
      return new House(position_, "blueroofuprightcorner");
      
    case BLUE_ROOF_UP_MIDDLE:
      return new House(position_, "blueroofupmiddle");
      
    case BLUE_ROOF_UP_LEFT_CORNER:
      return new House(position_, "blueroofupleftcorner");
      
    case BLUE_ROOF_LEFT_SIDE:
      return new House(position_, "blueroofleftside");
      
    case BLUE_ROOF_RIGHT_SIDE:
      return new House(position_, "blueroofrightside");
      
    case BLUE_ROOF_MIDDLE_EDGE:
      return new House(position_, "blueroofmiddleedge");
      
    case BLUE_ROOF_MIDDLE:
      return new House(position_, "blueroofmiddle");
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_1:
      return new House(position_, "blueroofdownrightcorner1");
      
    case BLUE_ROOF_DOWN_RIGHT_CORNER_2:
      return new House(position_, "blueroofdownrightcorner2");
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_1:
      return new House(position_, "blueroofdownleftcorner1");
      
    case BLUE_ROOF_DOWN_LEFT_CORNER_2:
      return new House(position_, "blueroofdownleftcorner2");
      
    default:
      error_handle("Unknown House part orientation for House");
  }
}
