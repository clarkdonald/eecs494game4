//
//  Npc_Factory.cpp
//  game
//
//  Created by Donald Clark on 11/19/13.
//
//

#include "Npc_Factory.h"
#include "Npc_Includes.h"
#include "Utility.h"

using std::bad_alloc;
using namespace Zeni;

Npc * create_npc(const String &type_,
                 const Point2f &position_,
                 const Team &team_,
                 const Vector2f &size_)
{
  if (type_ == "Blonde_Kid") return new Npc(position_, "blondekiddownidle", team_, size_);
  else if (type_ == "Girl") return new Npc(position_, "girldownidle", team_, size_);
  error_handle("Unknown npc type");
  return nullptr;
}
