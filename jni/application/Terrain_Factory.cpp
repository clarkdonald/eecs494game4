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

Terrain * create_terrain(const String &type_, const Point2f &position_, const Vector2f &size_)
{
  if (type_ == "Dirt") return new Simple_Terrain(position_, "dirt", size_);
  else if (type_ == "Water") return new Water(position_, size_);
  else if (type_ == "Rock_Pile") return new Simple_Terrain(position_, "rockpile", size_);
  else if (type_ == "Grass") return new Simple_Terrain(position_, "grass", size_);
  else if (type_ == "Stone_Road") return new Stone_Road(position_, size_);
  else if (type_ == "Wood_Floor") return new Simple_Terrain(position_, "woodfloor", size_);
  else if (type_ == "Bush") return new Simple_Terrain(position_, "bush", size_);
  else if (type_ == "Down_Left_Wall") return new Simple_Terrain(position_, "housewallcornerdownleft", size_);
  else if (type_ == "Down_Right_Wall") return new Simple_Terrain(position_, "housewallcornerdownright", size_);
  else if (type_ == "Up_Right_Wall") return new Simple_Terrain(position_, "housewallcornerupright", size_);
  else if (type_ == "Up_Left_Wall") return new Simple_Terrain(position_, "housewallcornerupleft", size_);
  else if (type_ == "Up_Wall") return new Simple_Terrain(position_, "housewallup", size_);
  else if (type_ == "Down_Wall") return new Simple_Terrain(position_, "housewalldown", size_);
  else if (type_ == "Right_Wall") return new Simple_Terrain(position_, "housewallright", size_);
  else if (type_ == "Left_Wall") return new Simple_Terrain(position_, "housewallleft", size_);
  else if (type_ == "Flower") return new Simple_Terrain(position_, "flowerpot", size_);
  else if (type_ == "Table") return new Simple_Terrain(position_, "table", size_);
  else if (type_ == "Bed") return new Simple_Terrain(position_, "bed", size_);
  else if (type_ == "Chest") return new Simple_Terrain(position_, "chest", size_);
  else if (type_ == "Chair") return new Simple_Terrain(position_, "chair", size_);
  else if (type_ == "Bookshelf") return new Simple_Terrain(position_, "bookshelf", size_);
  else if (type_ == "Dresser") return new Simple_Terrain(position_, "dresser", size_);
  else if (type_ == "Tan_Wall_Door") return new Simple_Terrain(position_, "tanwalldoor", size_);
  error_handle("Unknown terrain type");
  return nullptr;
}
