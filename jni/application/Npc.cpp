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
         const Team &team_,
         const Vector2f &size_)
: Game_Object(position_, size_),
  depositing(-1),
  deposit_indicator(position_ - Vector2f(0.0f, 8.0f), Vector2f(32.0f, 2.0f)),
  texture(texture_),
  team(team_),
  hold_a(false),
  a_button("hold_a", position_ - Vector2f(0.0f,41.0f))
{}

void Npc::set_deposit_pctg(const float &pctg_) {
  deposit_pctg = pctg_;
}

void Npc::render() const {
  if(depositing != -1)
    deposit_indicator.render(deposit_pctg);
  if(hold_a)
    a_button.render();
  Game_Object::render(texture);
}
