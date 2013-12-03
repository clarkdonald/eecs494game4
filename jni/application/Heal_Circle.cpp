#include "Heal_Circle.h"

using namespace std;

Heal_Circle::Heal_Circle(const Zeni::Point2f& position) :
	Game_Object(position) {}

void Heal_Circle::render() const 
{
	Game_Object::render("heal_circle");
}