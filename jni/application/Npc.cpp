//
//  Npc.cpp
//  game
//
//  Created by Donald Clark on 11/19/13.
//
//

#include "Npc.h"

using namespace Zeni;

Npc::Npc(const Point2f &position_,
         const String &texture_,
         const Team &team_)
: Game_Object(position_),
  texture(texture_),
  team(team_)
{}

void Npc::render() const {
  Game_Object::render(texture);
}
