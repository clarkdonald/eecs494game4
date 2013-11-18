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
  if (type_ == "Dirt") return new Dirt(position_);
  else if (type_ == "Water") return new Water(position_);
  else if (type_ == "Rock_Pile") return new Rock_Pile(position_);
  else if (type_ == "Grass") return new Grass(position_);
  else if (type_ == "Stone_Road") return new Stone_Road(position_);
  else if (type_ == "Wood_Floor") return new Wood_Floor(position_);
  else if (type_ == "Bush") return new Bush(position_);
  
  error_handle("Unknown terrain type");
}
