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
  error_handle("Unknown environment type");
  return NULL;
}
