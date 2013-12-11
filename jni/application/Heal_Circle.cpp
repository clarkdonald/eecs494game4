#include "Heal_Circle.h"

using namespace std;
using namespace Zeni;

Heal_Circle::Heal_Circle(const Zeni::Point2f& position, Team team_) :
	Game_Object(position, LARGE_SIZE * 2),
  team(team_)
{}

void Heal_Circle::render() const 
{

	Game_Object::render("green_circle");

}

