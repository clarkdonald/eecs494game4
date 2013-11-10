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
  if (type_ == "Ground") return new Ground(position_);
  else if (type_ == "Water") return new Water(position_);
  
  error_handle("Unknown terrain type");
}
