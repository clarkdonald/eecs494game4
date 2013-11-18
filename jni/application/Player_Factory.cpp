//
//  Player_Factory.cpp
//  game
//
//  Created by Donald Clark on 11/18/13.
//
//

#include "Player_Factory.h"
#include "Player_Includes.h"
#include "Utility.h"

using std::bad_alloc;
using namespace Zeni;

Player * create_player(const String &type_, const Point2f &position_)
{
  if (type_ == "Warrior");
  else if (type_ == "Mage");
  else if (type_ == "Archer");
  error_handle("Unknown player type");
}
