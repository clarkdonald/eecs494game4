//
//  Atmosphere_Factory.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Atmosphere_Factory.h"
#include "Atmosphere_Includes.h"
#include "Utility.h"

using std::bad_alloc;
using namespace Zeni;

Atmosphere * create_atmosphere(const String &type_, const Point2f &position_)
{
  if (type_ == "Cloud") return new Cloud(position_);
  error_handle("Unknown atmosphere type");
}
