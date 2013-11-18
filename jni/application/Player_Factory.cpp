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

Player * create_player(const String &type_, const Point2f &position_, const int &uid_)
{
  if (type_ == "Warrior") return new Warrior(position_, uid_);
  else if (type_ == "Mage") return new Mage(position_, uid_);
  else if (type_ == "Archer") return new Archer(position_, uid_);
  error_handle("Unknown player type");
  return nullptr;
}
