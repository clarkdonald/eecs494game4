//
//  Terrain_Factory.cpp
//  game
//
//  Created by Donald Clark on 11/9/13.
//
//

#include "Terrain_Factory.h"
#include "Terrain_Includes.h"
#include "Utility.h"

using std::bad_alloc;
using namespace Zeni;

Terrain * create_terrain(const String &type_, const Point2f &position_)
{
  if (type_ == "Dirt") return new Simple_Terrain(position_, "dirt");
  else if (type_ == "Water") return new Water(position_);
  else if (type_ == "Rock_Pile") return new Simple_Terrain(position_, "rockpile");
  else if (type_ == "Grass") return new Simple_Terrain(position_, "grass");
  else if (type_ == "Stone_Road") return new Stone_Road(position_);
  else if (type_ == "Wood_Floor") return new Simple_Terrain(position_, "woodfloor");
  else if (type_ == "Bush") return new Simple_Terrain(position_, "bush");
  error_handle("Unknown terrain type");
  return nullptr;
}
