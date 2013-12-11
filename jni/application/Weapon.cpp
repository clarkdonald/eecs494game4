#include "Weapon.h"

using namespace Zeni;
using namespace std;

Weapon::Weapon(const Point2f &position_,
               const float &damage_,
               const Team& team_,
               const Vector2f &size_)
: Game_Object(position_, size_),
  damage(damage_),
  stun_attack(false),
  shield(false),
  team(team_)
{}

String Weapon::get_color_str() const
{  
  Team team = get_team();
  String str = "";
	switch(team)
	{
		case RED:
			str = "red_";
			break;
		case BLUE:
			str = "blue_";
			break;
	}
  return str;
}


Weapon::~Weapon() {}
